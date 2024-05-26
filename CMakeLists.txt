
cmake_minimum_required(VERSION 3.20)

Project(Casino VERSION 1 LANGUAGES CXX)

file(GLOB_RECURSE src "src/*")

add_executable(${PROJECT_NAME} ${src})

target_include_directories(${PROJECT_NAME} PUBLIC inc)

