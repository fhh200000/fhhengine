#Basic
cmake_minimum_required(VERSION 3.7)
project(engine_test LANGUAGES CXX)
project(fhhengine LANGUAGES CXX)
#Environment
include_directories(${Vulkan_INCLUDE_DIRS} include/)
include(FindVulkan)
add_executable(engine_test main.cpp)
add_library(fhhengine STATIC framework/frontend.cpp framework/instance.cpp)
target_link_libraries(fhhengine ${Vulkan_LIBRARIES} glfw)
target_link_libraries(engine_test fhhengine)

add_definitions(-DFHHENGINE_MAJOR_VERSION=0)
add_definitions(-DFHHENGINE_MINOR_VERSION=0)
add_definitions(-DFHHENGINE_PATCH_VERSION=1)
install(TARGETS fhhengine RUNTIME DESTINATION bin)
