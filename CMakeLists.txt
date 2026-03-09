cmake_minimum_required(VERSION 3.10)

# Название проекта
project(security)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(gui)          
add_subdirectory(structures/queue)         
add_subdirectory(structures/stack)        
add_subdirectory(calculator)        

# add_executable(myapp main.cpp)
# target_link_libraries(myapp PRIVATE SomeLibFromSubdirectory)
