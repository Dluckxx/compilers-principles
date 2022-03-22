cmake_minimum_required(VERSION 3.21)
project(compilers-principles)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        symbol-table-demo
        main.cpp
        Env.h Env.cpp
        Symbol.h Symbol.cpp
        TranslateLibrary.h TranslateLibrary.cpp
)
