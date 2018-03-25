cmake_minimum_required(VERSION 3.9)
project(DES)

set(CMAKE_CXX_STANDARD 11)

include_directories(/usr/local/include)
link_libraries(/usr/local/lib)

add_executable(DES main.cpp
        des.cpp
        des.h
        des_data.h
        des_key.h
        des_lookup.h
        descbc.cpp
        descbc.h
        DEScryption.cpp DEScryption.h)

target_link_libraries(DES boost_program_options)

