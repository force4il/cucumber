cmake_minimum_required(VERSION 3.10)
project(calculator)

add_executable(calculator
    calculator.cpp)

set_target_properties(calculator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
