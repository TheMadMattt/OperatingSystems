cmake_minimum_required(VERSION 3.13)
project(DiningPhilosophers)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "-pthread")

find_package(Threads REQUIRED)

add_executable(DiningPhilosophers main.cpp Philosopher.cpp Philosopher.h Fork.cpp Fork.h)

target_link_libraries (DiningPhilosophers ${CMAKE_THREAD_LIBS_INIT})