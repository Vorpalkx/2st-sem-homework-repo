add_executable(csv
    functions.c
    functions.h
    main.c
    parcer.c
    parcer.h
)

target_compile_options(csv PRIVATE -Wall -Wextra)
