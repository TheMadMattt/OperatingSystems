cmake_minimum_required(VERSION 3.13)
project(DiningPhilosophersChandyMisra)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -no-pie -pedantic -g")
find_package(Threads REQUIRED)
set(ADDITIONAL_LIBRARIES menu)
find_package(Curses REQUIRED)


add_executable(DiningPhilosophersChandyMisra main.cpp SyncingChannel.cpp SyncingChannel.h Fork.cpp Fork.h Philosopher.cpp Philosopher.h Table.cpp Table.h Printing.cpp Printing.h)
target_link_libraries(DiningPhilosophersChandyMisra Threads::Threads curses menu)