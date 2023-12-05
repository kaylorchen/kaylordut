cmake_minimum_required(VERSION 3.10)
project(kaylordut)
#add_subdirectory(time)
#file(GLOB_RECURSE VAR *.h)
#install(FILES ${VAR} DESTINATION include/kaylordut)
install(DIRECTORY time
        DESTINATION include/kaylordut
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp")
