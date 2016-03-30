cmake_minimum_required(VERSION 3.4)
project(pset6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    public/test/index.html
    public/cat.html
    public/cat.jpg
    public/favicon.ico
    public/hello.html
    public/hello.php
    Makefile
    server.c)

add_executable(pset6 ${SOURCE_FILES})