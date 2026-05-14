cmake_minimum_required(VERSION 3.14)

project(get_Started)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 引入 EventBus (只编译lib子目录，不包含它的测试/benchmark)
add_subdirectory(third_party/EventBUs/lib)

add_executable(get_Started src/main.cpp)

# 当执行add_subdirectory(third_party/EventBUs/lib)时,CMake会去读取third_party/EventBUs/lib/CMakeLists.txt
# 在那个CMakeLists.txt中, 可以找到：
# add_library(EventBus INTERFACE)  # 定义一个库目标，名字叫EventBus，类型是INTERFACE
# add library(Dexode::EventBus ALIAS EventBus)  # 定义一个别名Dexode::EventBus，指向EventBus库目标
# 所以，Dexode::EventBus就是EventBus库目标的别名，可以用来链接到get_Started这个可执行文件上。
target_link_libraries(get_Started PRIVATE Dexode::EventBus)
