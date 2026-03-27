cmake_minimum_required(VERSION 3.25)
project(project)

set(CMAKE_C_STANDARD 11)

set(MODULES "" CACHE STRING "List  of modules o build")
option(WITH_TESTS "Build tests for enabled modules" ON)

if(WITH_TESTS)
    enable_testing()
endif()

foreach(module ${MODULES})
    message(STATUS "Configuring module: ${module}")

    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/${module})
        add_subdirectory(src/${module})
    else()
        message(FATAL_ERROR "Module ${module} not found in src/")
    endif()

    if(WITH_TESTS AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/${module})
        add_subdirectory(tests/${module})
    endif()
endforeach()
