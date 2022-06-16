#Basic
SET(CMAKE_C_COMPILER    "gcc")
SET(CMAKE_CXX_COMPILER  "g++")
cmake_minimum_required(VERSION 3.7)
project(engine_test LANGUAGES CXX)
project(fhhengine LANGUAGES CXX)
#Environment
include_directories(${Vulkan_INCLUDE_DIRS} include/)
include(FindVulkan)
add_executable(engine_test main.cpp)
#Files
aux_source_directory (framework/ FHHENGINE_FRAMEWORK)

add_library(fhhengine STATIC ${FHHENGINE_FRAMEWORK})
target_link_libraries(fhhengine ${Vulkan_LIBRARIES} glfw)
target_link_libraries(engine_test fhhengine)

add_definitions(-DFHHENGINE_MAJOR_VERSION=0)
add_definitions(-DFHHENGINE_MINOR_VERSION=0)
add_definitions(-DFHHENGINE_PATCH_VERSION=1)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
add_definitions(-DFHHENGINE_DEBUG=1)
endif()

install(TARGETS fhhengine RUNTIME DESTINATION bin)
