#include "Graphics/Light.h"
#include "Graphics/Renderer.h"
#include <GLFW/glfw3.h>

namespace Graphics {

Light::Light(float posX, float posY, float posZ)
    : posX(posX), posY(posY), posZ(posZ),
      constantAttenuation(0.5f),    // Increase constant attenuation, more focused lighting
      linearAttenuation(0.02f),     // Moderate linear attenuation
      quadraticAttenuation(0.005f)  // Slightly stronger quadratic attenuation for more realistic light falloff
{
    // Set default lighting parameters
    ambient[0] = 0.2f;  // Lower ambient intensity for more pronounced shadows
    ambient[1] = 0.2f;
    ambient[2] = 0.2f;
    ambient[3] = 1.0f;
    
    // Enhanced diffuse lighting, brighter
    diffuse[0] = 1.0f;
    diffuse[1] = 0.97f; // Slightly warm tint
    diffuse[2] = 0.85f;
    diffuse[3] = 1.0f;
    
    // Enhanced specular highlights
    specular[0] = 1.0f;
    specular[1] = 1.0f;
    specular[2] = 1.0f;
    specular[3] = 1.0f;
}

void Light::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

void Light::setAmbient(float r, float g, float b, float a) {
    ambient[0] = r;
    ambient[1] = g;
    ambient[2] = b;
    ambient[3] = a;
}

void Light::setDiffuse(float r, float g, float b, float a) {
    diffuse[0] = r;
    diffuse[1] = g;
    diffuse[2] = b;
    diffuse[3] = a;
}

void Light::setSpecular(float r, float g, float b, float a) {
    specular[0] = r;
    specular[1] = g;
    specular[2] = b;
    specular[3] = a;
}

void Light::setAttenuation(float constant, float linear, float quadratic) {
    constantAttenuation = constant;
    linearAttenuation = linear;
    quadraticAttenuation = quadratic;
}

void Light::apply() const {
    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    // Set light properties
    float lightPos[4] = {posX, posY, posZ, 1.0f}; // Positional light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    
    // Set light attenuation
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, constantAttenuation);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, linearAttenuation);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
    
    // Enable two-sided lighting for back faces
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    
    // Set global ambient light to prevent the scene from being too dark
    float globalAmbient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
    
    // Enable per-vertex color material for faster color changes
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    // Enable normal normalization for proper lighting calculations
    glEnable(GL_NORMALIZE);
    
    // Enable smooth shading
    glShadeModel(GL_SMOOTH);
}

void Light::draw() const {
    // Draw light source representation (small sphere)
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    
    // Temporarily disable lighting to draw the light source
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow for light source
    
    // Use renderer to draw a sphere
    Renderer::getInstance().drawSphere(0.2f, 16, 16);
    
    // Restore lighting
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void Light::getPosition(float& x, float& y, float& z) const {
    x = posX;
    y = posY;
    z = posZ;
}

} // namespace Graphics 