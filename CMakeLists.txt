#Basic
cmake_minimum_required(VERSION 3.7)
project(engine_test LANGUAGES CXX)
project(fhhengine LANGUAGES CXX)
#Environment
include_directories(${Vulkan_INCLUDE_DIRS} include/)
include(FindVulkan)
add_executable(engine_test main.cpp)
add_library(fhhengine STATIC framework/frontend.cpp)
target_link_libraries(fhhengine ${Vulkan_LIBRARIES} glfw)
target_link_libraries(engine_test fhhengine)
install(TARGETS fhhengine RUNTIME DESTINATION bin)
