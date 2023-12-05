cmake_minimum_required(VERSION 3.10)
project(kaylordut)

include_directories(../)

add_subdirectory(time)

add_executable(${PROJECT_NAME}_timeout_example example/timeout_example.cpp)
install(TARGETS ${PROJECT_NAME}_timeout_example
        DESTINATION bin)