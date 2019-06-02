cmake_minimum_required(VERSION 3.14)
project(HouseMultithreading)

set(CMAKE_CXX_STANDARD 17)
find_package(Threads REQUIRED)
set(ADDITIONAL_LIBRARIES menu)
find_package(Curses REQUIRED)

add_executable(HouseMultithreading main.cpp Printing.cpp Printing.h HouseSetup.cpp HouseSetup.h House.cpp House.h Threads/Person.cpp Threads/Person.h Threads/Adult.cpp Threads/Adult.h Threads/Child.cpp Threads/Child.h Resources/TV.cpp Resources/TV.h Resources/Shower.cpp Resources/Shower.h HouseStuff.cpp HouseStuff.h Resources/Console.cpp Resources/Console.h Resources/Chair.cpp Resources/Chair.h)
target_link_libraries(HouseMultithreading Threads::Threads curses menu)