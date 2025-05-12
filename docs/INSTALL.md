# Installation Guide

This document provides detailed instructions for installing and configuring the OpenGL Quickstart project on macOS, with specific optimizations for Apple Silicon Macs.

## Prerequisites

Before installation, ensure you have the following prerequisites:

- macOS 10.15 or higher (macOS 11+ recommended for Apple Silicon)
- A C++ compiler (Clang, GCC, or any compatible compiler)
- CMake 3.0 or higher

## Installation Methods

Two installation methods are available:

1. **Automatic Installation** (Recommended)
2. **Manual Installation**

## Automatic Installation

The automatic installation utilizes scripts to configure all necessary components with minimal user intervention.

### Step 1: Clone the Repository

```bash
git clone https://github.com/kust1011/opengl-quickstart.git
cd opengl-quickstart
```

### Step 2: Run the Installation Script

The most efficient approach is to run the installation script directly:

```bash
./scripts/install.sh
```

This command automatically executes the dependency setup script when required.

### Alternative: Execute the Dependencies Script Separately

For greater control over the setup process, you can run the dependencies script independently:

```bash
./scripts/setup_dependencies.sh
```

This script performs the following operations:
- Verifies Homebrew installation and installs if necessary
- Checks for C++ compiler availability and offers installation options if none is found
- Installs CMake if not already present
- Configures GLFW (with options for manual or automatic installation)
- Automatically detects your Mac's architecture (Intel vs Apple Silicon)
- Installs the appropriate libraries for your hardware configuration

#### C++ Compiler Options

When no C++ compiler is detected, the script presents these options:

1. **Install Clang via Homebrew**
   - Installs LLVM/Clang through Homebrew
   - More lightweight than Xcode Command Line Tools
   - Recommended for Apple Silicon Macs

2. **Install Xcode Command Line Tools**
   - Apple's standard development tools
   - Includes Clang and additional utilities

3. **Skip Installation**
   - For users who prefer to install a compiler manually

#### GLFW Setup Options

The script offers two GLFW installation methods:

1. **Manual Download**
   - Guides you through downloading the latest version from the GLFW website
   - Provides instructions for copying files to the appropriate directories
   - Assists in selecting the correct files for your Mac's architecture

2. **Automatic Download**
   - Detects and downloads the latest GLFW version automatically
   - Selects the correct library based on your Mac's architecture
   - Provides fallback to a stable version if automatic detection fails

### Step 3: Build the Project

If you used the dependencies script separately, execute the build script:

```bash
./scripts/build.sh
```

Alternatively, you can run the installation script which includes building:

```bash
./scripts/install.sh
```

The script:
- Creates necessary directory structure
- Verifies dependencies
- Builds the project using CMake with architecture-specific settings

### Step 4: Run the Application

After successful installation, launch the application:

```bash
./build/OpenGLScene
```

## Manual Installation

For users who prefer manual configuration:

### Step 1: Install Prerequisites

1. Install a C++ compiler:
   
   **Option A: Clang via Homebrew (recommended for Apple Silicon)**
   ```bash
   brew install llvm
   echo 'export PATH="/opt/homebrew/opt/llvm/bin:$PATH"' >> ~/.zshrc
   source ~/.zshrc
   ```

   **Option B: Xcode Command Line Tools**
   ```bash
   xcode-select --install
   ```

2. Install CMake:
   ```bash
   brew install cmake
   ```

### Step 2: Configure GLFW

1. Download GLFW for macOS from [GLFW official website](https://www.glfw.org/download.html)
2. Extract the downloaded package
3. Create necessary directories:
   ```bash
   mkdir -p Dependencies/include
   mkdir -p Dependencies/lib-arm64  # For Apple Silicon
   # OR
   mkdir -p Dependencies/lib-universal  # For Intel Macs
   ```
4. Copy GLFW files:
   - Copy the `include/GLFW` directory to your project's `Dependencies/include/`
   - Copy the appropriate library file based on your Mac's architecture:
     - For Apple Silicon: Copy `lib-arm64/libglfw.3.dylib` to `Dependencies/lib-arm64/`
     - For Intel Macs: Copy `lib-universal/libglfw.3.dylib` to `Dependencies/lib-arm64/`

### Step 3: Build the Project

1. Create the build directory:
   ```bash
   mkdir build
   cd build
   ```

2. Configure with CMake:
   ```bash
   cmake ..
   ```

3. Build the project:
   ```bash
   cmake --build .
   ```

### Step 4: Run the Application

After successful build, execute the application:

```bash
./OpenGLScene
```

## Architecture-Specific Considerations

### Apple Silicon Macs

- Our scripts automatically detect Apple Silicon and utilize the appropriate `lib-arm64` libraries
- OpenGL performance is optimized for the Metal backend used on Apple Silicon
- The configuration ensures compatibility with the ARM64 architecture

### Intel Macs

- On Intel Macs, the scripts use `lib-universal` or `lib-x86_64` libraries
- All OpenGL functionality remains fully compatible

## Troubleshooting

### Common Issues

1. **CMake Not Found**
   - Install CMake: `brew install cmake`

2. **GLFW Not Found**
   - Verify GLFW files are in the correct directories
   - Run `./scripts/setup_dependencies.sh` for guided GLFW setup

3. **No C++ Compiler Found**
   - Install Clang: `brew install llvm`
   - Alternatively, install Xcode Command Line Tools: `xcode-select --install`

4. **Build Errors**
   - Ensure you have a compatible C++ compiler
   - Verify your macOS version meets requirements
   - Confirm all dependencies are correctly installed

5. **Architecture-Specific Issues**
   - Ensure you're using the correct libraries for your Mac's architecture
   - Check your architecture with: `uname -m` (returns "arm64" for Apple Silicon)
   - Our scripts handle this automatically, but manual setup requires selecting appropriate files

6. **Runtime Errors**
   - Verify OpenGL support on your system
   - Ensure GLFW dynamic library is properly accessible

For additional assistance, consult the project's GitHub Issues section or contact the maintainers. 