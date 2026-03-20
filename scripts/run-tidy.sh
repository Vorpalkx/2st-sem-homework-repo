#!/bin/bash

# Проверяем существование директории build
if [[ ! -d "build" ]]; then
    echo "Error: build directory not found. Please run cmake first."
    exit 1
fi

# Проверяем наличие compile_commands.json
if [[ ! -f "build/compile_commands.json" ]]; then
    echo "Error: compile_commands.json not found in build directory."
    echo "Please configure CMake with -DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
    exit 1
fi

# Проверяем наличие run-clang-tidy
if ! command -v run-clang-tidy &> /dev/null; then
    echo "Error: run-clang-tidy not found. Please install clang-tidy."
    exit 1
fi

# Запускаем clang-tidy
echo "Running clang-tidy..."
run-clang-tidy -p=build

# Сохраняем код возврата
EXIT_CODE=$?

if [[ $EXIT_CODE -eq 0 ]]; then
    echo "clang-tidy completed successfully. No issues found."
else
    echo "clang-tidy found issues. Exit code: $EXIT_CODE"
fi

exit $EXIT_CODE
