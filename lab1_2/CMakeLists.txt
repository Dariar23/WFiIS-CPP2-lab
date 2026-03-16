cmake_minimum_required(VERSION 3.10)
project(InventoryProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Warnings
if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(include)

add_executable(program
    src/Main.cpp
    src/Monkey.cpp
    src/Tiger.cpp
    src/Zoo.cpp
)
