#pragma once

#include "../Application.h"
#include "../GameObjects/GameObject.h"
#include <glm/gtc/matrix_transform.hpp> // Include for glm::ortho

class UIScreenObject : public GameObject {
public:
    UIScreenObject(const std::string& name, const std::string& texturePath, const glm::vec2& position, const glm::vec2& size)
        : GameObject(name) {
        // Setup vertices, texture loading remains the same
        // ...

        // Convert position and size from pixel coordinates to NDC
        float ndcX = (position.x / SCR_WIDTH) * 2.0f - 1.0f;
        float ndcY = (position.y / SCR_HEIGHT) * 2.0f - 1.0f;
        float ndcWidth = (size.x / SCR_WIDTH) * 2.0f;
        float ndcHeight = (size.y / SCR_HEIGHT) * 2.0f;

        // Adjust the vertices based on ndcX, ndcY, ndcWidth, and ndcHeight
        // Remember to adjust for aspect ratio if necessary
    }

    virtual void Render() override {
        Renderer& renderer = Application::GetRenderer();

        Renderer& renderer = Application::GetRenderer();
        Shader& shader = renderer.GetShader(); // Assuming you have a method to get the current shader

        // Set uniforms
        shader.use();
        shader.SetInt("tex1", 0); // Texture unit
        shader.SetMatrix4("MVP", glm::mat4(1.0f)); // Identity matrix or orthographic projection if needed

        // Bind texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_Id);

        // Render mesh
        glBindVertexArray(meshVao);
        glDrawArrays(GL_TRIANGLES, 0, 6); // Assuming a simple quad
    }

    // Other methods remain unchanged
private:
    GLuint texture_Id;
    GLuint meshVao;
};
