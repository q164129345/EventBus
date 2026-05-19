#include <dexode/EventBus.hpp>
#include <dexode/eventbus/permission/PostponeBus.hpp>
#include <atomic>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

// ============================================================
// 1. 定义事件（每种传感器对应一个独立的事件类型）
//    放在独立 namespace 里，避免名称冲突
// ============================================================
namespace Event
{
    // 温度事件（由 Worker-1 产生，周期 1 秒）
    struct Temperature
    {
        int   sensorId;
        float celsius;
    };

    // 压力事件（由 Worker-2 产生，周期 2 秒）
    struct Pressure
    {
        int   sensorId;
        float kPa;
    };

    // 电流事件（由 Worker-3 产生，周期 3 秒）
    struct Current
    {
        int   sensorId;
        float ampere;
    };
}

// ============================================================
// 2. DataProcessor：订阅三种传感器事件，收到后打印到控制台
//
//    _listener 是成员变量（RAII），宿主析构时自动注销所有订阅，
//    无需手动 unlisten。
//
//    重要：回调由第 4 个线程（subscriberThread）注册，
//    但实际执行在调用 bus->process() 的线程（主线程）中。
//    EventBus 通过内部互斥锁保证这一过程是线程安全的。
// ============================================================
class DataProcessor
{
public:
    explicit DataProcessor(std::shared_ptr<dexode::EventBus> bus) : _listener(bus)
    {
        _listener.listen([](const Event::Temperature& e) {
            std::cout << "[DataProcessor] 收到温度事件: sensorId=" << e.sensorId
                      << ", celsius=" << e.celsius << " °C" << std::endl;
        });

        _listener.listen([](const Event::Pressure& e) {
            std::cout << "[DataProcessor] 收到压力事件: sensorId=" << e.sensorId
                      << ", kPa=" << e.kPa << " kPa" << std::endl;
        });

        _listener.listen([](const Event::Current& e) {
            std::cout << "[DataProcessor] 收到电流事件: sensorId=" << e.sensorId
                      << ", ampere=" << e.ampere << " A" << std::endl;
        });
    }

private:
    dexode::EventBus::Listener _listener; // RAII，析构时自动注销全部订阅
};

int main()
{
    using namespace std::chrono_literals;
    constexpr auto kRunDuration = 10s; // 程序总运行时长

    // --------------------------------------------------------
    // 3. 创建 EventBus 和 PostponeBus
    //
    //    PostponeBus 是对 EventBus 的权限封装：
    //    仅暴露 postpone() 接口，隐藏 listen() / process()。
    //    将 PostponeBus 传给 worker 线程，体现权限最小化原则：
    //    worker 只能投递事件，不能订阅或驱动处理。
    // --------------------------------------------------------
    auto bus = std::make_shared<dexode::EventBus>();
    dexode::eventbus::permission::PostponeBus postponeBus{bus};

    // --------------------------------------------------------
    // 4. 运行标志：主线程到时间后置为 false，各线程据此退出
    // --------------------------------------------------------
    std::atomic<bool> running{true};

    // --------------------------------------------------------
    // 5. Worker 线程（只负责 postpone，不能 listen / process）
    //
    //    多个 worker 可以并发调用 postpone()，EventBus 内部
    //    通过互斥锁保证线程安全，无需在这里额外加锁。
    //
    //    Worker-1：每 1 秒投递一次温度事件
    // --------------------------------------------------------
    std::thread worker1([&postponeBus, &running]() {
        int count = 0;
        while (running)
        {
            float celsius = 20.0f + static_cast<float>(count % 10) * 0.5f; // 模拟采样
            postponeBus.postpone(Event::Temperature{1, celsius});
            std::cout << "[Worker-1] 投递温度事件: " << celsius << " °C" << std::endl;
            ++count;
            std::this_thread::sleep_for(1s);
        }
    });

    // Worker-2：每 2 秒投递一次压力事件
    std::thread worker2([&postponeBus, &running]() {
        int count = 0;
        while (running)
        {
            float kPa = 100.0f + static_cast<float>(count % 5) * 0.3f; // 模拟采样
            postponeBus.postpone(Event::Pressure{2, kPa});
            std::cout << "[Worker-2] 投递压力事件: " << kPa << " kPa" << std::endl;
            ++count;
            std::this_thread::sleep_for(2s);
        }
    });

    // Worker-3：每 3 秒投递一次电流事件
    std::thread worker3([&postponeBus, &running]() {
        int count = 0;
        while (running)
        {
            float ampere = 4.5f + static_cast<float>(count % 8) * 0.1f; // 模拟采样
            postponeBus.postpone(Event::Current{3, ampere});
            std::cout << "[Worker-3] 投递电流事件: " << ampere << " A" << std::endl;
            ++count;
            std::this_thread::sleep_for(3s);
        }
    });

    // --------------------------------------------------------
    // 6. 第 4 个线程：订阅者线程
    //
    //    DataProcessor 在此线程的栈上构造，_listener 与它同
    //    生命周期；线程退出时 processor 析构，订阅自动注销。
    //
    //    注意：回调在这里注册，但执行发生在主线程的
    //    bus->process() 调用中，EventBus 保证这是线程安全的。
    // --------------------------------------------------------
    std::thread subscriberThread([bus, &running]() {
        DataProcessor processor(bus); // 订阅三种传感器事件
        std::cout << "[Subscriber] DataProcessor 已构造，等待主线程 process() 分发事件..." << std::endl;

        while (running)
        {
            std::this_thread::sleep_for(100ms);
        }

        // processor 析构 → _listener 析构 → 三种订阅自动注销
        std::cout << "[Subscriber] 线程退出，DataProcessor 即将析构，订阅自动注销" << std::endl;
    });

    // --------------------------------------------------------
    // 7. 主线程：每 5ms 调用一次 process()
    //
    //    process() 从队列中取出所有待处理事件，逐个触发回调。
    //    即便队列为空，调用也是安全的（直接返回 0）。
    // --------------------------------------------------------
    std::cout << ">>> [主线程] 启动，每 5ms 调用一次 process()，持续 10 秒" << std::endl;

    auto startTime = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - startTime < kRunDuration)
    {
        bus->process();
        std::this_thread::sleep_for(5ms);
    }

    // --------------------------------------------------------
    // 8. 停止所有线程并回收资源
    //
    //    先置 running = false，让各线程在下次循环检查时退出；
    //    join() 等待所有线程安全退出后，再做最终一次 process()，
    //    清空线程退出前最后一轮 postpone 留下的残余事件。
    // --------------------------------------------------------
    std::cout << ">>> [主线程] 10 秒到，通知各线程退出..." << std::endl;
    running = false;

    worker1.join();
    worker2.join();
    worker3.join();
    subscriberThread.join();

    // 最终 drain：确保 worker 退出前最后一批投递的事件不被丢弃
    bus->process();

    std::cout << ">>> [主线程] 所有线程已退出，程序正常结束" << std::endl;
    return 0;
}
