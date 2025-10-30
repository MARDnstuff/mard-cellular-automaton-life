cmake_minimum_required(VERSION 3.5)

project(Attractor_MakeFile LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Attractor_MakeFile main.cpp nodo.h nodo.cpp)

install(TARGETS Attractor_MakeFile
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
