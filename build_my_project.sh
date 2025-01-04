#!/bin/bash
set -e

mkdir -p build
cd build

cmake .. -DCMAKE_INSTALL_PREFIX="$HOME/.local"

make

make install

echo "Сборка и установка завершены. Файлы установлены в $HOME/.local/bin"

if [[ ":$PATH:" != *":$HOME/.local/bin:"* ]]; then
    echo "Добавляем $HOME/.local/bin в PATH"
    echo 'export PATH="$HOME/.local/bin:$PATH"' >> "$HOME/.bashrc"
    echo "Пожалуйста, перезапустите терминал или выполните 'source ~/.bashrc' для применения изменений."
else
    echo "$HOME/.local/bin уже присутствует в PATH"
fi
