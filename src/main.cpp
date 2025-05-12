#include "Core/Application.h"

/**
 * @brief Program entry point
 */
int main() {
    Core::Application app;
    
    if (app.initialize(800, 600, "OpenGL 3D Scene with Lighting")) {
        app.run();
    }
    
    return 0;
} 