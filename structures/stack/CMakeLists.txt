cmake_minimum_required(VERSION 3.10)
project(stack)

add_executable(stack
    stack.cpp
    stack.h
    main.cpp)

set_target_properties(stack PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
