cmake_minimum_required(VERSION 3.15...4.4)

project(PingPong VERSION 1.0 DESCRIPTION "PingPong Atari Style" LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main 
	src/main.cpp
    src/Entity.cpp
	src/Paddle.cpp
)

target_compile_features(main PRIVATE cxx_std_23)

target_include_directories(main PRIVATE ${PROJECT_SOURCE_DIR}/include)
