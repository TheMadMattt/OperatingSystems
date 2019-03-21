cmake_minimum_required(VERSION 3.13)
project(DiningPhilosophersChandyMisra)

set(CMAKE_CXX_STANDARD 17)

add_executable(DiningPhilosophersChandyMisra main.cpp SyncingChannel.cpp SyncingChannel.h Fork.cpp Fork.h Philosopher.cpp Philosopher.h Table.cpp Table.h)