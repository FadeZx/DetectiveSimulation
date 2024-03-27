#pragma once

#include "Scene.h"

#include "../GameObjects/RenderGameObject.h"
#include"../GameObjects/AnimateGameObject.h"	

#include "../UI/UIButton.h"
#include "../UI/UIDraggable.h"


class Kitchen : public Scene {


public:

	Kitchen() :audioManager(AudioManager::GetInstance()) {

		/*--------------------------------------------------------------LOAD AUDDIO------------------------------------------------------------------------------------------------------- */
		/*audioManager.LoadSound("kitchenAmbience", "Assets/Sounds/Ambience_Kitchen.mp3", 0.2f);
		audioManager.PlaySound("kitchenAmbience", true);*/

		/*--------------------------------------------------------------CREATE GAMEOBJECT------------------------------------------------------------------------------------------------------- */

		GameObject* KitchenBackground = new RenderGameObject("KitchenBackground", "Assets/Images/Kitchen/Kitchen_Background.png");

		/*--------------------------------------------------------------CREATE BUTTONS------------------------------------------------------------------------------------------------------- */

		UIButton* ServeBell = new UIButton("ServeBell", "Assets/Images/Kitchen/ServeButton_notServable_default.png", glm::vec3(-4.3f, -2.1f, 0.0f), glm::vec3(2.2f, 1.5f, 0.0f), true, false);

		/*--------------------------------------------------------------CREATE FOOD DRAGGABLES------------------------------------------------------------------------------------------------------- */

		UIDraggable* EarlGreyTea = new UIDraggable("EarlGreyTea", "Assets/Images/Kitchen/Food/Tea/TeaBox_Earl.png", glm::vec3(1.8f, 0.0f, 0.0f), glm::vec3(1.3f, 1.6f, 0.0f), true);
		UIDraggable* AssamBlackTea = new UIDraggable("AssamBlackTea", "Assets/Images/Kitchen/Food/Tea/TeaBox_Assam.png", glm::vec3(3.5f, 0.0f, 0.0f), glm::vec3(1.3f, 1.6f, 0.0f), true);

		/*UIDraggable* GreenTea = new UIDraggable("GreenTea", "Assets/Images/Kitchen/Food/Tea/TeaBox_Green.png", glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), true);
		UIDraggable* JasmineTea = new UIDraggable("JasmineTea", "Assets/Images/Kitchen/Food/Tea/TeaBox_Jasmine.png", glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), true);*/

		UIDraggable* SalmonSandwhich = new UIDraggable("SalmonSandwhich", "Assets/Images/Kitchen/Food/Sandwhich/Meal_Salmon.png", glm::vec3(2.3f, -2.1f, 0.0f), glm::vec3(2.6f, 1.3f, 0.0f), true);
		UIDraggable* EggSandwhich = new UIDraggable("EggSandwhich", "Assets/Images/Kitchen/Food/Sandwhich/Meal_Egg.png", glm::vec3(5.3f, -2.1f, 0.0f), glm::vec3(2.6f, 1.3f, 0.0f), true);

		UIDraggable* Eclair = new UIDraggable("Eclair", "Assets/Images/Kitchen/Food/Dessert/Dessert_Eclair.png", glm::vec3(2.3f, -4.3f, 0.0f), glm::vec3(2.2f, 0.8f, 0.0f), true);
		UIDraggable* Macaron = new UIDraggable("Macaron", "Assets/Images/Kitchen/Food/Dessert/Dessert_Macaron.png", glm::vec3(5.3f, -4.3f, 0.0f), glm::vec3(2.2f, 0.8f, 0.0f), true);


		/*-------------------------------------------------------------SET TRANSFORMATION------------------------------------------------------------------------------------------------------- */

		KitchenBackground->SetScale(glm::vec3(19.5f, 10.8f, 0.0f));
		KitchenBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		/*--------------------------------------------------------------PUSH BACK------------------------------------------------------------------------------------------------------- */
		
		m_gameObjects.push_back(KitchenBackground);
		m_gameObjects.push_back(ServeBell);

		//TEA
		m_gameObjects.push_back(EarlGreyTea);
		m_gameObjects.push_back(AssamBlackTea);
		/*m_gameObjects.push_back(GreenTea);
		m_gameObjects.push_back(JasmineTea);*/

		//SANDWHICH

		m_gameObjects.push_back(SalmonSandwhich);
		m_gameObjects.push_back(EggSandwhich);

		//DESSERT

		m_gameObjects.push_back(Eclair);
		m_gameObjects.push_back(Macaron);


	}

	void Update(float dt, long frame) override {

		Scene::Update(dt, frame); // Call the base class update

		
		if (input.Get().GetKeyDown(GLFW_KEY_K)) {
			Application::Get().SetScene("Hallway");
		}


	}

	

private:

	AudioManager& audioManager;
	Input& input = Application::GetInput();

	const glm::vec3 tea_platePos;
	const glm::vec3 sandwhich_platePos;
	const glm::vec3 dessert_platePos;
	
};