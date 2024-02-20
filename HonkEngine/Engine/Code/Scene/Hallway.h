#pragma once

#include "Scene.h"
#include "../GameObjects/RenderGameObject.h"
#include"../GameObjects/AnimateGameObject.h"	

#include "../GameObjects/Player.h"
#include "../Text/TextRenderer.h"
#include "../Text/Text.h"
#include"../Audio/AudioManager.h"	
#include "../UI/UIButton.h"
#include "../UI/UIDraggable.h"
#include "../UI/UINormal.h"
#include "../UI/UIElement.h"

class Hallway : public Scene
{

private:
	std::unique_ptr<TextRenderer> textRenderer;
	AudioManager& audioManager;
public:
	Hallway() :audioManager(AudioManager::GetInstance())
	{
		/*--------------------------------------------------------------🔊LOAD AUDDIO🔊------------------------------------------------------------------------------------------------------- */
		audioManager.LoadSound("backgroundMusic", "Assets/Sounds/MembersOnly.mp3", 0.2f);
		audioManager.LoadSound("trainAmbience", "Assets/Sounds/Train_Ambience.mp3", 0.2f);
		audioManager.PlaySound("backgroundMusic", true);
		audioManager.PlaySound("trainAmbience", true);

		/*--------------------------------------------------------------📦CREATE GAMEOBJECT📦------------------------------------------------------------------------------------------------------- */

		auto hallway = std::make_unique<RenderGameObject>("Cabin", "Assets/Images/Environment_Corridor_Hallway.png");
		auto hallwaylights = std::make_unique<RenderGameObject>("CabinLights", "Assets/Images/Environment_Corridor_Light.png");

		/*-------------------------------------------------------------🎮CREATE PLAYER🎮------------------------------------------------------------------------------------------------------- */

		auto player = std::make_unique<Player>("waiter", "Assets/Images/MainCharacter_WithTray_Walk.png", 2, 8);

		/*-------------------------------------------------------------💬CREATE TEXT💬------------------------------------------------------------------------------------------------------- */

		auto helloText = std::make_unique<Text>("GameTitle", " Welcome To Ticking Tea Time", "Assets/Fonts/WD.ttf");
		auto gt = std::make_unique<Text>("gt", "Test Font EI", "Assets/Fonts/EI.ttf");
		auto orderNoText = std::make_unique<Text>("orderNo", "1", "Assets/Fonts/WD.ttf");

		/*-------------------------------------------------------------💬CREATE UI💬------------------------------------------------------------------------------------------------------- */
		auto orderPaper = std::make_unique<UINormal>("OrderPaper", "Assets/Images/OrderPaper.png", glm::vec3(-7.9f, 3.5f, 0.0f), glm::vec3(3.0f, 3.0f, 0.0f), true);
		auto timer = std::make_unique<UINormal>("Timer", "Assets/Images/Timer.png", glm::vec3(7.9f, 3.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), true);
		auto screenUI = std::make_unique<UINormal>("ScreenUI", "Assets/Images/ScreenUI.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(16.0f * 1.19f, 9.0f * 1.19f, 0.0f), true);
		auto journalButton = std::make_unique<UIButton>("JournalButton", "Assets/Images/JournalButton.png", glm::vec3(-8.4f, -4.1f, 0.0f), glm::vec3(2.8f, 2.8f, 0.0f), true);
		auto ticket = std::make_unique<UIDraggable>("ticket", "Assets/Images/Journal_CaseSummary_Ticket_WithText.png", glm::vec3(6.0f, -4.0f, 0.0f), glm::vec3(2.0f, 1.0f, 0.0f), false);

		/*-------------------------------------------------------------➡️SET TRANSFORMATION➡️------------------------------------------------------------------------------------------------------- */

		hallway->SetScale(glm::vec3(45.0f, 10.5f , 0.0f));
		hallway->SetPosition(glm::vec3(0.0f, 0.24f, 0.0f));
		hallwaylights->SetScale(glm::vec3(45.0f, 10.5f, 0.0f));
		hallwaylights->SetPosition(glm::vec3(0.0f, -0.2f, 0.0f));


		helloText->SetPosition(glm::vec3(-3.7f, 3.8f, 0.0f));
		helloText->SetColor(glm::vec3(1, 1, 1));
		orderNoText->SetPosition(glm::vec3(-8.7f, 4.5f, 0.0f));
		orderNoText->SetColor(glm::vec3(1, 0, 0));

		/*--------------------------------------------------------------✅PUSH BACK✅------------------------------------------------------------------------------------------------------- */
		//Environment
		m_gameObjects.push_back(std::move(hallway));
		m_gameObjects.push_back(std::move(player));
		m_gameObjects.push_back(std::move(hallwaylights));

		//UIs
		m_gameObjects.push_back(std::move(journalButton));
		//m_gameObjects.push_back(timer);
		//m_gameObjects.push_back(orderPaper);
		m_gameObjects.push_back(std::move(screenUI));
		m_gameObjects.push_back(std::move(ticket));

		//Texts
		m_gameObjects.push_back(std::move(helloText));
		m_gameObjects.push_back(std::move(gt));
		m_gameObjects.push_back(std::move(orderNoText));
	}

	void Update(float dt, long frame) {
		Scene::Update(dt, frame); // Call the base class update

		// Retrieve the player object by name
		GameObject* playerObject = GetGameObjectByName("waiter");
		if (playerObject) {
			// Cast to Player* if necessary, or directly use if GetPosition is part of GameObject
			Player* player = dynamic_cast<Player*>(playerObject);
			if (player) {
				// Get the player's position
				glm::vec3 playerPos = player->GetPosition();
				// Get the camera and update its position
				Camera& camera = Application::GetCamera();

				const float leftBound = -12.74f;
				const float rightBound = 12.91f;

				// Set the target position for the camera
				float targetX = std::max(leftBound, std::min(playerPos.x, rightBound));

				// Smoothing factor for camera movement
				float smoothingFactor = 0.05f; // Experiment with different values

				// Smoothly interpolate the camera's x position towards the target
				float interpolatedX = camera.GetPosX() + smoothingFactor * (targetX - camera.GetPosX());

				// Set the new camera position
				camera.SetPosition(targetX, camera.GetPosY());

			}
		}

	}

};	