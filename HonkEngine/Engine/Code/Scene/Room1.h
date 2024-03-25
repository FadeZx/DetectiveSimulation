#pragma once

#include "Scene.h"
#include "../UI/UINormal.h"  
#include "../UI/UIElement.h"  
#include "../Input/Input.h"
#include "../Engine.h"
#include <glm/glm.hpp>
#include <iostream>
#include "../Dialogue/DialogueBox.h"
#include "../Dialogue/Dialoguemanager.h"
#include "../Effects/ParallaxManager.h"
#include <memory>

using namespace std;

class Room1 : public Scene {
public:

    Room1() {

        GameObject* background1 = new RenderGameObject("BG1", "Assets/Images/Cabin_Background.png");
        GameObject* background2 = new RenderGameObject("BG2", "Assets/Images/Cabin_Background.png");
        background1->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));
        background2->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));
        background1->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));
        background2->SetPosition(glm::vec3(76.6f, 3.0f, 0.0f));

        // Scale Multiplier to fit asset scale with screensize
        float sm = 1.23f;

        //Objects     
        UIElement* room = new UINormal("cabin1", "Assets/Images/Martha_Cabin.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(19.60f * sm, 10.55f * sm, 0.0f), true);
        UIElement* martha = new UINormal("Martha", "Assets/Images/Martha/Martha_Normal.png", glm::vec3(4.95f, -2.45f, 0.0f), glm::vec3(3.81f * sm, 6.53f * sm, 0.0f), true);
        UIElement* lamp = new UINormal("Lamp", "Assets/Images/Martha/Lamp.png", glm::vec3(-1.3f, -0.3f, 0.0f), glm::vec3(1.62f * sm, 2.25f * sm, 0.0f), true);
        UIElement* hat = new UINormal("Hat", "Assets/Images/Martha/Hat.png", glm::vec3(-1.1f, -1.22f, 0.0f), glm::vec3(3.12f * sm, 0.92f * sm, 0.0f), true);
        UIElement* bag = new UINormal("Bag", "Assets/Images/Martha/Bag.png", glm::vec3(-0.25f, -5.25f, 0.0f), glm::vec3(2.59f * sm * 1.2f, 1.64f * sm * 1.2f, 0.0f), true);
        UIElement* cane = new UINormal("Cane", "Assets/Images/Martha/Inspection_Cane.png", glm::vec3(-4.0f, -3.72f, 0.0f), glm::vec3(1.07f * sm * 1.2f, 3.7f * sm * 1.2f, 0.0f), true);
        UIElement* letter = new UINormal("Letter", "Assets/Images/Martha/Inspection_Letter.png", glm::vec3(-2.15f, -5.9f, 0.0f), glm::vec3(1.13f * sm * 1.2f, 0.73f * sm * 1.2f, 0.0f), true);

        //UIs
        UIButton* dialogueBox = new UIButton("DialogueBox", "Assets/Images/UI/DialogueBox.png",
            glm::vec3(0.0f, 3.6f, 0.0f), glm::vec3(10.96f, 2.05f, 0.0f),
            true, true, "Assets/Fonts/OverpassMono.ttf");

        UIButton* dialogueChoice1 = new UIButton("DialogueChoiceBox1", "Assets/Images/UI/DialogueChoiceBox.png",
            glm::vec3(0.0f, 1.6f, 0.0f), glm::vec3(10.96f, 2.05f, 0.0f),
            true, true, "Assets/Fonts/OverpassMono.ttf");
        UIButton* dialogueChoice2 = new UIButton("DialogueChoiceBox2", "Assets/Images/UI/DialogueChoiceBox.png",
            glm::vec3(0.0f, -1.6f, 0.0f), glm::vec3(10.96f, 2.05f, 0.0f),
            true, true, "Assets/Fonts/OverpassMono.ttf");

        UIElement* marthaIcon = new UINormal("MarthaIcon", "Assets/Images/UI/Speaker_icon_Martha.png", glm::vec3(4.18f, 3.6f, 0.0f), glm::vec3(2.19f, 1.57f, 0.0f), true);

        UIElement* waiterIcon = new UINormal("WaiterIcon", "Assets/Images/UI/Speaker_icon_Waiter.png", glm::vec3(4.18f, 3.53f, 0.0f), glm::vec3(1.23f, 1.4f, 0.0f), true);

        dialogueManager =make_unique<DialogueManager>("DialogueManagerName", dialogueBox,
             "Assets/Dialogue/Dialogue_Martha_OrderPhase.xml");
        //Add SpeakerIcon
        dialogueManager->AddSpeakerIcon("M", marthaIcon);
        dialogueManager->AddSpeakerIcon("W", waiterIcon);
        //Add ChoiceButton
        dialogueManager->AddChoiceButton(dialogueChoice1);
        dialogueManager->AddChoiceButton(dialogueChoice2);
        

        //setDialogueUI
        dialogueManager->SetDialoguePosition(-0.5f, 3.70f);
        dialogueManager->SetDialogueScale(0.55f);

        //Push GamePbjects
        m_gameObjects.push_back(background1);
        m_gameObjects.push_back(background2);
        m_gameObjects.push_back(room);
        m_gameObjects.push_back(martha);
        m_gameObjects.push_back(lamp);
        m_gameObjects.push_back(hat);
        m_gameObjects.push_back(bag);
        m_gameObjects.push_back(cane);
        m_gameObjects.push_back(letter);
        m_gameObjects.push_back(dialogueBox);
        m_gameObjects.push_back(dialogueChoice1);
        m_gameObjects.push_back(dialogueChoice2);
        m_gameObjects.push_back(marthaIcon);  
        m_gameObjects.push_back(waiterIcon);

        //add Parallax Effects
        parallaxManager = make_unique<ParallaxManager>();

        float defaultLayer = 0.8f;
        float objectLayerOne = 0.83f;

        // Add objects to different layers
        parallaxManager->AddObjectToLayer(room, defaultLayer);   // Layer 1
        parallaxManager->AddObjectToLayer(lamp, defaultLayer);   // Layer 1.5
        parallaxManager->AddObjectToLayer(hat, objectLayerOne);    // Layer 2
        parallaxManager->AddObjectToLayer(bag, objectLayerOne);    // Layer 2
        parallaxManager->AddObjectToLayer(cane, objectLayerOne);   // Layer 2
        parallaxManager->AddObjectToLayer(letter, objectLayerOne); // Layer 2
        parallaxManager->AddObjectToLayer(martha, objectLayerOne); // Layer 2

        //Scrolling effect for Background
        parallaxManager->SetBackgroundSpeed(2.0f);
        parallaxManager->AddBackgroundObject(background1);
        parallaxManager->AddBackgroundObject(background2);


    }

    void Update(float dt, long frame) override {

        Scene::Update(dt, frame);
        dialogueManager->Update(dt, frame);
        parallaxManager->Update(dt,frame);

        if (input.Get().GetKeyDown(GLFW_KEY_E)) {
            Application::Get().SetScene("Hallway");
        }

        if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {
            dialogueManager->PlayNextDialogue();
        }

 
    }




    void Render() override {
        Scene::Render(); // Renders GameObjects

        // Manually call DialogueManager's render function
        dialogueManager->Render();
    }

private:
    Input& input = Application::GetInput();
    Camera& camera = Application::GetCamera();
   unique_ptr<DialogueManager> dialogueManager;
   unique_ptr<ParallaxManager> parallaxManager;

};