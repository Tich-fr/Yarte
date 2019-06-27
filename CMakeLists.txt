# --------------------------------------------------------------------------
# Project definition
# --------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.7)
project(Yarte)

# --------------------------------------------------------------------------
# Directories
# --------------------------------------------------------------------------
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")

# --------------------------------------------------------------------------
# Source files
# --------------------------------------------------------------------------
set(SOURCES
    "${SRC_DIR}/main.cpp"
    )

# --------------------------------------------------------------------------
# Executable def and properties
# --------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

# usefull if you use llvm /vim autocompletion, ...
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --------------------------------------------------------------------------
# Third-party stuff
# --------------------------------------------------------------------------
# ==== GLM ==== #
target_include_directories(${PROJECT_NAME} PRIVATE "${INC_DIR}/glm")
