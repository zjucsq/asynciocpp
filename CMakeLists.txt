cmake_minimum_required(VERSION 3.22)
project(cpp20)

set (CMAKE_C_COMPILER "/usr/bin/gcc")
set (CMAKE_CXX_COMPILER "/usr/bin/g++")

# if(APPLE)
#     set(CMAKE_C_COMPILER "/Users/csq/anaconda3/envs/g++/bin/clang")
#     set(CMAKE_CXX_COMPILER "/Users/csq/anaconda3/envs/g++/bin/clang++")
# endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   # For clang-tidy.
set(BUILD_SHARED_LIBS OFF)              # We expect external libraries to be linked statically.
set(CMAKE_CXX_STANDARD 20)              # Compile as C++20.
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # Require C++20 support.

SET(CMAKE_BUILD_TYPE "Debug")
# SET(CMAKE_BUILD_TYPE "Release")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -fno-omit-frame-pointer -g")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=thread")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=thread")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*/*/*.cpp")

set(NOT_COMPILE "")

foreach(file ${CPP_FILES})
    get_filename_component(filename ${file} NAME_WE)
    if (NOT ${filename} IN_LIST NOT_COMPILE)
        add_executable(${filename} ${file})
        message("add ${filename}")
        target_link_libraries(${filename} PRIVATE pthread)
    endif()
endforeach()

