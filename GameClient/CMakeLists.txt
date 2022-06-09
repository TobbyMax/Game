cmake_minimum_required(VERSION 3.21)
project(GameClient)

set(CMAKE_CXX_STANDARD 17)

add_executable(GameClient main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR C:/Program Files/SFML/lib/cmake/SFML)

find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/Program Files/SFML/include)
target_link_libraries(GameClient sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
