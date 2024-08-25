#pragma once
#pragma once

#include "../UI/UIAnimated.h"
#include "../Animation/Animator.h"
#include <iostream>
#include <glm/glm.hpp>
#include "../Application.h"
#include "../Scene/Scene.h"

class BellSoundClue : public UIAnimated {
public:
    BellSoundClue(const std::string& name, const std::string& texturePath,glm::vec3 pos,float row, float col)
        : UIAnimated(name, texturePath,row,col,pos,true), animating(false), isRinging(false), m_name(name)
    {
        m_animator.AddAnimation("bell_ring", 1, 15, 3.0f, Animator::LoopType::Loop, std::bind(&BellSoundClue::onRingComplete, this));
    }

    virtual void Update(float dt, long frame) override {
        UIAnimated::Update(dt, frame);

        if (animating) {
            m_animator.Update(dt);
        }
        else {
            m_animator.SetAnimation("idle");
        }

        // Now get the current frame and row
        int currentFrame = m_animator.GetCurrentFrame();
        int currentRow = m_animator.GetCurrentRow();

        // Debugging output
        //std::cout << "Current Frame: " << currentFrame << std::endl;
       // std::cout << "Current Row: " << currentRow << std::endl;

        // Use the current frame and row for your sprite sheet
        animY = static_cast<float>(currentRow);
        animX = static_cast<float>(currentFrame);
    }

    void startRinging() {
        if (!animating) {
            animating = true;
            currentAnimation = "bell_ring";
            m_animator.SetAnimation(currentAnimation);
           // AudioManager::GetInstance().PlaySound("bellRing", false);
            isRinging = true;
            timerID = Application::Get().SetTimer(2500, [this]() { this->onTimerComplete(); }, false);
            timerActive = true;
        }
    }

    void stopRinging() {
        if (timerActive) {
            Application::Get().CancelTimer(timerID);
            timerActive = false;
        }
        if (isRinging) {
            animating = false;
            isRinging = false;
            currentAnimation = "idle";
            m_animator.SetAnimation(currentAnimation);
            // AudioManager::GetInstance().StopSound("bellRing");
        }
    }

    void setPaused(bool value) {
        paused = value;
    }

    bool wasPaused() const {
        return paused;
    }

    bool isBellRinging() const {
        return isRinging;
    }

    std::string getName()
    {
        return m_name;
    }

private:
    void onRingComplete() {
        if (animating) {
            currentAnimation = "idle";
            m_animator.SetAnimation(currentAnimation);
            animating = false;
        }
    }

    void onTimerComplete() {
        if (isRinging) {
            startRinging();
        }
    }

    bool paused = false;
    std::string m_name;
    Animator m_animator;
    bool animating;
    bool isRinging;
    bool timerActive;
    int timerID;
    std::string currentAnimation;
};
