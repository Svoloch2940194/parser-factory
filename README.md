# MyProject

## Описание

Система для парсинга файлов с точками, генерации графика и отображения результатов.

## Составляющие

- **Программа на C++**: Парсит файлы форматов `.txt`, `.bin`, `.json`.
- **Скрипт Python**: Генерирует график на основе полученных данных.
- **Скрипт Bash**: Координирует запуск программы на C++ и скрипта Python.

## Требования к среде

- **ОС**: Linux Ubuntu 22.04
- **Компилятор**: GCC >= 11
- **Python**: >= 3.10
- **C++ стандарт**: >= C++17
- **CMake**: >= 3.16

## Зависимости

### Для C++ программы

- [nlohmann/json](https://github.com/nlohmann/json) (устанавливается через CMake)
- OpenMP (для параллельной обработки)

### Для Python скрипта

- `matplotlib`

## Установка зависимостей

### C++ библиотеки

Все зависимости устанавливаются автоматически через CMake, кроме `nlohmann/json`, если он не установлен.

Для установки `nlohmann/json` можно использовать пакетный менеджер:

```bash
sudo apt-get update
sudo apt-get install nlohmann-json3-dev
