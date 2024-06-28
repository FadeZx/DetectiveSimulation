#pragma once

#include "Scene.h"

#include "../GameObjects/RenderGameObject.h"

#include "../UI/UIButton.h"

#include "../UI/UIElement.h"

#include "../Effects/TransitionEffects.h"

#include "../Application.h"

class TutorialScene : public Scene {

private:

	AudioManager& audioManager;
	UIElement* transitionObject;
	std::unique_ptr<TransitionEffects> transitionEffects;

	UIButton* StartButton;

public:

	TutorialScene() :audioManager(AudioManager::GetInstance())
	{

		//audioManager.LoadSound("NewspaperSlam", "Assets/Sounds/SFX_EndingNewspaperSlam.mp3", SFX, 4.0f);

		GameObject* EndingSceneBackground = new UIObject("EndingSceneBackground", "Assets/Images/Ending/EndingSelect_Background.png", true);
		EndingSceneBackground->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
		EndingSceneBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		GameObject* OperationGuide = new UIObject("OperationGuide", "Assets/Images/OperationGuide.png", true);
		OperationGuide->SetScale(glm::vec3(12.20f * 0.9, 9.70f * 0.9, 0.0f));
		OperationGuide->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		StartButton = new UIButton("StartButton", "Assets/Images/Kitchen/Button_ResetMeal.png", glm::vec3(3.1f, -3.57f, 0.0f), glm::vec3(3.19f, 0.92f, 0.0f), true, true, "Assets/Fonts/OverpassMono-SemiBold.ttf");
		StartButton->SetHoverTexture("Assets/Images/Kitchen/Button_ResetMeal_Highlight.png");
		StartButton->SetButtonText("Begin Mission");
		StartButton->SetTextSize(0.52f);
		StartButton->SetTextPosition(glm::vec3(3.15f, -3.63f, 0.0f));
		StartButton->SetOnClickAction([this]() { StartGame();});

		transitionObject = new UINormal("Transition", "Assets/Images/black.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(25.0f, 20.0f, 0.0f), true);
		transitionEffects = std::unique_ptr<TransitionEffects>(new TransitionEffects(transitionObject));

		m_gameObjects.push_back(EndingSceneBackground);
		m_gameObjects.push_back(OperationGuide);
		m_gameObjects.push_back(StartButton);

		m_gameObjects.push_back(transitionObject);

	}

	void OnEnter() override {
		transitionEffects->FadeIn(1.0f);
	}

	void Update(float dt, long frame) override {
		Scene::Update(dt, frame);
		transitionEffects->Update(dt);
	}

	void OnExit() override {

		audioManager.StopSound("OpenSceneBGMusic");

	}

	void StartGame() {
		audioManager.PlaySound("buttonClick2");
		transitionEffects->FadeOut(2.0f, [this]() { Application::Get().SetScene("Hallway"); });
	}


};