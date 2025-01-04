#!/bin/bash

# Проверка на наличие хотя бы одного аргумента
if [ "$#" -lt 1 ]; then
    echo "Использование: $0 file1 file2 ... fileN"
    exit 1
fi

# Имя исполняемого файла C++ (должно быть в PATH)
CPP_PROGRAM="my_project"

# Путь к скрипту Python (предполагается, что он находится в той же директории)
PYTHON_SCRIPT="$(dirname "$0")/plot.py"

# Проверка существования программы и скрипта
if ! command -v "$CPP_PROGRAM" &> /dev/null; then
    echo "Программа C++ не найдена в PATH: $CPP_PROGRAM"
    exit 1
fi

if [ ! -f "$PYTHON_SCRIPT" ]; then
    echo "Скрипт Python не найден: $PYTHON_SCRIPT"
    exit 1
fi

# Запуск программы на C++
json_output=$("$CPP_PROGRAM" "$@")
cpp_exit_code=$?

if [ $cpp_exit_code -ne 0 ]; then
    echo "Ошибка при выполнении программы C++"
    echo "$json_output"
    exit $cpp_exit_code
fi

# Передача вывода программе Python
python_output=$(echo "$json_output" | python3 "$PYTHON_SCRIPT")
python_exit_code=$?

if [ $python_exit_code -ne 0 ]; then
    echo "Ошибка при выполнении скрипта Python"
    echo "$python_output"
    exit $python_exit_code
fi

echo "$python_output"
exit 0    
