cmake_minimum_required(VERSION 3.0.0)

project(FIFA21-Players VERSION 0.1.0)

add_subdirectory(src/HashTable)

add_executable(FIFA21-Players src/main.cpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC src/HashTable
)

target_link_directories(${PROJECT_NAME} 
    PRIVATE src/HashTable
)

target_link_libraries(${PROJECT_NAME} 
    hashTable)