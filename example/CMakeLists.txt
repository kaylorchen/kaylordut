add_executable(${PROJECT_NAME}_timeout_example timeout_example.cpp)
install(TARGETS ${PROJECT_NAME}_timeout_example
        DESTINATION bin)

add_executable(${PROJECT_NAME}_private_timer_example private_timer_example.cpp)
install(TARGETS ${PROJECT_NAME}_private_timer_example
        DESTINATION bin)