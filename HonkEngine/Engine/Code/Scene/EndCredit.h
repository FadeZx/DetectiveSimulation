#pragma once

#include "Scene.h"
#include "../UI/UINormal.h"  
#include "../UI/UIButton.h"  
#include "../UI/UIElement.h"  
#include "../Input/Input.h"
#include "../Engine.h"
#include <glm/glm.hpp>
#include <iostream>
#include "../Dialogue/Dialoguemanager.h"
#include "../Effects/ObjectsParallax.h"
#include "../Effects/BackgroundParallax.h"
#include "../GameObjects/Timer.h"
#include "../GameStateManager.h"
#include <memory>
#include "../GameObjects/CharacterData.h"
#include "../Effects/TransitionEffects.h"
#include "../PopupWidget/PauseMenu.h"
#include "../GameObjects/RenderGameObject.h"

class EndCredit : public Scene {
private:
    AudioManager& audioManager;
    std::vector<UIObject*> creditsImages;
    std::unique_ptr<TransitionEffects> transitionEffects;
    UIElement* transitionObject;
    UIButton* ContinueButton;
    int currentImageIndex = 0;
    float sceneTimer = 0.0f;
    const float sceneDuration = 4.0f;
    bool isTransitioning = false;
    float transitionProgress = 0.0f;
    const float transitionSpeed = 20.0f; // Speed of transition

public:
    EndCredit() : audioManager(AudioManager::GetInstance()) {

        InitializeImages();

        transitionObject = new UINormal("Transition", "Assets/Images/black.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(25.0f, 20.0f, 0.0f), true);
        transitionEffects = std::unique_ptr<TransitionEffects>(new TransitionEffects(transitionObject));

        ContinueButton = new UIButton("SkpButton", "Assets/Images/UI/Skip_Button.png", glm::vec3(-8.85f, 4.8f, 0.0f), glm::vec3(1.3f / 2, 1.23f / 2, 0.0f), true, false);
        ContinueButton->SetHoverTexture("Assets/Images/UI/Skip_Button_Highlight.png");
        ContinueButton->SetOnClickAction([this]() { ContinueButton->setActiveStatus(false); audioManager.PlaySound("ProjectorSFX"); TransitionOut(); });
        ContinueButton->setActiveStatus(false);

        m_gameObjects.push_back(ContinueButton);
        m_gameObjects.push_back(transitionObject);
    }

    void InitializeImages() {
        float screenWidth = 19.2f;
        for (int i = 1; i <= 6; ++i) {
            std::string imagePath = "Assets/Images/EndCredit/Credit_" + std::to_string(i) + ".png";
            UIObject* creditImage = new UIObject("Credit" + std::to_string(i), imagePath, true);
            creditImage->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
            creditImage->SetPosition(glm::vec3(screenWidth * (i - 1), 0.0f, 0.0f)); // Positioned to the right initially
            creditsImages.push_back(creditImage);
            m_gameObjects.push_back(creditImage);
        }
    }

    void OnEnter() override {
        audioManager.PlaySound("menuMusic", true);
        ResetScene();
        transitionEffects->FadeIn(2.0f);
    }

    void ResetScene() {
        currentImageIndex = 0;
        sceneTimer = 0.0f;
        isTransitioning = false;
        transitionProgress = 0.0f;
        for (int i = 0; i < creditsImages.size(); ++i) {
            creditsImages[i]->SetPosition(glm::vec3(19.2f * i, 0.0f, 0.0f)); // Reset positions
            creditsImages[i]->setActiveStatus(i == 0); // Only the first image is active
        }
    }

    void Update(float dt, long frame) {
        transitionEffects->Update(dt);
        if (isTransitioning) {
            PerformImageTransition(dt);
        } else if (sceneTimer >= sceneDuration) {
            sceneTimer = 0.0f;
            if (currentImageIndex < creditsImages.size() - 1) {
                StartTransition();
            } else {
                Application::Get().SetTimer(4000, [this]() { TransitionOut(); }, false);
            }
        } else {
            sceneTimer += dt;
        }

        Scene::Update(dt, frame);
        Input& input = Application::GetInput();

        if (input.Get().GetKeyDown(GLFW_KEY_SPACE) || input.Get().GetMouseButtonDown(0))
            ContinueButton->setActiveStatus(true);
    }

    void StartTransition() {
        isTransitioning = true;
        transitionProgress = 0.0f;
        if (currentImageIndex + 1 < creditsImages.size()) {
            creditsImages[currentImageIndex + 1]->setActiveStatus(true);
        }
    }

    void PerformImageTransition(float dt) {
        float moveAmount = dt * transitionSpeed;
        transitionProgress += moveAmount;
        if (transitionProgress >= 19.2f) {
            CompleteTransition();
        }
        if (currentImageIndex < creditsImages.size()) {
            creditsImages[currentImageIndex]->SetPosition(glm::vec3(-transitionProgress, 0.0f, 0.0f));
        }
        if (currentImageIndex + 1 < creditsImages.size()) {
            creditsImages[currentImageIndex + 1]->SetPosition(glm::vec3(19.2f - transitionProgress, 0.0f, 0.0f));
        }
    }

    void CompleteTransition() {
        isTransitioning = false;
        transitionProgress = 0.0f;
        currentImageIndex++;
        creditsImages[currentImageIndex]->setActiveStatus(true);
        if (currentImageIndex > 0) {
            creditsImages[currentImageIndex - 1]->setActiveStatus(false);
        }
    }

    void TransitionOut() {
        transitionEffects->FadeOut(2.0f, [this]() {
            Application::Get().SetScene("MainMenu");
        });
    }

    void OnExit() override {

    }
};
