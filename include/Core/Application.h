#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <memory>

namespace Core {
class Camera;
}

namespace Graphics {
class Object;
class Light;
class Renderer;
}

namespace Core {

/**
 * @brief Application class for handling program initialization, main loop and termination
 */
class Application {
public:
    /**
     * @brief Default constructor
     */
    Application();
    
    /**
     * @brief Destructor
     */
    ~Application();
    
    /**
     * @brief Initialize the application
     * @param windowWidth Window width
     * @param windowHeight Window height
     * @param windowTitle Window title
     * @return Whether initialization was successful
     */
    bool initialize(int windowWidth = 800, int windowHeight = 600, 
                   const std::string& windowTitle = "OpenGL 3D Scene");
    
    /**
     * @brief Run the main loop
     */
    void run();
    
private:
    /**
     * @brief Process and display UI
     */
    void drawUI(const std::string& lastKeyPressed);
    
    GLFWwindow* window;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<Graphics::Object> object;
    std::unique_ptr<Graphics::Light> light;
};

} // namespace Core 