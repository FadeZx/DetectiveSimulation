#pragma once
#include "UIElement.h"

class UIDraggable : public UIElement {

public:
    UIDraggable(const std::string& name, const std::string& texturePath, UICategory UIcategory, const glm::vec3 position, const glm::vec3 scale)
        : UIElement(name, texturePath, UIcategory, position, scale) {
        // Additional properties specific to buttons


    }


    virtual void OnClick() {

        std::cout << "Button Clicked" << std::endl;

        //DRAG OBJECT HERE 

    }

    void Update(float dt, long frame) override {

        Input& input = Application::GetInput();
        RenderGameObject::Update(dt, frame);

        if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1))
        {

            std::cout << IsClickable() << std::endl;

            mousePos = Application::Get().CursorPos();

            std::cout << "x objpos: " << m_position.x << "y objpos: " << m_position.y << std::endl;

            //IsPointInside(mousePos.x, mousePos.y);
            //std::cout << "button clicked" << std::endl;


            if (IsClickable() && IsPointInside(mousePos.x, mousePos.y)) {

                OnClick();

            }


        }


    }

private:
    glm::vec2 mousePos;


};