#pragma once

#include "../UI/UIElement.h"

class UIDraggable : public UIElement {

public:
    UIDraggable(const std::string& name, const std::string& texturePath, const glm::vec3 position, const glm::vec3 scale)
        : UIElement(name, texturePath, position, scale) {

        //category = UIcategory;
        isDragging = false;

    }


    void OnClick() {

        //DRAG OBJECT HERE 

        std::cout << "Draggable Clicked" << std::endl;
        isDragging = true;


    }

 
    void Update(float dt, long frame) override {

        
        Input& input = Application::GetInput();
        RenderGameObject::Update(dt, frame);

        mousePos = Application::Get().CursorPos();

        if (IsClickable()) {

            //std::cout << "DRAGGABLE CLICK" << std::endl;

            if (IsPointInside(mousePos.x, mousePos.y)) {

               // std::cout << "DRAGGABLE POINT" << std::endl;

                if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {

                    OnClick();
                    isDragging = true;
                    dragStartPos = MousetoScreen(mousePos.x, mousePos.y); // Capture the starting point of the drag
                    dragOffset = glm::vec2(m_position.x, m_position.y) - mousePos; // Offset between mouse and object position

                }

            
            }
        }

        if (input.Get().GetMouseButtonUp(GLFW_MOUSE_BUTTON_1)) {

            isDragging = false;
            std::cout << "DRAGGABLE RELEASED" << std::endl;

        }

        if (isDragging) {

            // Continue drag - Update object position
            glm::vec2 newUiPosition = mousePos + dragOffset; // Apply offset to maintain relative position under cursor

            glm::vec2 convertedPosition = MousetoScreen(newUiPosition.x, newUiPosition.y);
            m_position = glm::vec3(convertedPosition.x, convertedPosition.y, 0.0f);

        }

    }

private:

    glm::vec2 mousePos;
    glm::vec2 dragStartPos;
    bool isDragging;

    glm::vec2 dragOffset; // Offset between

};