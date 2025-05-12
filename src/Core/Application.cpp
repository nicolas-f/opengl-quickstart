#include "Core/Application.h"
#include "Core/Camera.h"
#include "Core/InputHandler.h"
#include "Graphics/Object.h"
#include "Graphics/Light.h"
#include "Graphics/Renderer.h"
#include "Utils/MathUtils.h"

#include <iostream>

namespace Core {

Application::Application() : window(nullptr) {
}

Application::~Application() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

bool Application::initialize(int windowWidth, int windowHeight, const std::string& windowTitle) {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    
    // Create window
    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    
    // Set current context
    glfwMakeContextCurrent(window);
    
    // Initialize input handler
    InputHandler::getInstance().initialize(window);
    
    // Initialize renderer
    auto& renderer = Graphics::Renderer::getInstance();
    renderer.initialize(windowWidth, windowHeight);
    renderer.setupPerspective(45.0f, static_cast<float>(windowWidth) / windowHeight, 0.1f, 100.0f);
    
    // Create camera and objects
    camera = std::make_unique<Camera>(0.0f, 2.0f, 6.0f);

    // Create object, adjust position
    object = std::make_unique<Graphics::Object>(-2.0f, 1.0f, 1.0f, 1.0f);

    // Set light source position at (0, 8, 0)
    light = std::make_unique<Graphics::Light>(0.0f, 8.0f, 0.0f);
    
    // Set input control objects
    auto& inputHandler = InputHandler::getInstance();
    inputHandler.setCamera(camera.get());
    inputHandler.setObject(object.get());
    inputHandler.setLight(light.get());
    
    // Print initial positions
    std::cout << "Initial camera position: (0.0, 2.0, 6.0)" << std::endl;
    std::cout << "Initial object position: (-2.0, 1.0, 1.0)" << std::endl;
    std::cout << "Initial light position: (0.0, 8.0, 0.0)" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    
    // Print control instructions
    std::cout << "Controls:" << std::endl;
    std::cout << "A - Move camera left (-X)" << std::endl;
    std::cout << "D - Move camera right (+X)" << std::endl;
    std::cout << "W - Move camera forward (-Z)" << std::endl;
    std::cout << "S - Move camera backward (+Z)" << std::endl;
    std::cout << "Space - Move camera up (+Y)" << std::endl;
    std::cout << "Shift - Move camera down (-Y)" << std::endl;
    std::cout << "J - Move object left (-X)" << std::endl;
    std::cout << "L - Move object right (+X)" << std::endl;
    std::cout << "I - Move object forward (-Z)" << std::endl;
    std::cout << "K - Move object backward (+Z)" << std::endl;
    std::cout << "Q - Exit application" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    
    return true;
}

void Application::run() {
    auto& renderer = Graphics::Renderer::getInstance();
    auto& inputHandler = InputHandler::getInstance();
    
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Process input
        std::string lastKeyPressed = inputHandler.processInput();
        
        // Clear screen and set background color
        renderer.clearScreen(0.05f, 0.05f, 0.05f);
        
        // Set camera view
        camera->applyViewTransform();
        
        // Disable lighting to draw grid and axes
        glDisable(GL_LIGHTING);
        
        // Draw the XY grid and coordinate axes
        renderer.drawXYGrid();
        renderer.drawCoordinateAxes();
        
        // Draw connection line between camera and object
        float camX, camY, camZ;
        float objX, objY, objZ;
        camera->getPosition(camX, camY, camZ);
        object->getPosition(objX, objY, objZ);
        renderer.drawLine(camX, camY, camZ, objX, objY, objZ, 1.0f, 0.0f, 0.0f);
        
        // Enable lighting and set up
        glEnable(GL_LIGHTING);
        light->apply();
        
        // Draw light source
        light->draw();
        
        // Draw object (with lighting)
        object->draw();
        
        // Draw UI and information
        drawUI(lastKeyPressed);
        
        // Swap buffers and process events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Application::drawUI(const std::string& lastKeyPressed) {
    // UI drawing code omitted as we decided not to use text rendering
    // Position information is output directly through the console
}

} // namespace Core 