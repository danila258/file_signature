cmake_minimum_required(VERSION 3.5)
project(file_signature)

set(CMAKE_CXX_STANDARD 17)

# lots of warnings and all warnings as errors
if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory(FileSignature)
add_subdirectory(lib/googletest)
add_subdirectory(test)

# set Boost options
set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_USE_DEBUG_LIBS         OFF)
set(Boost_USE_RELEASE_LIBS        ON)
set(Boost_USE_MULTITHREADED       ON)
set(Boost_USE_STATIC_RUNTIME     OFF)

# find Boost
find_package(Boost 1.78.0 REQUIRED COMPONENTS iostreams REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
                      ${Boost_LIBRARIES}
                      FileSignature)
