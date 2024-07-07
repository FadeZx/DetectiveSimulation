#pragma once

#include "Scene.h"

#include "../GameObjects/RenderGameObject.h"
#include"../GameObjects/AnimateGameObject.h"	
#include "../UI/UIButton.h"
#include "../Text/Text.h"

#include "../Application.h"

#include "../GameObjects/JournalData.h"

#define CONTINUE_TIME 20000
class EndScene : public Scene {

public:

	EndScene() :audioManager(AudioManager::GetInstance())
	{

		audioManager.LoadSound("NewspaperSlam", "Assets/Sounds/SFX_EndingNewspaperSlam.mp3", SFX, 9.0f);

		GameObject* EndingSceneBackground = new UIObject("EndingSceneBackground", "Assets/Images/Ending/Ending_Background.png", true);
		EndingSceneBackground->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
		EndingSceneBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		MissingPoster = new UIObject("MissingPoster", "Assets/Images/Ending/MissingPoster_Rotate.png", true);
		MissingPoster->SetScale(glm::vec3(8.82f, 9.58f, 0.0f));
		MissingPoster->SetPosition(glm::vec3(-4.5f, -2.2f, 0.0f));

		Ending1 = new UIObject("Ending1", "Assets/Images/Ending/Ending1_Rotate.png", true);
		Ending1->SetScale(glm::vec3(12.85f, 8.85f, 0.0f));
		Ending1->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		Ending2 = new UIObject("Ending2", "Assets/Images/Ending/Ending2_Rotate.png", true);
		Ending2->SetScale(glm::vec3(12.85f, 8.85f, 0.0f));
		Ending2->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		Ending3 = new UIObject("Ending3", "Assets/Images/Ending/Ending3_Rotate.png", true);
		Ending3->SetScale(glm::vec3(12.85f, 8.85f, 0.0f));
		Ending3->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		Ending4 = new UIObject("Ending4", "Assets/Images/Ending/Ending4_Rotate.png", true);
		Ending4->SetScale(glm::vec3(12.85f, 8.85f, 0.0f));
		Ending4->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		Ending5 = new UIObject("Ending5", "Assets/Images/Ending/Ending5_Rotate.png", true);
		Ending5->SetScale(glm::vec3(12.85f, 8.56f, 0.0f));
		Ending5->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		Ending6 = new UIObject("Ending6", "Assets/Images/Ending/Ending6_Rotate.png", true);
		Ending6->SetScale(glm::vec3(12.85f, 8.56f, 0.0f));
		Ending6->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		Endings[END1] = Ending1;
		Endings[END2] = Ending2;
		Endings[END3] = Ending3;
		Endings[END4] = Ending4;
		Endings[END5] = Ending5;
		Endings[END6] = Ending6;

		ContinueButton = new UIButton("ContinueButton", "Assets/Images/Kitchen/Button_ResetMeal.png", glm::vec3(7.5f, 4.6f, 0.0f), glm::vec3(3.19f, 0.92f, 0.0f), true, true, "Assets/Fonts/OverpassMono-SemiBold.ttf");
		ContinueButton->SetHoverTexture("Assets/Images/Kitchen/Button_ResetMeal_Highlight.png");
		ContinueButton->SetButtonText("Continue");
		ContinueButton->SetTextSize(0.52f);
		ContinueButton->SetTextPosition(glm::vec3(7.55f, 4.52f, 0.0f));
		ContinueButton->SetOnClickAction([this]() { 
			ContinueButton->setActiveStatus(false);
			audioManager.PlaySound("buttonClick2");
			TransitionOut();
			});
		ContinueButton->setActiveStatus(false);

		transitionObject = new UINormal("Transition", "Assets/Images/black.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(25.0f, 20.0f, 0.0f), true);
		transitionEffects = std::unique_ptr<TransitionEffects>(new TransitionEffects(transitionObject));

		m_gameObjects.push_back(EndingSceneBackground);
		m_gameObjects.push_back(MissingPoster);
		m_gameObjects.push_back(ContinueButton);
		m_gameObjects.push_back(Ending1);
		m_gameObjects.push_back(Ending2);
		m_gameObjects.push_back(Ending3);
		m_gameObjects.push_back(Ending4);
		m_gameObjects.push_back(Ending5);
		m_gameObjects.push_back(Ending6);
		m_gameObjects.push_back(transitionObject);

	}

	void OnEnter() override {

		audioManager.PlaySound("NewspaperSlam");

		final_ending = journal_data->checkMainPageEntry();

		std::cout << "ENDING " << final_ending + 1 << std::endl;

		Application::Get().SetTimer(CONTINUE_TIME, [this]() {
			ShowContinueButton();
			}, false);

		SetFinalScene(final_ending);
		currentTime = 0.0f;
		transitioning = false;
		transitionEffects->FadeIn(0.5f);

	}


	void OnExit() override {

		audioManager.StopSound("OpenSceneBGMusic");

	}

	void SetFinalScene(int ending) {

		for (int i = 0; i < 6; i++) {
			if (ending == i) {
				Endings[i]->setActiveStatus(true);
				ChosenEndingPoster = Endings[i];
				ChosenEndingPoster->SetScale(glm::vec3(13.15f * 2.0f, 8.56f * 2.0f, 0.0f)); // 200% of the original scale
			}
			else {
				Endings[i]->setActiveStatus(false);
			}
		}

		if (ending == END5 || ending == END6) {
			MissingPoster->setActiveStatus(true);
		}
		else {
			MissingPoster->setActiveStatus(false);
		}

	}

	void Update(float dt, long frame)
	{

		Scene::Update(dt, frame);
		transitionEffects->Update(dt);

		if (ChosenEndingPoster && currentTime <= zoomInDuration) {

			currentTime += dt;
			float progress = currentTime / zoomInDuration;
			// Interpolating from 200% to 100%
			float targetScaleX = 26.3f - (13.15f * progress); // Decreasing from 26.3f to 13.15f
			float targetScaleY = 17.12f - (8.56f * progress); // Decreasing from 17.12f to 8.56f
			ChosenEndingPoster->SetScale(glm::vec3(targetScaleX, targetScaleY, 0.0f));
		}



		Input& input = Application::GetInput();

		if (!transitioning)
		{
			if (input.Get().GetKeyDown(GLFW_KEY_SPACE) || input.Get().GetMouseButtonDown(0)) {
				ShowContinueButton();
			}
		}

	}

	void ShowContinueButton()
	{
		if (!ContinueButton->getActiveStatus())
			ContinueButton->setActiveStatus(true);
	}

	void TransitionOut()
	{
		gameStateManager.Reset();
		journal_data->ResetJournalData();
		transitionEffects->FadeOut(3.0f, [this]() { Application::Get().SetScene("EndCredit"); });
		transitioning = true;
	}


private:

	GameStateManager& gameStateManager = GameStateManager::GetInstance();

	AudioManager& audioManager;

	JournalData* journal_data = JournalData::GetInstance();

	int final_ending;

	GameObject* Ending1;
	GameObject* Ending2;
	GameObject* Ending3;
	GameObject* Ending4;
	GameObject* Ending5;
	GameObject* Ending6;
	GameObject* MissingPoster;

	GameObject* Endings[6];

	GameObject* ChosenEndingPoster;


	UIButton* ContinueButton;

	UIElement* transitionObject;
	std::unique_ptr<TransitionEffects> transitionEffects;

	float zoomInDuration = 0.5f;  // Duration for zoom in effect in seconds
	float currentTime = 0.0f;     // Current time elapsed

	bool transitioning = false;

};