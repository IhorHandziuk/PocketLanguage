cmake_minimum_required(VERSION 3.10)
project(PocketLanguage)

set(CMAKE_CXX_STANDARD 11)

add_executable(PocketLanguage main.cpp Program.cpp arithmetics/Expression.cpp)