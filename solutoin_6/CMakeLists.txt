cmake_minimum_required(VERSION 3.5)

project(mtfind LANGUAGES CXX)
find_package(Threads)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mtfind
    src/main.cpp
    src/patterns.h
    src/patterns.cpp
    src/findpatterns.h
    src/findpatterns.cpp
    src/utils.h
    src/utils.cpp
)

target_link_libraries(mtfind Threads::Threads)
