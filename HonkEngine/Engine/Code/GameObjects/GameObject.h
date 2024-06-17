#pragma once

#include <string>
#include "glm/glm.hpp"

class GameObject {
public:
    GameObject(const std::string& name = "", const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f))
        : m_name(name), m_position(position), m_scale(scale),
        originalPosition(position), originalScale(scale) {}

    virtual void Update(float dt, long frame) {}

    virtual void Render() {}

    virtual void Clear() {}

    virtual void SetPosition(const glm::vec3& newPos) {
        m_position = newPos;
        if (!initialized) {
            originalPosition = newPos;
            initialized = true;
        }
    }

    virtual void SetScale(const glm::vec3& scale) {
        m_scale = scale;
        if (!initialized) {
            originalScale = scale;
            initialized = true;
        }
    }

    virtual void SetOrientation(float orientation) {
        m_orientation = orientation;
    }

    virtual void SetLayer(int layer) {
        this->layer = layer;
    }

    virtual glm::vec3 GetPosition() const { return m_position; }

    virtual glm::vec3 GetScale() const { return m_scale; }

    virtual float GetOrientation() const { return m_orientation; }

    virtual int GetLayer() const { return layer; }

    virtual std::string GetName() const {
        return m_name;
    }

    virtual void setActiveStatus(bool status) { active = status; }

    virtual bool getActiveStatus() const { return active; }

    // Update position and scale based on new window dimensions
    // Update position and scale based on new window dimensions
    virtual void Resize(float windowWidth, float windowHeight) {
        float scaleX = windowWidth / initialWindowWidth;
        float scaleY = windowHeight / initialWindowHeight;

        // Optionally, to maintain aspect ratio:
        float uniformScale = std::min(scaleX, scaleY);
        scaleX = scaleY = uniformScale;

        SetPosition(glm::vec3(originalPosition.x * scaleX, originalPosition.y * scaleY, originalPosition.z));
        SetScale(glm::vec3(originalScale.x * scaleX, originalScale.y * scaleY, originalScale.z));
    }




protected:
    std::string m_name;
    glm::vec3 m_position;
    glm::vec3 m_scale;
    glm::vec3 originalPosition;
    glm::vec3 originalScale;
    float initialWindowWidth = 1920.0f; // Default width, should be set during initialization
    float initialWindowHeight = 1080.0f; // Default height, should be set during initialization
    int layer = 0;
    float m_orientation = 0.0f;
    bool active = true;
    bool initialized = false;
};
