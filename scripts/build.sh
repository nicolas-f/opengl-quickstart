#!/bin/bash

# OpenGL Quickstart Build Script
# This script handles the compilation of the OpenGL Quickstart project

# Color definitions for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# Function definitions for status output
print_status() {
    echo -e "${GREEN}[STATUS]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

# Platform verification
if [[ "$OSTYPE" != "darwin"* ]]; then
    print_error "This script is designed to run on macOS."
    exit 1
fi

# Create directory structure if not exists
create_directories() {
    print_status "Verifying directory structure..."
    
    mkdir -p build
    
    if [ ! -d "build" ]; then
        print_error "Failed to create build directory."
        exit 1
    fi
    
    print_status "Directory structure verified."
}

# Verify dependencies before building
verify_dependencies() {
    print_status "Verifying dependencies..."
    
    # Verify CMake installation
    if ! command -v cmake &> /dev/null; then
        print_error "CMake is not installed. Please run the setup_dependencies.sh script first."
        exit 1
    fi
    
    # Verify C++ compiler availability
    if command -v clang++ &> /dev/null; then
        print_status "Found Clang++ compiler."
    elif command -v g++ &> /dev/null; then
        print_status "Found G++ compiler."
    elif command -v c++ &> /dev/null; then
        print_status "Found C++ compiler."
    else
        print_error "No C++ compiler found. Please run setup_dependencies.sh first."
        exit 1
    fi
    
    # Verify GLFW installation
    if [ ! -d "Dependencies/include/GLFW" ] || [ ! -f "Dependencies/lib-arm64/libglfw.3.dylib" ]; then
        print_error "GLFW libraries not found. Please run setup_dependencies.sh first."
        exit 1
    fi
    
    print_status "All dependencies verified."
}

# Execute CMake build process
build_project() {
    print_status "Building OpenGL Quickstart..."
    
    cd build
    cmake ..
    
    if [ $? -ne 0 ]; then
        print_error "CMake configuration failed."
        exit 1
    fi
    
    cmake --build .
    
    if [ $? -ne 0 ]; then
        print_error "Build process failed."
        exit 1
    fi
    
    cd ..
    
    print_status "Build completed successfully."
}

# Main function
main() {
    print_status "OpenGL Quickstart Build Script"
    print_status "==============================="
    
    create_directories
    verify_dependencies
    build_project
    
    print_status "Build completed successfully."
    print_status "You can run the application with: ./build/OpenGLScene"
}

# Execute main function
main 