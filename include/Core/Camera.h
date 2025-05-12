#pragma once

namespace Core {

/**
 * @brief Camera class for handling view and projection transformations
 */
class Camera {
public:
    /**
     * @brief Create a camera
     * @param posX Camera X coordinate
     * @param posY Camera Y coordinate
     * @param posZ Camera Z coordinate
     * @param speed Movement speed
     */
    Camera(float posX = 0.0f, float posY = 2.0f, float posZ = 6.0f, float speed = 0.1f);
    
    /**
     * @brief Set camera position
     */
    void setPosition(float x, float y, float z);
    
    /**
     * @brief Move the camera
     */
    void move(float deltaX, float deltaY, float deltaZ);
    
    /**
     * @brief Apply camera transformation
     */
    void applyViewTransform();
    
    /**
     * @brief Get camera position
     */
    void getPosition(float& x, float& y, float& z) const;
    
    /**
     * @brief Get camera speed
     */
    float getSpeed() const { return speed; }
    
private:
    float posX, posY, posZ;  // Camera position
    float speed;             // Movement speed
};

} // namespace Core 