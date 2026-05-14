cmake_minimum_required(VERSION 3.14)

project(get_Started)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # 生成compile_commands.json文件，方便IDE使用。（读取它来知道头文件路径、宏定义，提供准确的代码补全和跳转）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 引入 EventBus (只编译lib子目录，不包含它的测试/benchmark)
add_subdirectory(third_party/EventBus/lib)

add_executable(get_Started src/main.cpp)

# 当执行add_subdirectory(third_party/EventBus/lib)时,CMake会去读取third_party/EventBus/lib/CMakeLists.txt
# 在那个CMakeLists.txt中, 可以找到：
# add library(Dexode::EventBus ALIAS EventBus)  # 定义一个别名Dexode::EventBus，指向EventBus库目标
# 所以，Dexode::EventBus就是EventBus库目标的别名，可以用来链接到get_Started这个可执行文件上。
target_link_libraries(get_Started PRIVATE Dexode::EventBus)
