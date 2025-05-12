#include "Core/Camera.h"
#include "Utils/MathUtils.h"
#include <GLFW/glfw3.h>
#include <cmath>

namespace Core {

Camera::Camera(float posX, float posY, float posZ, float speed)
    : posX(posX), posY(posY), posZ(posZ), speed(speed) {
}

void Camera::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

void Camera::move(float deltaX, float deltaY, float deltaZ) {
    posX += deltaX;
    posY += deltaY;
    posZ += deltaZ;
}

void Camera::applyViewTransform() {
    // Set up camera view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Use simple transformations to simulate the camera
    // First move the camera back to position it at the specified position
    glTranslatef(-posX, -posY, -posZ);
}

void Camera::getPosition(float& x, float& y, float& z) const {
    x = posX;
    y = posY;
    z = posZ;
}

} // namespace Core 