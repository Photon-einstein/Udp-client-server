cmake_minimum_required(VERSION 3.7)
project(udp_client)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp*" )

add_executable(udp_client ${SOURCES})

set_property(TARGET udp_client PROPERTY CXX_STANDART 17)
target_compile_options(udp_client INTERFACE -Wall -Wextra)
