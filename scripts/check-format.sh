#!/bin/bash

# Путь к директории build (исключается из поиска)
BUILD_DIR="build"

# Функция для поиска файлов
find_files() {
    find . -path "./$BUILD_DIR" -prune -o -type f -name '*.[c|h]' -print
}

# Проверяем наличие флага --format
if [[ "$1" == "--format" ]]; then
    # Режим форматирования: применяем изменения
    echo "Applying formatting to source files..."
    find_files | xargs clang-format --style=file -i
    echo "Formatting complete."
else
    # Режим проверки: dry-run с ошибками
    echo "Checking formatting (dry-run)..."
    find_files | xargs clang-format --style=file --dry-run -Werror
    echo "Check complete."
fi
