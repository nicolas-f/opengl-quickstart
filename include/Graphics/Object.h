#pragma once

namespace Graphics {

/**
 * @brief Object class for handling 3D object rendering and properties
 */
class Object {
public:
    /**
     * @brief Create an object
     * @param posX Object X coordinate
     * @param posY Object Y coordinate
     * @param posZ Object Z coordinate
     * @param radius Object radius (for spheres)
     * @param speed Movement speed
     */
    Object(float posX = -2.0f, float posY = 1.0f, float posZ = 0.0f, 
           float radius = 0.8f, float speed = 0.1f);
    
    /**
     * @brief Set object position
     */
    void setPosition(float x, float y, float z);
    
    /**
     * @brief Move object
     */
    void move(float deltaX, float deltaY, float deltaZ);
    
    /**
     * @brief Set rotation angles
     */
    void setRotation(float x, float y, float z);
    
    /**
     * @brief Rotate object by incrementing angles
     */
    void rotate(float x, float y, float z);
    
    /**
     * @brief Apply material properties
     */
    void applyMaterial() const;
    
    /**
     * @brief Set ambient light material
     */
    void setAmbient(float r, float g, float b, float a = 1.0f);
    
    /**
     * @brief Set diffuse light material
     */
    void setDiffuse(float r, float g, float b, float a = 1.0f);
    
    /**
     * @brief Set specular light material
     */
    void setSpecular(float r, float g, float b, float a = 1.0f);
    
    /**
     * @brief Set object shininess
     */
    void setShininess(float value);
    
    /**
     * @brief Draw the object
     */
    void draw() const;
    
    /**
     * @brief Get object position
     */
    void getPosition(float& x, float& y, float& z) const;
    
    /**
     * @brief Get object speed
     */
    float getSpeed() const { return speed; }
    
private:
    float posX, posY, posZ;     // Object position
    float speed;                // Movement speed
    float radius;               // Radius (for spheres)
    float ambient[4];           // Ambient light material
    float diffuse[4];           // Diffuse light material
    float specular[4];          // Specular light material
    float shininess;            // Shininess
    float rotX, rotY, rotZ;     // Rotation angles
};

} // namespace Graphics 