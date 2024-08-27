#pragma once

#include "../UI/UIAnimated.h"
#include "../Animation/Animator.h"
#include <iostream>
#include <glm/glm.hpp>
#include "../Application.h"
#include "../Scene/Scene.h"

class BellSoundClue : public UIAnimated {
public:
    BellSoundClue(const std::string& name, const std::string& texturePath, glm::vec3 pos, float row, float col)
        : UIAnimated(name, texturePath, row, col, pos, true), m_name(name) {}

    virtual void Update(float dt, long frame) override {
        UIAnimated::Update(dt, frame);
        // The frame and row will be updated by the manager based on the bell's animation
    }

    void setFrameAndRow(int frame, int row) {
        animX = static_cast<float>(frame);
        animY = static_cast<float>(row);
    }

    std::string getName() const {
        return m_name;
    }

private:
    std::string m_name;
};
