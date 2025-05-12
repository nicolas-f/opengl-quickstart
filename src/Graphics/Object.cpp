#include "Graphics/Object.h"
#include "Graphics/Renderer.h"
#include <GLFW/glfw3.h>

namespace Graphics {

Object::Object(float posX, float posY, float posZ, float radius, float speed)
    : posX(posX), posY(posY), posZ(posZ), speed(speed), radius(radius), shininess(75.0f),
      rotX(0.0f), rotY(0.0f), rotZ(0.0f) {
    
    // Set default material properties
    ambient[0] = 0.05f;  // Rich green with darker ambient for depth
    ambient[1] = 0.15f;
    ambient[2] = 0.05f;
    ambient[3] = 1.0f;
    
    diffuse[0] = 0.1f;   // Strong but natural green for diffuse reflection
    diffuse[1] = 0.6f;
    diffuse[2] = 0.1f;
    diffuse[3] = 1.0f;
    
    specular[0] = 0.9f;  // Slightly greenish highlights
    specular[1] = 1.0f;
    specular[2] = 0.9f;
    specular[3] = 1.0f;
}

void Object::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

void Object::move(float deltaX, float deltaY, float deltaZ) {
    posX += deltaX;
    posY += deltaY;
    posZ += deltaZ;
}

void Object::setAmbient(float r, float g, float b, float a) {
    ambient[0] = r;
    ambient[1] = g;
    ambient[2] = b;
    ambient[3] = a;
}

void Object::setDiffuse(float r, float g, float b, float a) {
    diffuse[0] = r;
    diffuse[1] = g;
    diffuse[2] = b;
    diffuse[3] = a;
}

void Object::setSpecular(float r, float g, float b, float a) {
    specular[0] = r;
    specular[1] = g;
    specular[2] = b;
    specular[3] = a;
}

void Object::setShininess(float value) {
    shininess = value;
}

void Object::setRotation(float x, float y, float z) {
    rotX = x;
    rotY = y;
    rotZ = z;
}

void Object::rotate(float x, float y, float z) {
    rotX += x;
    rotY += y;
    rotZ += z;
}

void Object::applyMaterial() const {
    // Apply material properties to the current rendering context
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

void Object::draw() const {
    glPushMatrix();
    
    // Move to object position
    glTranslatef(posX, posY, posZ);
    
    // Apply rotation
    glRotatef(rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotZ, 0.0f, 0.0f, 1.0f);
    
    // Apply material properties
    applyMaterial();
    
    // Draw sphere using renderer
    Renderer::getInstance().drawSphere(radius, 32, 32);
    
    glPopMatrix();
}

void Object::getPosition(float& x, float& y, float& z) const {
    x = posX;
    y = posY;
    z = posZ;
}

} // namespace Graphics 