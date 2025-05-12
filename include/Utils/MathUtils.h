#pragma once

#include <cmath>

namespace Utils {

// Convert degrees to radians
inline float toRadians(float degrees) {
    return degrees * 0.01745329251f; // PI/180
}

// Convert radians to degrees
inline float toDegrees(float radians) {
    return radians * 57.29577951f; // 180/PI
}

// Normalize vector
inline void normalize(float& x, float& y, float& z) {
    float length = std::sqrt(x * x + y * y + z * z);
    if (length > 0.0001f) {
        x /= length;
        y /= length;
        z /= length;
    }
}

// Vector cross product
inline void crossProduct(
    float x1, float y1, float z1, 
    float x2, float y2, float z2, 
    float& outX, float& outY, float& outZ) {
    
    outX = y1 * z2 - z1 * y2;
    outY = z1 * x2 - x1 * z2;
    outZ = x1 * y2 - y1 * x2;
}

} // namespace Utils 