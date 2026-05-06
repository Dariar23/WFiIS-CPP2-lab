cmake_minimum_required(VERSION 3.10)
project(EventBusDemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(EventBusDemo
    src/Main.cpp
    src/EventBus.cpp
    src/Enemy.cpp
    src/Player.cpp
    src/ScoreSystem.cpp
    src/LootSystem.cpp
    src/SoundSystem.cpp
)

target_include_directories(EventBusDemo PRIVATE include)
