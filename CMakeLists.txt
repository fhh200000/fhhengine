cmake_minimum_required(VERSION 3.0)

project(fhhengine LANGUAGES C)

add_executable(fhhengine main.c)

install(TARGETS fhhengine RUNTIME DESTINATION bin)
