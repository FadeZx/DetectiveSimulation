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

        // Create a UIElement instead of RenderGameObject for the cabin
        UIElement* room = new UINormal("cabin1", "Assets/Images/passenger_room1.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(20.0f, 12.0f, 0.0f),true);




        //dialogueManager.LoadDialogues("Assets/Dialogue/test.xml");
        //room->SetScale(glm::vec3(20.0f, 12.0f, 0.0f));
        m_gameObjects.push_back(room);
       // m_gameObjects.push_back(dialogueBox);

    }

    void Update(float dt, long frame) override {

        Scene::Update(dt, frame); // Call the base class update

        if (input.Get().GetKeyDown(GLFW_KEY_E)) {
            std::cout << "Button pressed" << std::endl;
            Application::Get().SetScene("Hallway");
        }

        if (input.Get().GetKeyDown(GLFW_KEY_T)) {
            //dialogueBox->SetText("You pressed T!");
            //dialogueManager.NextDialogue();
        }

        //dialogueManager.DisplayCurrentDialogue();

        // Use the UIElement for cabin interaction
        //GameObject* cabinObject = GetGameObjectByName("cabin1");
        
    }

private:
    Input& input = Application::GetInput();
    Camera& camera = Application::GetCamera();
    //std::unique_ptr<DialogueBox> dialogueBox;
    //DialogueManager dialogueManager;
};
