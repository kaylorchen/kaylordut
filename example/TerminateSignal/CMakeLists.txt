add_executable(${PROJECT_NAME}_stop_flag stop_flag.cpp
        thread1.cpp)
target_link_libraries(${PROJECT_NAME}_stop_flag ${CUSTOM_LIBS})
