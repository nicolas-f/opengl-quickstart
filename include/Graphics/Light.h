#pragma once

namespace Graphics {

/**
 * @brief Light class for handling lighting effects
 */
class Light {
public:
    /**
     * @brief Create a light source
     * @param posX Light X coordinate
     * @param posY Light Y coordinate
     * @param posZ Light Z coordinate
     */
    Light(float posX = 0.0f, float posY = 8.0f, float posZ = 0.0f);
    
    /**
     * @brief Set light position
     */
    void setPosition(float x, float y, float z);
    
    /**
     * @brief Set light ambient color
     */
    void setAmbient(float r, float g, float b, float a = 1.0f);
    
    /**
     * @brief Set light diffuse color
     */
    void setDiffuse(float r, float g, float b, float a = 1.0f);
    
    /**
     * @brief Set light specular color
     */
    void setSpecular(float r, float g, float b, float a = 1.0f);
    
    /**
     * @brief Set light attenuation coefficients
     */
    void setAttenuation(float constant, float linear, float quadratic);
    
    /**
     * @brief Apply lighting settings to OpenGL
     */
    void apply() const;
    
    /**
     * @brief Draw light source representation (small sphere)
     */
    void draw() const;
    
    /**
     * @brief Get light position
     */
    void getPosition(float& x, float& y, float& z) const;
    
private:
    float posX, posY, posZ;          // Light position
    float ambient[4];                // Ambient color
    float diffuse[4];                // Diffuse color
    float specular[4];               // Specular color
    float constantAttenuation;       // Constant attenuation
    float linearAttenuation;         // Linear attenuation
    float quadraticAttenuation;      // Quadratic attenuation
};

} // namespace Graphics 