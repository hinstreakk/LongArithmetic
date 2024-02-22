cmake_minimum_required(VERSION 3.27)
project(LongArithmetic LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(LongNumbers SHARED
        header/LongNumbers.hpp
        source/LongNumbers.cpp
)

add_executable(pi PiCounting.cpp)
target_link_libraries(pi LongNumbers)

add_executable(test tests.cpp)
target_link_libraries(test LongNumbers)

add_custom_target(evalpi COMMAND pi)
add_custom_target(runtest COMMAND test)