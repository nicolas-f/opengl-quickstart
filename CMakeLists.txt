cmake_minimum_required(VERSION 3.10)
project(OpenGLScene)

# Options
option(BUILD_TESTS "Build tests" OFF)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Dependencies/include
)

# Link directories
link_directories(
    ${CMAKE_SOURCE_DIR}/Dependencies/lib-arm64
)

# Find OpenGL
find_package(OpenGL REQUIRED)
find_package(glfw3 3.4 REQUIRED)

# Silence OpenGL deprecation warnings on macOS
add_definitions(-DGL_SILENCE_DEPRECATION)

# Source files
file(GLOB_RECURSE SOURCE_FILES 
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# Executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    glfw
    OpenGL::GL
)

# Installation
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Output information
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "OpenGL Library: ${OPENGL_LIBRARY}")
message(STATUS "Source files: ${SOURCE_FILES}")