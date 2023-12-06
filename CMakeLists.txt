cmake_minimum_required(VERSION 3.26)
project(imsProjekt)

set(CMAKE_CXX_STANDARD 14)

add_executable(imsProjekt
        main.cpp)
target_link_libraries(imsProjekt simlib)