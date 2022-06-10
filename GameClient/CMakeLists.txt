cmake_minimum_required(VERSION 3.21.1)
project(game)

set(CMAKE_CXX_STANDARD 14)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/arial.ttf
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(game source/main.cpp source/Paddle.cpp header/Paddle.h source/Ball.cpp header/Ball.h source/Game.cpp header/Game.h source/Score.cpp header/Score.h source/Info.cpp header/Info.h)

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR SFML/lib/cmake/SFML)

find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(SFML/include)
target_link_libraries(game sfml-system sfml-window sfml-graphics sfml-audio sfml-network)