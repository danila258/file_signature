cmake_minimum_required(VERSION 3.5)
project(FileSignature)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC FileSignature.cpp)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})