#pragma once

#include "tinyxml2.h"
#include "../GameObjects/GameObject.h"
#include "../Text/Text.h" 
#include <string>
#include <vector>
#include <memory>
#include<iostream>

struct Dialogue {
    int id;
    std::string text;
};

class DialogueManager : public GameObject {
public:

    DialogueManager(const std::string& name, const std::string& fontPath, const std::string& filePath)
        : GameObject(name){
        LoadDialogues(filePath);
        if (!dialogues.empty()) {
            // Initialize the Text object with the first dialogue
            currentText = std::make_shared<Text>("DialogueText", dialogues[currentDialogueIndex].text, fontPath);
        }
    }

    void LoadDialogues(const std::string& filePath) {
        tinyxml2::XMLDocument doc;
        if (doc.LoadFile(filePath.c_str()) == tinyxml2::XML_SUCCESS) {
            tinyxml2::XMLElement* root = doc.FirstChildElement("Dialogues");
            for (tinyxml2::XMLElement* element = root->FirstChildElement("Dialogue"); element != nullptr; element = element->NextSiblingElement("Dialogue")) {
                Dialogue dialogue;
                dialogue.id = element->IntAttribute("id");
                dialogue.text = element->FirstChildElement("Text")->GetText();
                dialogues.push_back(dialogue);
            }
        }
        std::cout << "Loaded " << dialogues.size() << " dialogues." << std::endl;
    }

    // Override Render method from GameObject
    virtual void Render() override {
        if (currentText) {
            currentText->Render();
        }
    }

    void PlayNextDialogue() {
        std::cout << "Loaded " << dialogues.size() << " dialogues." << std::endl;
        if (currentDialogueIndex < dialogues.size()) {
            // Move to the next dialogue
            currentDialogueIndex++;

            // Loop back to the first dialogue if we've reached the end
            if (currentDialogueIndex >= dialogues.size()) {
                currentDialogueIndex = 0;
            }

            // Update the content of the current Text object
            currentText->SetContent(dialogues[currentDialogueIndex].text);
            std::cout << "Dialogue ID: " << dialogues[currentDialogueIndex].id << " - Text: " << dialogues[currentDialogueIndex].text << std::endl;
        }
    }



private:
    std::vector<Dialogue> dialogues;
    std::shared_ptr<Text> currentText; // Single Text object for display
    size_t currentDialogueIndex = 0;
    std::string fontPath; // Path to the font used for dialogues
};
