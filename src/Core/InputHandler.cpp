#include "Core/InputHandler.h"
#include "Core/Camera.h"
#include "Graphics/Object.h"
#include "Graphics/Light.h"
#include <iostream>

namespace Core {

bool InputHandler::keys[1024] = {0};

InputHandler& InputHandler::getInstance() {
    static InputHandler instance;
    return instance;
}

void InputHandler::initialize(GLFWwindow* window) {
    glfwSetKeyCallback(window, InputHandler::keyCallback);
}

void InputHandler::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
    
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void InputHandler::setCamera(Camera* cam) {
    camera = cam;
}

void InputHandler::setObject(Graphics::Object* obj) {
    object = obj;
}

void InputHandler::setLight(Graphics::Light* l) {
    light = l;
}

std::string InputHandler::processInput() {
    bool moved = false;
    
    if (camera) {
        // Camera movement
        float camX = 0.0f, camY = 0.0f, camZ = 0.0f;
        
        // A: -X (left)
        if (keys[GLFW_KEY_A]) {
            camX -= camera->getSpeed();
            lastKey = "A (-X, left)";
            moved = true;
        }
        // D: +X (right)
        if (keys[GLFW_KEY_D]) {
            camX += camera->getSpeed();
            lastKey = "D (+X, right)";
            moved = true;
        }
        // W: -Z (forward)
        if (keys[GLFW_KEY_W]) {
            camZ -= camera->getSpeed();
            lastKey = "W (-Z, forward)";
            moved = true;
        }
        // S: +Z (backward)
        if (keys[GLFW_KEY_S]) {
            camZ += camera->getSpeed();
            lastKey = "S (+Z, backward)";
            moved = true;
        }
        // Space: +Y (up)
        if (keys[GLFW_KEY_SPACE]) {
            camY += camera->getSpeed();
            lastKey = "Space (+Y, up)";
            moved = true;
        }
        // Shift: -Y (down)
        if (keys[GLFW_KEY_LEFT_SHIFT]) {
            camY -= camera->getSpeed();
            lastKey = "Shift (-Y, down)";
            moved = true;
        }
        
        if (camX != 0.0f || camY != 0.0f || camZ != 0.0f) {
            camera->move(camX, camY, camZ);
        }
    }
    
    if (object) {
        // Object movement
        float objX = 0.0f, objY = 0.0f, objZ = 0.0f;
        
        // J: -X (left)
        if (keys[GLFW_KEY_J]) {
            objX -= object->getSpeed();
            lastKey = "J (-X, object left)";
            moved = true;
        }
        // L: +X (right)
        if (keys[GLFW_KEY_L]) {
            objX += object->getSpeed();
            lastKey = "L (+X, object right)";
            moved = true;
        }
        // I: -Z (forward)
        if (keys[GLFW_KEY_I]) {
            objZ -= object->getSpeed();
            lastKey = "I (-Z, object forward)";
            moved = true;
        }
        // K: +Z (backward)
        if (keys[GLFW_KEY_K]) {
            objZ += object->getSpeed();
            lastKey = "K (+Z, object backward)";
            moved = true;
        }
        
        if (objX != 0.0f || objY != 0.0f || objZ != 0.0f) {
            object->move(objX, objY, objZ);
        }
    }
    
    // Print position information
    if (moved) {
        std::cout << "Key pressed: " << lastKey << std::endl;
        
        if (camera) {
            float camX, camY, camZ;
            camera->getPosition(camX, camY, camZ);
            std::cout << "Camera Position: (" << camX << ", " << camY << ", " << camZ << ")" << std::endl;
        }
        
        if (object) {
            float objX, objY, objZ;
            object->getPosition(objX, objY, objZ);
            std::cout << "Object Position: (" << objX << ", " << objY << ", " << objZ << ")" << std::endl;
        }
        
        if (light) {
            float lightX, lightY, lightZ;
            light->getPosition(lightX, lightY, lightZ);
            std::cout << "Light Position: (" << lightX << ", " << lightY << ", " << lightZ << ")" << std::endl;
        }
        
        std::cout << "------------------------------------------------" << std::endl;
    }
    
    return lastKey;
}

} // namespace Core 