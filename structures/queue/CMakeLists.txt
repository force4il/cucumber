cmake_minimum_required(VERSION 3.10)
project(queue)

add_executable(queue
    queue.cpp
    queue.h
    main.cpp)

set_target_properties(queue PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../../bin"
)
