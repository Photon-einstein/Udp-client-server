cmake_minimum_required(VERSION 3.7)
project(udp_server)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp*" )

add_executable(udp_server ${SOURCES})

set_property(TARGET udp_server PROPERTY CXX_STANDART 17)
target_compile_options(udp_server INTERFACE -Wall -Wextra)
