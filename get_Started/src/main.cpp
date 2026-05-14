#include <dexode/EventBus.hpp>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

// 1.定义事件（普通struct, 随意定义字段）
namespace Event {
    struct SensorData {
        int sensorId;
        float temperature;
    };

    struct SystemError {
        std::string message;
        int errorCode;
    };
}

// 2.一个业务模块，持有Listener
class DataProcessor {
    public:
        explicit DataProcessor(std::shared_ptr<dexode::EventBus> bus) : _listener(bus) {
            // 3. 注册监听 -- lambda方式
            _listener.listen([this](const Event::SensorData& data) {
                onSensorData(data);
            });

            // 也可以直接绑定成员函数
            _listener.listen<Event::SystemError>(std::bind(&DataProcessor::onError, this, std::placeholders::_1));
        }

    private:
        void onSensorData(const Event::SensorData& data) {
            std::cout << "Received Sensor Data: ID=" << data.sensorId << ", Temp=" << data.temperature << std::endl;
        }

        void onError(const Event::SystemError& error) {
            std::cout << "Received System Error: " << error.message << " (Code: " << error.errorCode << ")" << std::endl;
        }

        dexode::EventBus::Listener _listener; // RAII, 析构时自动注销
};

int main() {
    // 通常存在singleton 或 主控制器里
    auto bus = std::make_shared<dexode::EventBus>();

    DataProcessor processor(bus);

    // 4. 投递事件（放入队列，不立即触发）
    bus->postpone(Event::SensorData{1, 36.5f});
    bus->postpone(Event::SensorData{2, 22.3f});

    bus->postpone(Event::SystemError{"Overheating detected", 408});

    // 5. 处理所有排队的事件（同步执行所有回调）
    bus->process();

    return 0;
}




