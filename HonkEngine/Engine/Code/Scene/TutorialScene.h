#pragma once

#include "Scene.h"

#include "../GameObjects/RenderGameObject.h"

#include "../UI/UIButton.h"

#include "../Application.h"

class TutorialScene : public Scene {

public:

	TutorialScene() :audioManager(AudioManager::GetInstance())
	{

		//audioManager.LoadSound("NewspaperSlam", "Assets/Sounds/SFX_EndingNewspaperSlam.mp3", SFX, 4.0f);

		GameObject* EndingSceneBackground = new UIObject("EndingSceneBackground", "Assets/Images/Ending/Ending_Background.png", true);
		EndingSceneBackground->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
		EndingSceneBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		GameObject* OperationGuide = new UIObject("OperationGuide", "Assets/Images/OperationGuide.png", true);
		OperationGuide->SetScale(glm::vec3(12.85f, 8.85f, 0.0f));
		OperationGuide->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		StartButton = new UIButton("StarteButton", "Assets/Images/Kitchen/Button_ResetMeal.png", glm::vec3(7.5f, 4.6f, 0.0f), glm::vec3(3.19f, 0.92f, 0.0f), true, true, "Assets/Fonts/OverpassMono-SemiBold.ttf");
		StartButton->SetHoverTexture("Assets/Images/Kitchen/Button_ResetMeal_Highlight.png");
		StartButton->SetButtonText("Begin Mission");
		StartButton->SetTextSize(0.52f);
		StartButton->SetTextPosition(glm::vec3(7.55f, 4.52f, 0.0f));
		StartButton->SetOnClickAction([this]() { StartGame();});

		m_gameObjects.push_back(EndingSceneBackground);
		m_gameObjects.push_back(OperationGuide);

		m_gameObjects.push_back(StartButton);

	}


	void OnExit() override {

		audioManager.StopSound("OpenSceneBGMusic");

	}


	void StartGame() {

		Application::Get().SetScene("Hallway");

	}


private:

	AudioManager& audioManager;

	UIButton* StartButton;

};