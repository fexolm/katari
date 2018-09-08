cmake_minimum_required(VERSION 3.11)
project(katari)

file(GLOB SOURCES *.cpp)

add_executable(katari_interpreter ${SOURCES})