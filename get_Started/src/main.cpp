#include <dexode/EventBus.hpp>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

// ============================================================
// 1. 定义事件（普通 struct，字段随意）
//    建议放在独立的 namespace 里，避免与其他类型名冲突
// ============================================================
namespace Event
{
    // 事件类型一：电机温度事件
    struct MotorTemperature
    {
        int sensorId;
        float temperature;
    };

    // 事件类型二：机器人错误事件
    struct RobotError
    {
        std::string message;
        int errorCode;
    };
}

// ============================================================
// 2. 业务模块：持有 Listener，在构造函数里完成订阅
//    Listener 是 RAII 对象，析构时自动注销所有订阅，
//    不需要手动 unlisten，避免野指针风险。
// ============================================================
class DataProcessor
{
public:
    explicit DataProcessor(std::shared_ptr<dexode::EventBus> bus) : _listener(bus) // 源码要求使用初始化成员列表
    {
        // 3a. 订阅方式一：lambda（推荐，简洁）
        _listener.listen([this](const Event::MotorTemperature &data) { onMotorTemperature(data);});

        // 3b. 订阅方式二：std::bind 绑定成员函数
        _listener.listen<Event::RobotError>(std::bind(&DataProcessor::onError, this, std::placeholders::_1));
    }

private:
    void onMotorTemperature(const Event::MotorTemperature &data)
    {
        std::cout << "[DataProcessor] 收到温度事件: ID=" << data.sensorId
                  << ", Temp=" << data.temperature << "C" << std::endl;
    }

    void onError(const Event::RobotError &error)
    {
        std::cout << "[DataProcessor] 收到错误事件: " << error.message
                  << " (Code: " << error.errorCode << ")" << std::endl;
    }

    dexode::EventBus::Listener _listener; // RAII对象，析构时会自动注销，很安全
};

int main()
{
    // 在堆上创建一个EventBus实例，并用shared_ptr管理它的生命周期
    auto bus = std::make_shared<dexode::EventBus>();

    // 将EventBus实例的指针传递给DataProcessor，DataProcessor会在构造函数里订阅事件
    DataProcessor processor(bus);

    // 4. 投递事件（仅入队，回调尚未触发）
    bus->postpone(Event::MotorTemperature{1, 36.5f});
    bus->postpone(Event::MotorTemperature{2, 22.3f});
    bus->postpone(Event::RobotError{"Overheating detected", 408});

    std::cout << ">>> 三个事件已投递入队，但回调尚未触发" << std::endl;
    std::cout << ">>> 调用 process() ..." << std::endl;

    // 5. 处理队列里的所有事件（回调在这里被同步执行）
    bus->process();

    std::cout << ">>> process() 完成" << std::endl;

    return 0;
}