#pragma once

#include "tinyxml2.h"
#include <string>
#include <vector>
#include <memory>
#include<iostream>

struct Dialogue {
    int id;
    std::string text;
};

class DialogueManager {
public:
    DialogueManager() : currentDialogueIndex(0) {}

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
    }

    void DisplayCurrentDialogue() {
        if (currentDialogueIndex < dialogues.size()) {
            const auto& dialogue = dialogues[currentDialogueIndex];
            // Assuming you have a method to display text. This is just a placeholder.
            DisplayText(dialogue.text); // Implement this function to work with your text system
        }
    }

    void NextDialogue() {
        if (currentDialogueIndex < dialogues.size() - 1) {
            ++currentDialogueIndex;
        }
        else {
            // End of dialogues or loop back to the start
            currentDialogueIndex = 0; // Or handle the end of dialogues as needed
        }
    }

private:
    std::vector<Dialogue> dialogues;
    size_t currentDialogueIndex;

    void DisplayText(const std::string& text) {
        // Integrate with your existing text rendering system
        std::cout << text << std::endl; // Placeholder for actual text rendering
    }
};
