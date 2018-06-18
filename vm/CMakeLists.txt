cmake_minimum_required(VERSION 2.6)
project(VMEmulator)

add_executable(VMEmulator VMEmulator.cpp Parser.cpp CodeWriter.cpp)
