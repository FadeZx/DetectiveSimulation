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

       

       auto room = std::make_unique<UINormal>("cabin1", "Assets/Images/passenger_room1.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(20.0f, 12.0f, 0.0f), true);

       // Push the room directly as a unique_ptr
       m_gameObjects.push_back(std::move(room));

       // Create and move the DialogueManager unique_ptr into m_gameObjects
       dialogueManager = std::make_unique<DialogueManager>("DialogueManagerName", "Assets/Fonts/EI.ttf", "Assets/Dialogue/test.xml");
       m_gameObjects.push_back(std::move(dialogueManager));

    }

    void Update(float dt, long frame) override {

        Scene::Update(dt, frame); // Call the base class update

        GameObject* dialogueText = GetGameObjectByName("Dialogue1");
        if (input.Get().GetKeyDown(GLFW_KEY_E)) {
            std::cout << "E key pressed" << std::endl;
            Application::Get().SetScene("Hallway");
        }

        if (input.Get().GetKeyDown(GLFW_KEY_T)) {
            std::cout << "T key pressed" << std::endl;
            dialogueManager->PlayNextDialogue();
           //alogueText
        }


        // Use the UIElement for cabin interaction
        
        
    }

private:
    Input& input = Application::GetInput();
    Camera& camera = Application::GetCamera();
    std::unique_ptr<DialogueManager> dialogueManager;

};
