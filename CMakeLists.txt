cmake_minimum_required(VERSION 3.15)

project(RingBuffer LANGUAGES C)

add_library(rb_lib)
target_sources(rb_lib PRIVATE ring_buffer.c)

add_executable(test_runner test_runner.c)
target_link_libraries(test_runner PRIVATE rb_lib)
