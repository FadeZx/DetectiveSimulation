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
#include <memory>

class Room1 : public Scene {
public:

    Room1() {

        auto room = std::make_shared<UINormal>("cabin1", "Assets/Images/passenger_room1.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(20.0f, 12.0f, 0.0f), true);
        auto dialogueManager = std::make_shared<DialogueManager>("DialogueManager", "path/to/font.ttf", "Assets/Dialogue/test.xml");

        m_gameObjects.push_back(room); // Assuming m_gameObjects can store shared_ptr<GameObject>
        m_gameObjects.push_back(dialogueManager);
        
    }

    void Update(float dt, long frame) override {

        Scene::Update(dt, frame); // Call the base class update

        GameObject* dialogueText = GetGameObjectByName("Dialogue1");
        if (input.Get().GetKeyDown(GLFW_KEY_E)) {
            std::cout << "Button pressed" << std::endl; 
            Application::Get().SetScene("Hallway");
        }

        if (input.Get().GetKeyDown(GLFW_KEY_T)) {
            //dialogueBox->SetText("You pressed T!");
           //alogueText
        }


        // Use the UIElement for cabin interaction
        
        
    }

private:
    Input& input = Application::GetInput();
    Camera& camera = Application::GetCamera();
    //std::unique_ptr<DialogueBox> dialogueBox;
    DialogueManager dialogueManager;
};
