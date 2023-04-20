cmake_minimum_required(VERSION 3.5)
project(file_signature)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Werror")

add_executable(${PROJECT_NAME} main.cpp FileSignature.cpp)
