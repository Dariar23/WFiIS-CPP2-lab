cmake_minimum_required(VERSION 3.10)
project(zad)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(zad
    src/Main.cpp
  

   
)


target_include_directories(zad PRIVATE include)