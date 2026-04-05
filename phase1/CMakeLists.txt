cmake_minimum_required(VERSION 3.20)
project(phase1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(
    ${PROJECT_NAME}
    main.cpp
    src/mat_vec_row_major.cpp
    src/mat_vec_col_major.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    Include
)