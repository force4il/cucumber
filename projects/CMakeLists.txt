cmake_minimum_required(VERSION 3.10)
project(projects)

# Исполняемый файл для очереди
add_executable(queue queue.cpp )

# Исполняемый файл для стека
add_executable(stack stack.cpp )

# Исполняемый файл для калькулятора
add_executable(calculator calculator.cpp)

set_target_properties(projects PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
