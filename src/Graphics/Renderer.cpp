#include "Graphics/Renderer.h"
#include "Utils/MathUtils.h"
#include <cmath>

namespace Graphics {

Renderer& Renderer::getInstance() {
    static Renderer instance;
    return instance;
}

void Renderer::initialize(int width, int height) {
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
}

void Renderer::setupPerspective(float fov, float aspectRatio, float near, float far) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float top = near * std::tan(Utils::toRadians(fov * 0.5f));
    float right = top * aspectRatio;
    glFrustum(-right, right, -top, top, near, far);
    
    glMatrixMode(GL_MODELVIEW);
}

void Renderer::clearScreen(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawXYGrid(float gridSize, int divisions) {
    glDisable(GL_LIGHTING); // Temporarily disable lighting
    
    glBegin(GL_LINES);
    glColor3f(0.5f, 0.5f, 0.5f); // Grey grid
    
    float step = (2.0f * gridSize) / divisions;
    
    // Draw X-axis lines
    for (int i = -divisions/2; i <= divisions/2; i++) {
        if (i == 0) continue; // Skip axis line, we'll draw it separately
        float pos = i * step;
        glVertex3f(pos, 0.0f, -gridSize);
        glVertex3f(pos, 0.0f, gridSize);
    }
    
    // Draw Z-axis lines
    for (int i = -divisions/2; i <= divisions/2; i++) {
        if (i == 0) continue; // Skip axis line, we'll draw it separately
        float pos = i * step;
        glVertex3f(-gridSize, 0.0f, pos);
        glVertex3f(gridSize, 0.0f, pos);
    }
    
    glEnd();
    
    // Don't re-enable lighting here, should be determined by the caller
}

void Renderer::drawCoordinateAxes(float length) {
    glDisable(GL_LIGHTING); // Temporarily disable lighting
    
    // X-axis (red)
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(length, 0.0f, 0.0f); // X points right
    glEnd();
    
    // Draw X-axis arrow
    glPushMatrix();
    glTranslatef(length, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.2f, 0.1f, 0.0f);
    glVertex3f(-0.2f, -0.1f, 0.0f);
    glEnd();
    glPopMatrix();
    
    // Y-axis (green)
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, length, 0.0f); // Y points up
    glEnd();
    
    // Draw Y-axis arrow
    glPushMatrix();
    glTranslatef(0.0f, length, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.2f, 0.0f);
    glVertex3f(-0.1f, -0.2f, 0.0f);
    glEnd();
    glPopMatrix();
    
    // Z-axis (blue)
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, length); // Z points toward viewer
    glEnd();
    
    // Draw Z-axis arrow
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, length);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, 0.1f, -0.2f);
    glVertex3f(-0.1f, 0.1f, -0.2f);
    glEnd();
    glPopMatrix();
    
    // Draw coordinate axis labels
    
    // X-axis label
    glPushMatrix();
    glTranslatef(length + 0.2f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    // Draw "X"
    glVertex3f(-0.2f, -0.2f, 0.0f);
    glVertex3f(0.2f, 0.2f, 0.0f);
    glVertex3f(-0.2f, 0.2f, 0.0f);
    glVertex3f(0.2f, -0.2f, 0.0f);
    glEnd();
    glPopMatrix();
    
    // Y-axis label
    glPushMatrix();
    glTranslatef(0.0f, length + 0.2f, 0.0f);
    glBegin(GL_LINES);
    // Draw "Y"
    glVertex3f(-0.2f, 0.2f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.2f, 0.2f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -0.2f, 0.0f);
    glEnd();
    glPopMatrix();
    
    // Z-axis label
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, length + 0.2f);
    glBegin(GL_LINES);
    // Draw "Z"
    glVertex3f(-0.2f, 0.2f, 0.0f);
    glVertex3f(0.2f, 0.2f, 0.0f);
    glVertex3f(0.2f, 0.2f, 0.0f);
    glVertex3f(-0.2f, -0.2f, 0.0f);
    glVertex3f(-0.2f, -0.2f, 0.0f);
    glVertex3f(0.2f, -0.2f, 0.0f);
    glEnd();
    glPopMatrix();
    
    glLineWidth(1.0f); // Reset line width
    
    // Don't re-enable lighting here, should be determined by the caller
}

void Renderer::generateSphereData(int slices, int stacks) {
    // If we need to generate new sphere data, or update existing data
    if (sphereCache.slices != slices || sphereCache.stacks != stacks || 
        sphereCache.vertices.empty() || sphereCache.normals.empty()) {
        
        sphereCache.slices = slices;
        sphereCache.stacks = stacks;
        sphereCache.vertices.clear();
        sphereCache.normals.clear();
        
        const float PI = 3.14159265358979323846f;
        
        // Generate vertices and normals
        for (int i = 0; i <= stacks; ++i) {
            float phi = PI * (float)i / (float)stacks;
            float sinPhi = std::sin(phi);
            float cosPhi = std::cos(phi);
            
            for (int j = 0; j <= slices; ++j) {
                float theta = 2.0f * PI * (float)j / (float)slices;
                float sinTheta = std::sin(theta);
                float cosTheta = std::cos(theta);
                
                float x = cosTheta * sinPhi;
                float y = cosPhi;
                float z = sinTheta * sinPhi;
                
                // Normal is the position of the point on the unit sphere
                sphereCache.normals.push_back(x);
                sphereCache.normals.push_back(y);
                sphereCache.normals.push_back(z);
                
                // Vertex position is a point with radius 1, will be scaled when drawing
                sphereCache.vertices.push_back(x);
                sphereCache.vertices.push_back(y);
                sphereCache.vertices.push_back(z);
            }
        }
    }
}

void Renderer::drawSphere(float radius, int slices, int stacks) {
    // Generate/update sphere data
    generateSphereData(slices, stacks);
    
    // Draw sphere using triangle strips
    for (int i = 0; i < stacks; ++i) {
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= slices; ++j) {
            int current = i * (slices + 1) + j;
            int next = current + slices + 1;
            
            // Set normal and vertex for the first point
            glNormal3f(
                sphereCache.normals[current * 3],
                sphereCache.normals[current * 3 + 1],
                sphereCache.normals[current * 3 + 2]
            );
            glVertex3f(
                sphereCache.vertices[current * 3] * radius,
                sphereCache.vertices[current * 3 + 1] * radius,
                sphereCache.vertices[current * 3 + 2] * radius
            );
            
            // Set normal and vertex for the second point
            glNormal3f(
                sphereCache.normals[next * 3],
                sphereCache.normals[next * 3 + 1],
                sphereCache.normals[next * 3 + 2]
            );
            glVertex3f(
                sphereCache.vertices[next * 3] * radius,
                sphereCache.vertices[next * 3 + 1] * radius,
                sphereCache.vertices[next * 3 + 2] * radius
            );
        }
        glEnd();
    }
}

void Renderer::drawLine(float x1, float y1, float z1, float x2, float y2, float z2, 
                        float r, float g, float b) {
    // Temporarily disable lighting to draw the line
    bool lightingEnabled = glIsEnabled(GL_LIGHTING);
    if (lightingEnabled) {
        glDisable(GL_LIGHTING);
    }
    
    glColor3f(r, g, b);
    glBegin(GL_LINES);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glEnd();
    
    // If lighting was enabled before, restore it
    if (lightingEnabled) {
        glEnable(GL_LIGHTING);
    }
}

} // namespace Graphics 