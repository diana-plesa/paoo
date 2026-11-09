cmake_minimum_required(VERSION 3.10)

project(libstudent)

add_library(student STATIC student.cpp)
target_include_directories(student PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS student DESTINATION lib)
install(FILES student.h DESTINATION include)
