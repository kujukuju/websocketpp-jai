cmake_minimum_required(VERSION 3.25)
project(websocketpp)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-D_WEBSOCKETPP_CPP11_STL_)
add_definitions(-D_GLIBCXX_USE_NANOSLEEP -DNO_VALIDATE -DASIO_STANDALONE -DENABLE_CPP11=TRUE -D_USE_MATH_DEFINES)

include_directories(asio-1.28.0/include)
include_directories(websocketpp)

add_library(websocketpp SHARED main.cpp main.h)
#add_executable(websocketpp main.cpp main.h)
