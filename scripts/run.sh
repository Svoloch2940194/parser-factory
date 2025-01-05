#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 file1 file2 ... fileN"
    exit 1
fi

CPP_PROGRAM="my_project"

PYTHON_SCRIPT="$(dirname "$0")/plot.py"

if ! command -v "$CPP_PROGRAM" &> /dev/null; then
    echo "C++ program not found in PATH: $CPP_PROGRAM"
    exit 1
fi

if [ ! -f "$PYTHON_SCRIPT" ]; then
    echo "Python script not found: $PYTHON_SCRIPT"
    exit 1
fi

json_output=$("$CPP_PROGRAM" "$@")
cpp_exit_code=$?

if [ $cpp_exit_code -ne 0 ]; then
    echo "Error while executing C++ program"
    echo "$json_output"
    exit $cpp_exit_code
fi

python_output=$(echo "$json_output" | python3 "$PYTHON_SCRIPT")
python_exit_code=$?

if [ $python_exit_code -ne 0 ]; then
    echo "Error while executing Python script"
    echo "$python_output"
    exit $python_exit_code
fi

echo "$python_output"
exit 0    
