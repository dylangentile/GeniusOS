cmake_minimum_required(VERSION 3.13)
project(genius)
#set(EXECUTABLE_OUTPUT_PATH ~/code/geniusbuilds)

#The includes
include_directories(include)

file(GLOB SOURCES src/*.cpp)

#remove from glob
#list(REMOVE_ITEM SOURCES Genius/badcode.cpp)

add_executable(genius ${SOURCES})