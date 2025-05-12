#!/bin/bash

# OpenGL Quickstart Installation Script
# This script performs a complete installation including dependency setup and building

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

# Create initial directory structure
create_initial_directories() {
    print_status "Creating initial directory structure..."
    
    mkdir -p Dependencies/include
    mkdir -p Dependencies/lib-arm64
    mkdir -p build
    
    if [ ! -d "Dependencies/include" ] || [ ! -d "Dependencies/lib-arm64" ]; then
        print_error "Failed to create directory structure."
        exit 1
    fi
    
    print_status "Directory structure created successfully."
}

# Verify dependencies are installed
verify_dependencies() {
    print_status "Verifying dependencies..."
    
    # Verify CMake installation
    if ! command -v cmake &> /dev/null; then
        print_warning "CMake is not installed. Running dependency setup script..."
        setup_dependencies
        return
    fi
    
    # Verify C++ compiler availability
    compiler_found=false
    if command -v clang++ &> /dev/null || command -v g++ &> /dev/null || command -v c++ &> /dev/null; then
        compiler_found=true
    fi
    
    if [ "$compiler_found" = false ]; then
        print_warning "No C++ compiler found. Running dependency setup script..."
        setup_dependencies
        return
    fi
    
    # Verify GLFW installation
    if [ ! -d "Dependencies/include/GLFW" ] || [ ! -f "Dependencies/lib-arm64/libglfw.3.dylib" ]; then
        print_warning "GLFW is not installed. Running dependency setup script..."
        setup_dependencies
        return
    fi
    
    print_status "All required dependencies verified."
}

# Run the setup_dependencies script if needed
setup_dependencies() {
    print_status "Running dependency setup script..."
    
    if [ -f "./scripts/setup_dependencies.sh" ]; then
        bash ./scripts/setup_dependencies.sh
        
        if [ $? -ne 0 ]; then
            print_error "Dependency setup failed. Please check the output for errors."
            exit 1
        fi
    else
        print_error "Could not find setup_dependencies.sh script."
        print_error "Please verify the project structure is correct."
        exit 1
    fi
    
    print_status "Dependency setup completed."
}

# Run the build script
run_build() {
    print_status "Running build script..."
    
    if [ -f "./scripts/build.sh" ]; then
        bash ./scripts/build.sh
        
        if [ $? -ne 0 ]; then
            print_error "Build process failed. Please check the output for errors."
            exit 1
        fi
    else
        print_error "Could not find build.sh script."
        print_error "Please verify the project structure is correct."
        exit 1
    fi
    
    print_status "Build process completed."
}

# Main function
main() {
    print_status "OpenGL Quickstart Installation"
    print_status "=============================="
    
    create_initial_directories
    verify_dependencies
    run_build
    
    print_status "Installation completed successfully!"
    print_status "You can run the application with: ./build/OpenGLScene"
}

# Execute main function
main 