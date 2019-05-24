cmake_minimum_required(VERSION 3.13)
project(HouseMultithreading)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -no-pie -pedantic -g")
find_package(Threads REQUIRED)
set(ADDITIONAL_LIBRARIES menu)
find_package(Curses REQUIRED)

add_executable(HouseMultithreading main.cpp Printing.cpp Printing.h SyncingChannel.cpp SyncingChannel.h House.cpp House.h Person.cpp Person.h Adult.cpp Adult.h Child.cpp Child.h)
target_link_libraries(HouseMultithreading Threads::Threads curses menu)