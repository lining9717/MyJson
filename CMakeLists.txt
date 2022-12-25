cmake_minimum_required(VERSION 2.6)
project(my_json C)

add_library(myjson myjson.c)
add_executable(json_test test.c)
target_link_libraries(json_test myjson)