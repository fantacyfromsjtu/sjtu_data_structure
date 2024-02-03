cmake_minimum_required(VERSION 3.26)
project(list)

set(CMAKE_CXX_STANDARD 17)

add_executable(list main.cpp
        list.h
        seqList.cpp
        sLinkList.cpp
        dLinkList.cpp)
