#!/bin/bash

# OpenGL Quickstart Dependency Setup Script
# This script handles the installation of all required dependencies

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

# Verify Homebrew installation and install if necessary
verify_homebrew() {
    print_status "Verifying Homebrew installation..."
    
    if ! command -v brew &> /dev/null; then
        print_status "Homebrew not found. Installing Homebrew..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
        
        if [ $? -ne 0 ]; then
            print_error "Failed to install Homebrew."
            exit 1
        fi
    else
        print_status "Homebrew is already installed."
    fi
}

# Install CMake using Homebrew
install_cmake() {
    print_status "Verifying CMake installation..."
    
    if ! command -v cmake &> /dev/null; then
        print_status "CMake not found. Installing using Homebrew..."
        brew install cmake
        
        if [ $? -ne 0 ]; then
            print_error "Failed to install CMake."
            exit 1
        fi
    else
        print_status "CMake is already installed."
    fi
}

# Check for any C++ compiler (Clang or GCC)
verify_cpp_compiler() {
    print_status "Checking for C++ compiler..."
    
    # Check for multiple compiler variants
    if command -v clang++ &> /dev/null; then
        print_status "Found Clang++ compiler."
        return 0
    elif command -v g++ &> /dev/null; then
        print_status "Found G++ compiler."
        return 0
    elif command -v c++ &> /dev/null; then
        print_status "Found C++ compiler."
        return 0
    else
        print_warning "No C++ compiler found. A C++ compiler is required to build the project."
        print_status "Available installation options:"
        
        echo ""
        echo "Options:"
        echo "1) Install Clang via Homebrew"
        echo "2) Install Xcode Command Line Tools"
        echo "3) Skip (if you plan to install a compiler manually)"
        read -p "Select option (1-3): " compiler_option
        
        case $compiler_option in
            1)
                print_status "Installing Clang via Homebrew..."
                brew install llvm
                # Add LLVM to PATH for this session
                export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
                print_status "Clang installed. For permanent use, add to your shell profile:"
                print_status "echo 'export PATH=\"/opt/homebrew/opt/llvm/bin:\$PATH\"' >> ~/.zshrc"
                ;;
            2)
                print_status "Installing Xcode Command Line Tools..."
                xcode-select --install
                print_warning "Please follow the prompts to install Xcode Command Line Tools."
                print_warning "After installation completes, please run this script again."
                exit 0
                ;;
            3)
                print_warning "Skipping compiler installation. Please ensure a compiler is installed before building."
                ;;
            *)
                print_error "Invalid option. Skipping compiler installation."
                ;;
        esac
    fi
}

# Get latest GLFW version from GitHub API
get_latest_glfw_version() {
    # Redirect status message to stderr
    print_status "Checking for latest GLFW version..." >&2
    
    # Fetch latest version silently (output only the version number to stdout)
    latest_version=$(curl -s https://api.github.com/repos/glfw/glfw/releases/latest | grep -o '"tag_name": ".*"' | cut -d'"' -f4)
    
    # If API fails, fallback to a known version
    if [ -z "$latest_version" ]; then
        print_warning "Could not determine latest GLFW version. Using fallback version 3.4." >&2
        latest_version="3.4"
    else
        print_status "Latest GLFW version: $latest_version" >&2
    fi
    
    # Return only the version string with no extra output
    echo "$latest_version"
}

# Setup GLFW library
setup_glfw() {
    print_status "Setting up GLFW library..."
    
    # Create directories if they don't exist
    mkdir -p Dependencies/include
    mkdir -p Dependencies/lib-arm64
    
    # Skip if GLFW is already installed
    if [ -d "Dependencies/include/GLFW" ] && [ -f "Dependencies/lib-arm64/libglfw.3.dylib" ]; then
        print_status "GLFW is already installed."
        return 0
    fi
    
    echo ""
    echo "GLFW setup options:"
    echo "1) Manual download (recommended for latest version)"
    echo "2) Automatic download"
    read -p "Select option (1-2): " option
    
    case $option in
        1)
            setup_glfw_manual
            ;;
        2)
            setup_glfw_automatic
            ;;
        *)
            print_error "Invalid option. Please select 1 or 2."
            setup_glfw
            ;;
    esac
}

# Guide user through manual GLFW download
setup_glfw_manual() {
    print_status "Manual GLFW setup selected."
    echo ""
    echo "Please follow these steps:"
    echo "1) Visit the GLFW download page: https://www.glfw.org/download.html"
    echo "2) Download the 'macOS pre-compiled binaries'"
    echo "3) Extract the archive"
    echo "4) Copy the contents to the correct directories:"
    echo "   - Copy 'include/GLFW' directory to '$(pwd)/Dependencies/include/'"
    echo "   - Copy appropriate library file to '$(pwd)/Dependencies/lib-arm64/':"
    echo "     - For Apple Silicon (M1/M2): copy 'lib-arm64/libglfw.3.dylib'"
    echo "     - For Intel Macs: copy 'lib-universal/libglfw.3.dylib'"
    echo ""
    read -p "Press Enter when you have completed these steps..." confirm
    
    # Verify GLFW files are in the correct location
    if [ ! -d "Dependencies/include/GLFW" ] || [ ! -f "Dependencies/lib-arm64/libglfw.3.dylib" ]; then
        print_error "GLFW files not found in the expected directories."
        echo "Would you like to:"
        echo "1) Try again with manual setup"
        echo "2) Switch to automatic download"
        read -p "Select option (1-2): " retry_option
        
        case $retry_option in
            1)
                setup_glfw_manual
                ;;
            2)
                setup_glfw_automatic
                ;;
            *)
                print_error "Invalid option. Exiting."
                exit 1
                ;;
        esac
    else
        print_status "GLFW files successfully installed."
    fi
}

