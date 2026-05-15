#include <dexode/EventBus.hpp>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

// ============================================================
// 事件定义
// ============================================================
namespace Event {
    struct MotorTemperature {
        int sensorId;
        float temperature;
    };
}

// ============================================================
// 演示一：危险写法 —— Listener 存活时间超过宿主对象
//
// 将 Listener 的生命周期与宿主对象分离（独立管理），
// 宿主对象销毁后 Listener 仍存活，bus 仍持有回调。
// 下次 process() 时，回调访问已销毁的 this，导致未定义行为。
//
// 注意：此处用注释标注危险点，不实际触发崩溃。
// ============================================================
class DangerousProcessor {
public:
    int value = 42; // 用于在回调里访问成员，演示悬空引用

    void subscribe(std::shared_ptr<dexode::EventBus> bus,
                   std::shared_ptr<dexode::EventBus::Listener>& outListener) {
        // 将 Listener 的所有权交给外部，宿主对象不持有它
        // 这样宿主析构时，Listener 不会随之析构，订阅不会自动注销
        auto listener = std::make_shared<dexode::EventBus::Listener>(bus);
        listener->listen([this](const Event::MotorTemperature& data) {
            // 危险：this 可能已经是野指针
            std::cout << "[DangerousProcessor] 收到温度事件, value=" << value << std::endl;
        });
        outListener = listener; // 所有权交给外部
        std::cout << "[DangerousProcessor] 已构造，已订阅（Listener 由外部持有）" << std::endl;
    }

    ~DangerousProcessor() {
        std::cout << "[DangerousProcessor] 析构！但 Listener 还活着，订阅未注销！" << std::endl;
        // Listener 不是成员变量，析构时不会自动注销
        // bus 仍持有指向已销毁 this 的回调 —— 这是野指针
    }
};

// ============================================================
// 演示二：安全写法 —— Listener 作为成员变量（RAII）
//
// Listener 的生命周期与宿主对象绑定。
// 宿主析构时，Listener 成员自动析构，自动注销订阅。
// 不需要任何手动操作。
// ============================================================
class SafeProcessor {
public:
    int value = 100;

    explicit SafeProcessor(std::shared_ptr<dexode::EventBus> bus) : _listener(bus) {
        _listener.listen([this](const Event::MotorTemperature& data) {
            std::cout << "[SafeProcessor]     收到温度事件: ID=" << data.sensorId
                      << ", Temp=" << data.temperature << "C"
                      << ", value=" << value << std::endl;
        });
        std::cout << "[SafeProcessor]     已构造，已订阅" << std::endl;
    }

    ~SafeProcessor() {
        std::cout << "[SafeProcessor]     析构，_listener 成员随之析构，订阅自动注销" << std::endl;
        // 什么都不需要写
    }

private:
    dexode::EventBus::Listener _listener; // 与宿主生命周期绑定
};

int main() {
    auto bus = std::make_shared<dexode::EventBus>();

    // --------------------------------------------------------
    // 演示一：危险写法
    // Listener 生命周期与宿主分离，宿主析构后订阅仍残留
    // --------------------------------------------------------
    std::cout << "========================================" << std::endl;
    std::cout << "  演示一：危险写法（Listener 与宿主分离）" << std::endl;
    std::cout << "========================================" << std::endl;

    std::shared_ptr<dexode::EventBus::Listener> danglingListener;
    {
        auto dp = std::make_unique<DangerousProcessor>();
        dp->subscribe(bus, danglingListener);

        bus->postpone(Event::MotorTemperature{1, 36.5f});
        std::cout << ">>> process()，dp 存活：" << std::endl;
        bus->process(); // 正常，dp 还活着
    }
    // dp 已析构，但 danglingListener 仍持有订阅
    // 此时回调里的 this 是野指针

    std::cout << ">>> dp 已析构，danglingListener 仍存活" << std::endl;
    bus->postpone(Event::MotorTemperature{2, 40.0f});
    std::cout << ">>> process()，dp 已析构，回调访问野指针（未定义行为，可能崩溃）：" << std::endl;
    // ⚠️  下面这行是危险的，实际项目中这里会崩溃或产生随机结果
    // bus->process();
    std::cout << ">>> [已跳过 process()，避免实际崩溃，但真实场景中这里会出问题]" << std::endl;

    danglingListener.reset(); // 清理
    bus->postpone(Event::MotorTemperature{2, 40.0f});
    bus->process(); // 清空队列

    std::cout << std::endl;

    // --------------------------------------------------------
    // 演示二：安全写法（RAII）
    // Listener 是成员变量，与宿主生命周期完全绑定
    // --------------------------------------------------------
    std::cout << "========================================" << std::endl;
    std::cout << "  演示二：安全写法（Listener 作为成员变量）" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        auto sp = std::make_unique<SafeProcessor>(bus);

        bus->postpone(Event::MotorTemperature{3, 55.0f});
        std::cout << ">>> process()，sp 存活：" << std::endl;
        bus->process(); // 正常收到
    }
    // sp 析构时，_listener 成员自动析构，订阅自动注销

    bus->postpone(Event::MotorTemperature{4, 60.0f});
    std::cout << ">>> process()，sp 已析构，订阅已自动注销：" << std::endl;
    bus->process(); // 没有任何回调被触发，安全

    std::cout << "\n========================================" << std::endl;
    std::cout << "  例程结束" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}

