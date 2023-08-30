cmake_minimum_required(VERSION 3.22)
project(cpp20)

set (CMAKE_C_COMPILER "gcc")
set (CMAKE_CXX_COMPILER "g++")

# if(APPLE)
#     set(CMAKE_C_COMPILER "/Users/csq/anaconda3/envs/g++/bin/clang")
#     set(CMAKE_CXX_COMPILER "/Users/csq/anaconda3/envs/g++/bin/clang++")
# endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   # For clang-tidy.
set(BUILD_SHARED_LIBS OFF)              # We expect external libraries to be linked statically.
set(CMAKE_CXX_STANDARD 20)              # Compile as C++20.
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # Require C++20 support.

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer -g")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*/*/*.cpp")

set(NOT_COMPILE "")

foreach(file ${CPP_FILES})
    get_filename_component(filename ${file} NAME_WE)
    if (NOT ${filename} IN_LIST NOT_COMPILE)
        add_executable(${filename} ${file})
        message("add ${filename}")
    endif()
endforeach()
