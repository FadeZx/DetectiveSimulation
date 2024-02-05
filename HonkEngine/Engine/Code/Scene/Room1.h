#pragma once

#include "Scene.h"
#include "../UI/UINormal.h"  
#include "../UI/UIElement.h"  
#include "../Input/Input.h"
#include "../Engine.h"
#include <glm/glm.hpp>
#include <iostream>
#include "../Dialogue/DialogueBox.h"
#include <memory>

class Room1 : public Scene {
public:

    Room1() {

        // Create a UIElement instead of RenderGameObject for the cabin
        UIElement* room = new UINormal("cabin1", "Assets/Images/passenger_room1.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(20.0f, 12.0f, 0.0f),true);

        //GameObject* room = new RenderGameObject("cabin1", "Assets/Images/passenger_room1.png");
        dialogueBox = std::make_unique<DialogueBox>(
            "DialogueBox",
            "Assets/Images/DialogueBox.png", // Texture for the dialogue box
            "Assets/Fonts/WD.ttf", // Font for the text
            glm::vec3(50, 50, 0), // Position of the dialogue box
            glm::vec3(300, 150, 1), // Scale of the dialogue box
            true, // It should be rendered on screen space
            "Welcome to Room 1!", // Initial text
            glm::vec3(70, 80, 0), // Text position relative to the box
            1.0f, // Text scale
            glm::vec3(1.0f, 1.0f, 1.0f) // Text color
        );
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
            dialogueBox->SetText("You pressed T!");
        }

        // Use the UIElement for cabin interaction
        GameObject* cabinObject = GetGameObjectByName("cabin1");
        if (cabinObject) {
            UIElement* cabin = dynamic_cast<UIElement*>(cabinObject);
            if (cabin) {
                // Get the player's position
                glm::vec3 camPos = glm::vec3(camera.GetPosX(), camera.GetPosY(), 0.0f);
                cabin->SetPosition(camPos);
            }
        }
    }

    void Render() override {
        Scene::Render(); // Render other game objects
        dialogueBox->Render(); // Render the dialogue box
    }

private:
    Input& input = Application::GetInput();
    Camera& camera = Application::GetCamera();
    std::unique_ptr<DialogueBox> dialogueBox;
};
