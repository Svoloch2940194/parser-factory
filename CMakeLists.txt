cmake_minimum_required(VERSION 3.16)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

find_package(nlohmann_json 3.2.0 REQUIRED)

# Добавляем Executable
add_executable(my_project
    src/main.cpp
    src/Parser.cpp
    src/TxtParser.cpp
    src/BinParser.cpp
    src/JsonParser.cpp
)

target_link_libraries(my_project PRIVATE nlohmann_json::nlohmann_json)

install(TARGETS my_project DESTINATION bin)
install(DIRECTORY scripts/ DESTINATION bin/scripts
    FILES_MATCHING PATTERN "*.sh" PATTERN "*.py")
