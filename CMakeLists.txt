cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)

project(log4cpp)

file(GLOB project_SRCS src/*.cc)

add_executable(log4cpp ${project_SRCS})
