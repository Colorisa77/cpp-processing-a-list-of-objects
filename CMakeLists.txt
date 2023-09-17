cmake_minimum_required(VERSION 3.22)
project(processing_a_list_of_objects)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

add_executable(processing_a_list_of_objects main.cpp
        object_processor.cpp
        object_processor.h
        common.h
)
