#pragma once

#include "BellSoundClue.h"
#include "BellManager.h"
#include "../Camera/Camera.h"
#include <glm/glm.hpp>

class BellSoundClueManager {
public:
    BellSoundClueManager(BellSoundClue* leftClue, BellSoundClue* rightClue)
        : m_leftClue(leftClue), m_rightClue(rightClue) 
    {
        m_leftClue->setActiveStatus(false);
        m_rightClue->setActiveStatus(false);
    }

    void Update(float dt, long frame) {
        bool isAnyBellRinging = BellManager::GetInstance().isAnyBellRinging();
        bool leftClueActive = false;
        bool rightClueActive = false;

        if (isAnyBellRinging) {
            float leftBoundary = m_camera.GetLeftBoundary();
            float rightBoundary = m_camera.GetRightBoundary();

            for (auto* bell : BellManager::GetInstance().GetAllBells()) {
                if (bell->isBellRinging()) {
                    glm::vec3 bellPosition = bell->GetPosition();

                    if (bellPosition.x < leftBoundary) { // Bell is outside on the left
                        m_leftClue->startRinging();
                        leftClueActive = true;
                        m_leftClue->setActiveStatus(true);
                    }
                    else if (bellPosition.x > rightBoundary) { // Bell is outside on the right
                        m_rightClue->startRinging();
                        rightClueActive = true;
                        m_rightClue->setActiveStatus(true);
                    }
                }
            }
        }

        // Stop the clues if no bell is ringing on their side
        if (!leftClueActive) {
            m_leftClue->stopRinging();
            m_leftClue->setActiveStatus(false);
        }
        if (!rightClueActive) {
            m_rightClue->stopRinging();
            m_rightClue->setActiveStatus(false);
        }

        // Update the clues' animations
        m_leftClue->Update(dt, frame);
        m_rightClue->Update(dt, frame);
    }

private:
    BellSoundClue* m_leftClue;
    BellSoundClue* m_rightClue;
    Camera& m_camera = Application::GetCamera();  // Add camera reference
};

