cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 11)

project(log4cpp)

file(GLOB project_SRCS src/*.cc)

add_executable(log4cpp ${project_SRCS})
