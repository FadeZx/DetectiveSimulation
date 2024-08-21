#pragma once
#pragma once

#include "BellSoundClue.h"
#include "BellManager.h"
#include <glm/glm.hpp>

class BellSoundClueManager {
public:
    BellSoundClueManager(BellSoundClue* leftClue, BellSoundClue* rightClue)
        : m_leftClue(leftClue), m_rightClue(rightClue) {}

    void Update(float dt, long frame) {
        bool isAnyBellRinging = BellManager::GetInstance().isAnyBellRinging();
        bool leftClueActive = false;
        bool rightClueActive = false;

        if (isAnyBellRinging) {
            for (auto* bell : BellManager::GetInstance().GetAllBells()) {
                if (bell->isBellRinging()) {
                    glm::vec3 bellPosition = bell->GetPosition();

                    if (bellPosition.x < 0.0f) { // Assuming 0 is the middle of the screen
                        m_leftClue->startRinging();
                        leftClueActive = true;
                    }
                    else if (bellPosition.x > 0.0f) {
                        m_rightClue->startRinging();
                        rightClueActive = true;
                    }
                }
            }
        }

        // Stop the clues if no bell is ringing on their side
        if (!leftClueActive) {
            m_leftClue->stopRinging();
        }
        if (!rightClueActive) {
            m_rightClue->stopRinging();
        }

        // Update the clues' animations
        m_leftClue->Update(dt, frame);
        m_rightClue->Update(dt, frame);
    }

private:
    BellSoundClue* m_leftClue;
    BellSoundClue* m_rightClue;
};
