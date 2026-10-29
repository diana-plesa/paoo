cmake_minimum_required(VERSION 3.10)

project(paoo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libstudent)

add_executable(paoo main.cpp)
target_link_libraries(paoo student)

install(TARGETS paoo DESTINATION bin)
