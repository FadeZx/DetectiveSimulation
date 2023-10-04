#pragma once
#pragma once

#include "AnimateGameObject.h"
#include "Engine.h"
#include <glm/glm.hpp>
#include "Application.h"
#include"Scene.h"
#include "Input.h"
#include <iostream>
#include"GameObject.h"
#include "Animator.h"


class Player : public AnimateGameObject
{
public:
	Player(const std::string& name, const std::string& texturePath,int p_row,int p_col)
		:AnimateGameObject(name, texturePath,4.0f,4.0f)
	{
		m_scale = glm::vec3(1.0f, 1.0f, 0.0f);
		
	}
	
	 void Update(float dt,long frame) override
	{

		//std::cout << "frame" << frame << std::endl;

		 //std::cout<< "x: " << m_position.x << " y: " << m_position.y << " z: " << m_position.z << std::endl;	
		 Input& input = Application::GetInput();
		AnimateGameObject::Update(dt, frame);
       
        if (input.Get().GetKey(GLFW_KEY_A))
        {
            m_position.x -= speed * dt;
			animY = 3.0f;
			if (frame % 5 == 0)
			{
				animX += 1.0f;
				if (animX > 4.0f)
				{
					animX = 0.0f;
				}
			}
           
        }
         if (input.Get().GetKey(GLFW_KEY_D))
        {
            m_position.x += speed * dt;
			animY = 2.0f;
			if (frame % 5 == 0)
			{
				animX += 1.0f;
				if (animX > 4.0f)
				{
					animX = 0.0f;
				}
			}
           
        }
		 if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1))
		 {
			 mousePos = Application::Get().CursorPos();
			 Application::Get().GetCurrentScene()->AddGameObject(new RenderGameObject("Konrai", "Assets/Images/konrai.jpg"));


			 std::cout << "x: " << mousePos.x << " y: " << mousePos.y << std::endl;
		 }
		if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_2))
		{
			Application::Get().SetScene("room1");
		}

		
	}



private:
	float speed = 5.0f;
    int frameCounter = 0;
    static const int framesPerCycle = 30;
	glm::vec2 mousePos;
};