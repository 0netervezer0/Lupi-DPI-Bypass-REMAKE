cmake_minimum_required(VERSION 3.16)
project(LupiDPI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)  # Автоматическая обработка MOC

add_executable(LupiDPI main.cpp)
target_link_libraries(LupiDPI PRIVATE Qt6::Widgets)
