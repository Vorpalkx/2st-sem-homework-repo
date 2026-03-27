add_executable(test_csv test_csv_parser.c)

target_link_libraries(test_csv PRIVATE csv_lib)

add_test(NAME test_csv COMMAND test_csv)
