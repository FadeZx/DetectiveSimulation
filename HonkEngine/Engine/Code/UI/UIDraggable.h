#pragma once

#include "../GameObjects/RenderGameObject.h"
#include <glm/glm.hpp>
#include"../Scene/Scene.h"
#include "../Input/Input.h"
#include <iostream>
#include "../GameObjects/GameObject.h"
#include "../Engine.h"
#include "../Application.h"

class UIDraggable : public RenderGameObject {

public:
    UIDraggable(const std::string& name, const std::string& texturePath, const glm::vec3 position, const glm::vec3 scale)
        : RenderGameObject(name, texturePath, position) {

        m_scale = scale;
        button_name = name;
        isClickable = true;
        //category = UIcategory;
        isDragging = false;

    }

    bool IsClickable() {
        return isClickable;
    }

    void SetClickable(bool clickable) {
        isClickable = clickable;
    }

    bool IsPointInside(float x, float y) const {

        float xpos = x - (SCR_WIDTH / 2.0f);
        float ypos = y - (SCR_HEIGHT / 2.0f);

        xpos = xpos / (SCR_WIDTH / (8 * 2)); //TEMPORARY FIX
        ypos = ypos / (SCR_HEIGHT / (4.5 * 2)) * -1; //TEMPORARY FIX

        float minX = m_position.x - (m_scale.x / 2.0f);
        float maxX = m_position.x + (m_scale.x / 2.0f);
        float minY = m_position.y - (m_scale.y / 2.0f);
        float maxY = m_position.y + (m_scale.y / 2.0f);

        //std::cout << "maxX: " << maxX << " minX: " << minX << std::endl;
        //std::cout << "maxY: " << maxY << " minY: " << minY << std::endl;


        std::cout << "x: " << x << " y: " << y << std::endl;
        std::cout << "new xpos: " << xpos << " new ypos: " << ypos << std::endl;
        std::cout << "obj x: " << m_position.x << "obj y: " << m_position.y << std::endl;
        std::cout << "maxX: " << maxX << " minX: " << minX << std::endl;
        std::cout << "maxY: " << maxY << " minY: " << minY << std::endl;

        return (xpos >= minX && xpos <= maxX && ypos >= minY && ypos <= maxY);

    }

    void OnClick() {

        //std::cout << "Button Clicked" << std::endl;

        //DRAG OBJECT HERE 

        std::cout << "Draggable Clicked" << std::endl;
        isDragging = true;
        //dragStartPos = ScreenToUIPosition(mousePos);

    }

 
    void Update(float dt, long frame) override {

        
        Input& input = Application::GetInput();
        RenderGameObject::Update(dt, frame);

        if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1))
        {

            mousePos = Application::Get().CursorPos();

            if (IsClickable() && IsPointInside(mousePos.x, mousePos.y)) {
          
                OnClick();

            }

        }


    }

private:

    std::string button_name;
    glm::vec2 mousePos;
    glm::vec2 dragStartPos;
    bool isDragging;
    bool isClickable;

    glm::vec2 ScreenToUIPosition(const glm::vec2& screenPos) const {
        // Convert screen coordinates to UI coordinates
        float uiX = (screenPos.x - SCR_WIDTH / 2.0f) / (SCR_WIDTH / (16 * 2));
        float uiY = (SCR_HEIGHT / 2.0f - screenPos.y) / (SCR_HEIGHT / (9 * 2)) * -1;
        return glm::vec2(uiX, uiY);
    }

};