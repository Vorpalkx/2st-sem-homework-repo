add_library(csv_lib STATIC
    parser.c
    functions.c
)

target_include_directories(csv_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(csv_app main.c)
target_link_libraries(csv_app PRIVATE csv_lib)
