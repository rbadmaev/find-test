cmake_minimum_required (VERSION 3.5)
project (mtfind)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set (source_dir "${PROJECT_SOURCE_DIR}/src/")
file (GLOB source_files "${source_dir}*.cpp")

add_executable (${PROJECT_NAME} ${source_files})
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)