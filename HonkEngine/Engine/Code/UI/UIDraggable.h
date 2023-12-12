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

                }

                //if button up
                //isDragging false

            }
        }


        //if isdragging true

    }

private:

    glm::vec2 mousePos;
    glm::vec2 dragStartPos;
    bool isDragging;

};