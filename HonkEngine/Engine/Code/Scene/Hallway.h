﻿#pragma once

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
#include "../GameObjects/Book.h"
#include "../UI/UIButtonEmpty.h"
#include "../GameObjects/Door.h"
#include "../GameObjects/DoorsManager.h"
#include "../OrderSystem/OrderUIManager.h"
#include "../OrderSystem/OrderData.h"
#include "../OrderSystem/IOrderDataObserver.h"

class Hallway : public Scene, public IOrderDataObserver
{
	Text* orderNoText;
	Text* teaOrderText;
	Text* sandwichOrderText;
	Text* pastryOrderText;


private:
	std::unique_ptr<TextRenderer> textRenderer;
	AudioManager& audioManager;
	Book* Journal;
	OrderUIManager* uiManager;
	
public:
	Hallway() :audioManager(AudioManager::GetInstance())
	{
		/*--------------------------------------------------------------🔊LOAD AUDDIO🔊------------------------------------------------------------------------------------------------------- */
		audioManager.LoadSound("hallwayMusic", "Assets/Sounds/BGmusic_Corridor_NoTimer.mp3", 0.3f);
		audioManager.LoadSound("trainAmbience", "Assets/Sounds/Ambience_Train.mp3", 0.3f);
		audioManager.PlaySound("hallwayMusic", true);
		audioManager.PlaySound("trainAmbience", true);

		/*--------------------------------------------------------------📦CREATE GAMEOBJECT📦------------------------------------------------------------------------------------------------------- */

		GameObject* hallway = new RenderGameObject("Cabin", "Assets/Images/Environment_Corridor_Hallway.png");
		GameObject* hallwaylights = new RenderGameObject("CabinLights", "Assets/Images/Environment_Corridor_Light.png");
		Journal = new Book();
		// Inside the Hallway constructor
		


		/*-------------------------------------------------------------🎮CREATE PLAYER🎮------------------------------------------------------------------------------------------------------- */

		Player* player = new Player("waiter", "Assets/Images/MainCharacter_WithTray_Walk.png", 2, 8, Journal); 

		/*-------------------------------------------------------------💬CREATE TEXT💬------------------------------------------------------------------------------------------------------- */

		Text* helloText = new Text("GameTitle", " Welcome To Ticking Tea Time", "Assets/Fonts/WD.ttf",true);
		
		Text* orderNoText = new Text("orderNo", "", "Assets/Fonts/mvboli.ttf",true);
		Text* teaOrderText = new Text("TeaOrder", "", "Assets/Fonts/mvboli.ttf", true);
		Text* sandwichOrderText = new Text("sandwichOrder", "", "Assets/Fonts/mvboli.ttf", true);
		Text* pastryOrderText = new Text("PastryOrder", "", "Assets/Fonts/mvboli.ttf", true);

		//OrderData to manager Order Text
		OrderData::GetInstance().RegisterObserver(this);

		/*-------------------------------------------------------------💬CREATE UI💬------------------------------------------------------------------------------------------------------- */
		UIElement* orderPaper = new UINormal("OrderPaper", "Assets/Images/OrderPaper.png", glm::vec3(-7.65f, 4.0f, 0.0f), glm::vec3(3.55f, 2.54f, 0.0f), true);
		UIElement* timer = new UINormal("Timer", "Assets/Images/Timer.png", glm::vec3(7.3f, 5.1f, 0.0f), glm::vec3(4.37f, 3.13f, 0.0f), true);
		UIElement* screenUI = new UINormal("ScreenUI", "Assets/Images/ScreenUI.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(16.0f * 1.19f, 9.0f * 1.19f, 0.0f), true);
		UIButton* journalButton = new UIButton("JournalButton", "Assets/Images/JournalButton.png", glm::vec3(-8.32f, -4.8f, 0.0f), glm::vec3(3.0f, 3.0f, 0.0f), true, false, "");
		journalButton->SetOnClickAction([this]() { Journal->drawBook(); });

		Door* kitchenDoor = new Door("KitchenDoor", glm::vec3(18.35f, -0.55f, 0.0f), glm::vec3(2.8f, 5.7f, 0.0f), "Kitchen");
		DoorManager::GetInstance().AddDoor(kitchenDoor);

		Door* room1Door = new Door("Room1Door", glm::vec3(-18.35f, -0.55f, 0.0f), glm::vec3(2.8f, 5.7f, 0.0f), "Room1");
		DoorManager::GetInstance().AddDoor(room1Door);

		//TO TEST DRAW EMPTY UI
		/*GameObject* box = new RenderGameObject("textbox", "Assets/Images/Square_Border.png");
		box->SetScale(glm::vec3(2.8f, 5.7f, 0.0f));
		box->SetPosition(glm::vec3(18.35f, -0.55f, 0.0f));
		m_gameObjects.push_back(box);*/

		/*-------------------------------------------------------------➡️SET TRANSFORMATION➡️------------------------------------------------------------------------------------------------------- */

		hallway->SetScale(glm::vec3(50.00f, 10.8f, 0.0f));
		hallway->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		hallwaylights->SetScale(glm::vec3(50.0f, 10.8f, 0.0f));
		hallwaylights->SetPosition(glm::vec3(0.0f, -0.2f, 0.0f));


		helloText->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));
		helloText->SetColor(glm::vec3(1, 1, 1));
		orderNoText->SetPosition(glm::vec3(-8.8f, 4.5f, 0.0f));
		orderNoText->SetColor(glm::vec3(0.5, 0, 0));
		teaOrderText->SetPosition(glm::vec3(-6.8f, 4.6f, 0.0f));
		teaOrderText->SetScale(0.5f);
		sandwichOrderText->SetPosition(glm::vec3(-7.8f, 4.0f, 0.0f));
		sandwichOrderText->SetScale(0.5f);
		pastryOrderText->SetPosition(glm::vec3(-7.8f, 3.3f, 0.0f));
		pastryOrderText-> SetScale(0.5f);

		/*--------------------------------------------------------------✅PUSH BACK✅------------------------------------------------------------------------------------------------------- */
		//Environment
		m_gameObjects.push_back(hallway);
		m_gameObjects.push_back(player);
		m_gameObjects.push_back(hallwaylights);

		//UIs
		m_gameObjects.push_back(journalButton);
		m_gameObjects.push_back(timer);
		m_gameObjects.push_back(orderPaper);
		m_gameObjects.push_back(kitchenDoor);
		m_gameObjects.push_back(room1Door);
		
		
		//Texts
		//m_gameObjects.push_back(helloText);
		m_gameObjects.push_back(orderNoText);
		m_gameObjects.push_back(teaOrderText);
		m_gameObjects.push_back(sandwichOrderText);
		m_gameObjects.push_back(pastryOrderText);

		//Journal
		m_gameObjects.push_back(Journal);
		//Journal->closeBook();

	}

	~Hallway() {
		OrderData::GetInstance().UnregisterObserver(this);
		delete uiManager;
	}

	void OnOrderDataChanged() override {
		// Update text based on the changes in OrderData
		orderNoText->SetContent(OrderData::GetInstance().GetRoomNumber());
		teaOrderText->SetContent(OrderData::GetInstance().GetTeaOrder());
		sandwichOrderText->SetContent(OrderData::GetInstance().GetSandwichOrder());
		pastryOrderText->SetContent(OrderData::GetInstance().GetPastryOrder());
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





