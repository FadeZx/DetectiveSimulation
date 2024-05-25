#pragma once

#include "AnimateGameObject.h"
#include "../Engine.h"
#include <glm/glm.hpp>
#include "../Application.h"
#include"../Scene/Scene.h"
#include "../Input/Input.h"
#include <iostream>
#include"GameObject.h"
#include "../Animation/Animator.h" 
#include "../Audio/AudioManager.h"
#include "../Scene/Hallway.h"
#include "../GameObjects/Book.h"


class Player : public AnimateGameObject
{
    bool canMove = true;
    Book* m_journal;
public:
    Player(const std::string& name, const std::string& texturePath, int p_row, int p_col, Book* journal,float speed)
        : AnimateGameObject(name, texturePath, p_row, p_col), m_journal(journal),speed(speed), audioManager(AudioManager::GetInstance())
    {
        m_scale = glm::vec3(6.1f, 6.1f, 0.0f);
        m_position = glm::vec3(0.0f, -0.9f, 0.0f);
        m_animator.AddAnimation("walk_left", 2, 8, 8.0f, Animator::LoopType::Loop, []() {});
        m_animator.AddAnimation("walk_right", 1, 8, 8.0f, Animator::LoopType::Loop, []() {});
        audioManager.LoadSound("Player_footsteps", "Assets/Sounds/footstep.mp3",SFX, 0.65f);
    }

    void StopMovement() {
        canMove = false;
        audioManager.StopSound("Player_footsteps");
    }

    void ResumeMovement() {
        canMove = true;
    }

    void Update(float dt, long frame) override
    {
        Input& input = Application::GetInput();
        AnimateGameObject::Update(dt, frame);
         

        // Initialize to a default or idle animation
        std::string currentAnimation = "idle";
        bool isWalking = false;

        const float leftBound = -20.52f;
        const float rightBound = 21.0f;

        if (input.Get().GetKey(GLFW_KEY_A) && canMove)
        {
            isWalking = true;
            float newPos = m_position.x - speed * dt;
            m_position.x = std::max(newPos, leftBound); // Ensure player doesn't move past left bound
            currentAnimation = "walk_left";
        }
        if (input.Get().GetKey(GLFW_KEY_D) && canMove)
        {
            isWalking = true;
            float newPos = m_position.x + speed * dt;
            m_position.x = std::min(newPos, rightBound); // Ensure player doesn't move past right bound
            currentAnimation = "walk_right";
        }
        if (input.Get().GetKeyDown(GLFW_KEY_TAB)) {

            if (m_journal->isOpen()) {
                if (!JournalData::GetInstance()->GetBookState()) { //If book is not locked
                    m_journal->closeBook();
                }
            }
            else {
                m_journal->drawBook();
            }
        }


        //test journal entry scene
       /*if (input.Get().GetKeyDown(GLFW_KEY_J)) {
            Application::Get().SetScene("JournalEntry");
       }*/

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

        if (isWalking && Application::Get().GetCurrentSceneName() == ("Hallway")) {
            if (!audioManager.IsSoundPlaying("Player_footsteps")) {
                audioManager.PlaySound("Player_footsteps", true);
                //std::cout << "Playing sound" << std::endl;
            }
        }
        else {
            if (audioManager.IsSoundPlaying("Player_footsteps")) {
                audioManager.StopSound("Player_footsteps");
            }
        }


        glm::vec2 mosePos = Application::Get().MousetoWorld();

    }



private:

    float speed = 6.0f;
    glm::vec2 mousePos;
    Animator m_animator;
    AudioManager& audioManager;
    

};