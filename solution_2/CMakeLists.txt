cmake_minimum_required(VERSION 3.1)

project(mt_find LANGUAGES CXX)

find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)



set(INC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${INC})



set(HEADERS
     ${INC}/worker.hpp
     ${INC}/mask_key.hpp
    )

set(SOURCES
     ${SRC}/worker.cpp
     ${SRC}/main.cpp
    )



add_executable(mtfind ${HEADERS} ${SOURCES} )
target_link_libraries(mtfind Threads::Threads)
