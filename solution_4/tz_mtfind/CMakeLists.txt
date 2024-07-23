
cmake_minimum_required (VERSION 3.8)

find_package(Threads)

set(SOURCES 
	src/tz_mtfind.cpp
	src/stringfinder.cpp
)

set(HEADERS 
	include/tz_mtfind.h
	include/stringfinder.h
)

add_executable (tz_mtfind 
	${HEADERS}
	${SOURCES}
)


target_include_directories(${PROJECT_NAME} PRIVATE src include)
target_link_libraries(${PROJECT_NAME} Threads::Threads)
