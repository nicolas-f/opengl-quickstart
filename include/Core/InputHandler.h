#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <functional>

namespace Core {

class Camera;

}

namespace Graphics {
class Light;
class Object;
}

namespace Core {

/**
 * @brief Input handling class for processing keyboard and mouse input
 */
class InputHandler {
public:
    /**
     * @brief Get input handler instance
     */
    static InputHandler& getInstance();
    
    /**
     * @brief Initialize input handling
     * @param window GLFW window pointer
     */
    void initialize(GLFWwindow* window);
    
    /**
     * @brief Set camera control
     * @param camera Camera to control
     */
    void setCamera(Camera* camera);
    
    /**
     * @brief Set object control
     * @param object Object to control
     */
    void setObject(Graphics::Object* object);
    
    /**
     * @brief Set light control
     * @param light Light to control
     */
    void setLight(Graphics::Light* light);
    
    /**
     * @brief Process input
     * @return Name of the last pressed key
     */
    std::string processInput();
    
    /**
     * @brief Key callback function
     */
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    
private:
    // Private constructor and copy constructor for singleton pattern
    InputHandler() : lastKey("None") {}
    InputHandler(const InputHandler&) = delete;
    InputHandler& operator=(const InputHandler&) = delete;
    
    static bool keys[1024];
    Camera* camera = nullptr;
    Graphics::Object* object = nullptr;
    Graphics::Light* light = nullptr;
    std::string lastKey;
};

} // namespace Core 