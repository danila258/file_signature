cmake_minimum_required(VERSION 3.5)
project(test)

set(CMAKE_CXX_STANDARD 17)

# set Boost options
set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_USE_DEBUG_LIBS         OFF)
set(Boost_USE_RELEASE_LIBS        ON)
set(Boost_USE_MULTITHREADED       ON)
set(Boost_USE_STATIC_RUNTIME     OFF)

# find Boost
find_package(Boost 1.78.0 REQUIRED COMPONENTS iostreams REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp test.cpp)

add_test(NAME ${PROJECT_NAME} COMMAND test)

target_link_libraries(${PROJECT_NAME} PRIVATE
                      FileSignature
                      ${Boost_LIBRARIES}
                      gtest
                      )