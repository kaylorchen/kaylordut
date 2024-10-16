include_directories(../)

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
set(CUSTOM_LIBS spdlog::spdlog)
if (UNIX AND NOT APPLE)
    list(APPEND CUSTOM_LIBS systemd)
endif ()



add_executable(${PROJECT_NAME}_spdlog_example spdlog_test.cpp)
target_link_libraries(${PROJECT_NAME}_spdlog_example ${CUSTOM_LIBS})
install(TARGETS ${PROJECT_NAME}_spdlog_example
        DESTINATION bin)

add_executable(${PROJECT_NAME}_time_cost time_cost.cpp)
target_link_libraries(${PROJECT_NAME}_time_cost ${CUSTOM_LIBS})

add_executable(${PROJECT_NAME}_time_point time_point.cpp)
target_link_libraries(${PROJECT_NAME}_time_point ${CUSTOM_LIBS})

add_executable(${PROJECT_NAME}_condition_var condition_var.cpp)

add_executable(${PROJECT_NAME}_time_example time_example.cpp)
target_link_libraries(${PROJECT_NAME}_time_example ${CUSTOM_LIBS})

add_executable(${PROJECT_NAME}_stop_flag stop_flag.cpp)
target_link_libraries(${PROJECT_NAME}_stop_flag ${CUSTOM_LIBS})
