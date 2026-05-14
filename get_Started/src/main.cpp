#include <dexode/EventBus.hpp>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

// 1.定义事件（普通struct, 随意定义字段）
namespace Event {
    struct MotorTemperature {
        int sensorId;
        float temperature;
    };

    struct RobotError {
        std::string message;
        int errorCode;
    };
}

// 2.一个业务模块，持有Listener
class DataProcessor {
    public:
        explicit DataProcessor(std::shared_ptr<dexode::EventBus> bus) : _listener(bus) {
            // 3. 注册监听 -- lambda方式
            _listener.listen([this](const Event::MotorTemperature& data) {
                onMotorTemperature(data);
            });

            // 也可以直接绑定成员函数
            _listener.listen<Event::RobotError>(std::bind(&DataProcessor::onError, this, std::placeholders::_1));
        }

    private:
        void onMotorTemperature(const Event::MotorTemperature& data) {
            std::cout << "Received Motor Temperature: ID=" << data.sensorId << ", Temp=" << data.temperature << std::endl;
        }

        void onError(const Event::RobotError& error) {
            std::cout << "Received Robot Error: " << error.message << " (Code: " << error.errorCode << ")" << std::endl;
        }

        dexode::EventBus::Listener _listener; // RAII, 析构时自动注销
};

int main() {
    // 通常存在singleton 或 主控制器里
    auto bus = std::make_shared<dexode::EventBus>();

    DataProcessor processor(bus);

    // 4. 投递事件（放入队列，不立即触发）
    bus->postpone(Event::MotorTemperature{1, 36.5f});
    bus->postpone(Event::MotorTemperature{2, 22.3f});

    bus->postpone(Event::RobotError{"Overheating detected", 408});

    // 5. 处理所有排队的事件（同步执行所有回调）
    bus->process();

    return 0;
}




