#pragma once
#include "../GameObjects/RenderGameObject.h"
#include <glm/glm.hpp>
#include"../Scene/Scene.h"
#include "../Input/Input.h"
#include <iostream>
#include "../GameObjects/GameObject.h"
#include "../Engine.h"
#include "../Application.h"

class UIButton : public RenderGameObject {

	public:
        UIButton(const std::string& name, const std::string& texturePath, const glm::vec3 position, const glm::vec3 scale)
            : RenderGameObject(name, texturePath, position) {
            // Additional properties specific to buttons

            m_scale = scale;
            button_name = name;
            isClickable = true;
            //category = UIcategory;

        }


        void OnClick(){

            std::cout << "Button Clicked" << std::endl;
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

			xpos = xpos / (SCR_WIDTH / (8 * 2)) - 0.4f; //TEMPORARY FIX
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


        void Update(float dt, long frame) override {

            Input& input = Application::GetInput();
            RenderGameObject::Update(dt, frame);

            if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1))
            {

                //std::cout << IsClickable() << std::endl;
                mousePos = Application::Get().CursorPos();

                if (IsClickable() && IsPointInside(mousePos.x, mousePos.y)) {

                    OnClick();

                }
            }

        }

        

    private:

        std::string button_name;
        bool isClickable;
        //UICategory category;
        glm::vec2 mousePos;


};