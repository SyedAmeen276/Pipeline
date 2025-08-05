cmake_minimum_required(VERSION 3.28)

project(pipeline CXX)

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pthread")

# Pipeline Execution
SET(SRC_FILES
            ${SRC_DIR}/EnricherStage.cpp
            ${SRC_DIR}/FileSource.cpp
            ${SRC_DIR}/FilterStage.cpp
            ${SRC_DIR}/FlinkStage.cpp
            ${SRC_DIR}/InputSource.cpp
            ${SRC_DIR}/JsonParserStage.cpp
            ${SRC_DIR}/Logger.cpp
            ${SRC_DIR}/Main.cpp
            ${SRC_DIR}/Pipeline.cpp
            ${SRC_DIR}/SensorSource.cpp
            ${SRC_DIR}/SocketSource.cpp
            ${SRC_DIR}/TransformStage.cpp
)

include_directories(include)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(pipeline PRIVATE spdlog::spdlog fmt::fmt)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
)