# Download GLFW automatically
setup_glfw_automatic() {
    print_status "Automatic GLFW download selected."
    
    # Get latest version (capturing only the version string, not status messages)
    latest_version=$(get_latest_glfw_version)
    
    print_status "Downloading GLFW version $latest_version..."
    
    # Create temporary directory
    mkdir -p temp
    cd temp
    
    # Use hardcoded URL format for GLFW downloads with the detected version
    download_url="https://github.com/glfw/glfw/releases/download/$latest_version/glfw-$latest_version.bin.MACOS.zip"
    
    # Download GLFW with improved error handling
    if ! curl -L -o glfw-macos.zip "$download_url"; then
        print_error "Failed to download GLFW from: $download_url"
        print_warning "Trying alternative download URL format..."
        
        # Try alternative URL format (some versions use different naming)
        download_url="https://github.com/glfw/glfw/releases/download/$latest_version/glfw-$latest_version-macos.zip"
        if ! curl -L -o glfw-macos.zip "$download_url"; then
            print_error "Both download attempts failed."
            print_warning "Please try the manual download option instead."
            cd ..
            rm -rf temp
            setup_glfw
            return
        fi
    fi
    
    # Extract the archive
    if ! unzip glfw-macos.zip; then
        print_error "Failed to extract GLFW."
        cd ..
        rm -rf temp
        exit 1
    fi
    
    # Copy files to their respective directories
    GLFW_DIR=$(find . -type d -name 'glfw-*')
    
    # Check if we found the directory
    if [ -z "$GLFW_DIR" ]; then
        print_error "Failed to find extracted GLFW directory."
        cd ..
        rm -rf temp
        exit 1
    fi
    
    # Show directory content for debugging
    print_status "Found GLFW directory: $GLFW_DIR"
    print_status "Directory contents:"
    ls -la "$GLFW_DIR"
    
    # Copy include files
    if [ -d "$GLFW_DIR/include/GLFW" ]; then
        cp -r "$GLFW_DIR/include/GLFW" ../Dependencies/include/
    else
        print_error "GLFW include directory not found."
        cd ..
        rm -rf temp
        exit 1
    fi
    
    # Detect architecture and copy appropriate library
    if [[ $(uname -m) == 'arm64' ]]; then
        if [ -f "$GLFW_DIR/lib-arm64/libglfw.3.dylib" ]; then
            cp "$GLFW_DIR/lib-arm64/libglfw.3.dylib" ../Dependencies/lib-arm64/
        else
            print_error "ARM64 library not found, looking for universal library..."
            if [ -f "$GLFW_DIR/lib-universal/libglfw.3.dylib" ]; then
                cp "$GLFW_DIR/lib-universal/libglfw.3.dylib" ../Dependencies/lib-arm64/
            else
                print_error "No compatible library found."
                cd ..
                rm -rf temp
                exit 1
            fi
        fi
    else
        # For Intel Mac
        if [ -f "$GLFW_DIR/lib-universal/libglfw.3.dylib" ]; then
            cp "$GLFW_DIR/lib-universal/libglfw.3.dylib" ../Dependencies/lib-arm64/
            print_warning "Using universal library for Intel Mac."
        elif [ -f "$GLFW_DIR/lib-x86_64/libglfw.3.dylib" ]; then
            cp "$GLFW_DIR/lib-x86_64/libglfw.3.dylib" ../Dependencies/lib-arm64/
            print_warning "Using x86_64 library for Intel Mac."
        else
            print_error "No compatible library found for Intel Mac."
            cd ..
            rm -rf temp
            exit 1
        fi
    fi
    
    # Clean up
    cd ..
    rm -rf temp
    
    # Verify installation
    if [ -d "Dependencies/include/GLFW" ] && [ -f "Dependencies/lib-arm64/libglfw.3.dylib" ]; then
        print_status "GLFW installed successfully."
    else
        print_error "Installation verification failed. GLFW files are missing."
        exit 1
    fi
}

# Main function
main() {
    print_status "OpenGL Quickstart Dependency Setup"
    print_status "=================================="
    
    verify_homebrew
    verify_cpp_compiler
    install_cmake
    setup_glfw
    
    print_status "Dependency setup completed successfully."
    print_status "You can now build the project using: ./scripts/build.sh"
}

# Execute main function
main 