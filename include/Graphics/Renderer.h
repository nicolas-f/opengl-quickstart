#pragma once

#include <GLFW/glfw3.h>
#include <vector>

namespace Graphics {

/**
 * @brief Renderer helper singleton class, providing basic rendering functions
 */
class Renderer {
public:
    /**
     * @brief Get renderer instance
     */
    static Renderer& getInstance();
    
    /**
     * @brief Initialize the renderer
     */
    void initialize(int width, int height);
    
    /**
     * @brief Set up perspective projection matrix
     */
    void setupPerspective(float fov, float aspectRatio, float near, float far);
    
    /**
     * @brief Clear screen and prepare for drawing
     */
    void clearScreen(float r = 0.05f, float g = 0.05f, float b = 0.05f, float a = 1.0f);
    
    /**
     * @brief Draw XY plane grid
     */
    void drawXYGrid(float gridSize = 10.0f, int divisions = 20);
    
    /**
     * @brief Draw coordinate axes
     */
    void drawCoordinateAxes(float length = 10.0f);
    
    /**
     * @brief Draw sphere
     * @param radius Sphere radius
     * @param slices Number of horizontal slices
     * @param stacks Number of vertical stacks
     */
    void drawSphere(float radius = 1.0f, int slices = 32, int stacks = 16);
    
    /**
     * @brief Draw line
     * @param x1, y1, z1 Start point coordinates
     * @param x2, y2, z2 End point coordinates
     * @param r, g, b Color
     */
    void drawLine(float x1, float y1, float z1, float x2, float y2, float z2,
                  float r = 1.0f, float g = 1.0f, float b = 1.0f);
    
private:
    // Private constructor and copy constructor for singleton pattern
    Renderer() = default;
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    // Sphere vertex cache
    struct SphereCache {
        int slices;
        int stacks;
        std::vector<float> vertices;
        std::vector<float> normals;
    };

    SphereCache sphereCache;
    
    // Generate sphere vertex data
    void generateSphereData(int slices, int stacks);
};

} // namespace Graphics 