add_executable(${PROJECT_NAME}_timeout_example timeout_example.cpp)
install(TARGETS ${PROJECT_NAME}_timeout_example
        DESTINATION bin)

add_executable(${PROJECT_NAME}_private_timer_example private_timer_example.cpp)
install(TARGETS ${PROJECT_NAME}_private_timer_example
        DESTINATION bin)

add_executable(${PROJECT_NAME}_time_duration_example time_duration_example.cpp)
install(TARGETS ${PROJECT_NAME}_time_duration_example
        DESTINATION bin)

add_executable(${PROJECT_NAME}_run_once_example run_once_example.cpp)
install(TARGETS ${PROJECT_NAME}_run_once_example
        DESTINATION bin)

#add_definitions(-DSUFFIX_FORMAT_DISABLE)
find_package(spdlog REQUIRED)
add_executable(${PROJECT_NAME}_spdlog_example spdlog_test.cpp)
target_link_libraries(${PROJECT_NAME}_spdlog_example spdlog::spdlog systemd)
install(TARGETS ${PROJECT_NAME}_spdlog_example
        DESTINATION bin)
