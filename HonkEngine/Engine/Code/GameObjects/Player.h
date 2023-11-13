#pragma once
#pragma once

#include "AnimateGameObject.h"
#include "Engine.h"
#include <glm/glm.hpp>
#include "Application.h"
#include"../Scene/Scene.h"
#include "../Input/Input.h"
#include <iostream>
#include"GameObject.h"
#include "../Animation/Animator.h" 



class Player : public AnimateGameObject
{
public:
	Player(const std::string& name, const std::string& texturePath,int p_row,int p_col)
		:AnimateGameObject(name, texturePath, p_row, p_col),audioManager(AudioManager::GetInstance())
	{
		m_scale = glm::vec3(4.5f, 3.5f, 0.0f);
	    m_animator.AddAnimation("walk", 1, 8, 7.5f, Animator::LoopType::Loop, []() {});
        audioManager.LoadSound("Player_footsteps","Assets/Sounds/footstep.mp3",3.0f);
	}
	
void Update(float dt, long frame) override
{
    Input& input = Application::GetInput();
    AnimateGameObject::Update(dt, frame);

    // Initialize to a default or idle animation
    std::string currentAnimation = "idle"; 
    bool isWalking = false;

    
    if (input.Get().GetKey(GLFW_KEY_A))
    {
        isWalking = true;
       // audioManager.PlaySound("Player_footsteps",true);
        m_position.x -= speed * dt;
        if (m_scale.x > 0) m_scale.x *= -1.0f;
        currentAnimation = "walk";
    }
    if (input.Get().GetKey(GLFW_KEY_D))
    {
        isWalking = true;
       // audioManager.PlaySound("Player_footsteps",true);
        m_position.x += speed * dt;
        if (m_scale.x < 0) m_scale.x *= -1.0f;
        currentAnimation = "walk";
    }
    if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1))
    {

        Application::Get().GetCurrentScene()->AddGameObject(new RenderGameObject("Boss", "Assets/Images/awesomeface.png",m_position));

     
    }
    if (m_position.x > GetWindowWidth() / 2.0f)
    {
        // If the player's x-position is greater than half the window's width, change the scene
        Application::Get().SetScene("Room1");
    }
    // You might also want to check for other directions, for example:
    else if (m_position.x < -GetWindowWidth() / 2.0f)
    {

        Application::Get().SetScene("Room2");
    }
    // Set the animation
    m_animator.SetAnimation(currentAnimation);

    // Then update the animator
    m_animator.Update(dt);

    // Now get the current frame and row
    int currentFrame = m_animator.GetCurrentFrame();
    int currentRow = m_animator.GetCurrentRow();

    // Use the current frame and row for your sprite sheet
    animY = static_cast<float>(currentRow);
    animX = static_cast<float>(currentFrame);

    if (isWalking && !audioManager.IsSoundPlaying("Player_footsteps")) {
        audioManager.PlaySound("Player_footsteps", true);
    }
    else if (!isWalking && audioManager.IsSoundPlaying("Player_footsteps")) {
        audioManager.StopSound("Player_footsteps");
    }
}



private:
	float speed = 5.0f;
	glm::vec2 mousePos;
	Animator m_animator;
    AudioManager& audioManager;
};