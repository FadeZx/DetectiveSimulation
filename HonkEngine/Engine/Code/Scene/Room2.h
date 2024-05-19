#pragma once

#include "Scene.h"
#include "../UI/UINormal.h"  
#include "../UI/UIButton.h" 
#include "../UI/UIElement.h"  
#include "../Input/Input.h"
#include "../Engine.h"
#include <glm/glm.hpp>
#include <iostream>
#include "../Dialogue/Dialoguemanager.h"
#include "../Effects/ObjectsParallax.h"
#include "../Effects/BackgroundParallax.h"
#include "../GameObjects/Timer.h"
#include "../GameObjects/CharacterData.h"
#include <memory>

using namespace std;


class Room2 : public Scene {

private:
    CharacterData* characterData = CharacterData::GetInstance();
    AudioManager& audioManager;
    Timer* timer;
    Text* instructionText;
    GameStateManager& gameStateManager = GameStateManager::GetInstance();
    Door* door = DoorManager::GetInstance().GetDoorByName("Room2Door");
    Door* kichenDoor = DoorManager::GetInstance().GetDoorByName("KitchenDoor");


    UIElement* medicineFront;
    UIButton* medicineFrontInspect;
    UIElement* hat;
    UIButton* hatInspect;
    UIElement* bag;
    UIButton* bagInspect;

public:
    Room2() :audioManager(AudioManager::GetInstance()) {

        timer = &Timer::GetInstance();

        audioManager.LoadSound("cabinMusic", "Assets/Sounds/Music/BGmusic_Cabin.mp3", 5.0f);
        audioManager.LoadSound("knockDoor", "Assets/Sounds/SFX_KnockDoor.mp3", 2.0f);
        audioManager.LoadSound("slideDoor", "Assets/Sounds/SFX_SlideDoor.mp3", 2.5f);

        GameObject* background1a = new RenderGameObject("BG1", "Assets/Images/BG/Cabin_Background_01.png");
        GameObject* background2a = new RenderGameObject("BG2", "Assets/Images/BG/Cabin_Background_02.png");
        GameObject* background3a = new RenderGameObject("BG3", "Assets/Images/BG/Cabin_Background_03.png");
        GameObject* background4a = new RenderGameObject("BG3", "Assets/Images/BG/Cabin_Background_04.png");
        GameObject* background5a = new RenderGameObject("BG3", "Assets/Images/BG/Cabin_Background_05.png");
        GameObject* background6a = new RenderGameObject("BG3", "Assets/Images/BG/Cabin_Background_06.png");

        GameObject* background1b = new RenderGameObject("BG1", "Assets/Images/BG/Cabin_Background_01.png");
        GameObject* background2b = new RenderGameObject("BG2", "Assets/Images/BG/Cabin_Background_02.png");
        GameObject* background3b = new RenderGameObject("BG3", "Assets/Images/BG/Cabin_Background_03.png");
        GameObject* background4b = new RenderGameObject("BG3", "Assets/Images/BG/Cabin_Background_04.png");
        GameObject* background5b = new RenderGameObject("BG3", "Assets/Images/BG/Cabin_Background_05.png");
        GameObject* background6b = new RenderGameObject("BG3", "Assets/Images/BG/Cabin_Background_06.png");

        background1a->SetScale(glm::vec3(76.6f, 10.8f, 0.0f)); background1a->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));
        background2a->SetScale(glm::vec3(76.6f, 10.8f, 0.0f)); background2a->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));
        background3a->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background3a->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));
        background4a->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background4a->SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
        background5a->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background5a->SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
        background6a->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background6a->SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));

        background1b->SetScale(glm::vec3(76.6f, 10.8f, 0.0f)); background1b->SetPosition(glm::vec3(76.6f, 3.0f, 0.0f));
        background2b->SetScale(glm::vec3(76.6f, 10.8f, 0.0f)); background2b->SetPosition(glm::vec3(76.6f, 3.0f, 0.0f));
        background3b->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background3b->SetPosition(glm::vec3(76.6f, 3.0f, 0.0f));
        background4b->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background4b->SetPosition(glm::vec3(76.6f, 2.0f, 0.0f));
        background5b->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background5b->SetPosition(glm::vec3(76.6f, 2.0f, 0.0f));
        background6b->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background6b->SetPosition(glm::vec3(76.6f, 1.0f, 0.0f));


        // Scale Multiplier to fit asset scale with screensize
        float sm = 1.23f;

        //Objects     
        UIElement* room = new UINormal("cabin2", "Assets/Images/Twins/Twin_Cabin.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(19.0f * sm, 10.55f * sm, 0.0f), true);
        UIElement* medicineBack = new UINormal("MedicineBack", "Assets/Images/Twins/Twin_Inspection_MedicineBack.png", glm::vec3(-6.4f, -2.9f, 0.0f), glm::vec3(3.44f / 4 * sm, 3.96f / 4 * sm, 0.0f), true);


        //Inspection Items
        medicineFront = new UINormal("MedicineFront", "Assets/Images/Twins/Twin_Inspection_MedicineFront.png", glm::vec3(-5.25f, -3.35f, 0.0f), glm::vec3(4.56f / 4 * sm, 1.76f / 4 * sm, 0.0f), true);
        hat = new UINormal("Hat", "Assets/Images/Twins/Twin_Inspection_Hat.png", glm::vec3(4.6f, -2.05f, 0.0f), glm::vec3(4.89f / 3 * sm, 4.05f / 3 * sm, 0.0f), true);
        bag = new UINormal("Bag", "Assets/Images/Twins/Twin_Inspection_Bag.png", glm::vec3(2.6f, -5.35f, 0.0f), glm::vec3(5.58f / 3 * sm, 4.92f / 3 * sm, 0.0f), true);


        //Inspection Item Buttons
        medicineFrontInspect = new UIButton("MedicineFront", "Assets/Images/Twins/Twin_Inspection_MedicineFront.png", glm::vec3(-5.25f, -3.35f, 0.0f), glm::vec3(4.56f / 4 * sm, 1.76f / 4 * sm, 0.0f), true, false, "");
        medicineFrontInspect->SetHoverTexture("Assets/Images/Twins/Twin_Inspection_MedicineFront_Highlight.png");
        medicineFrontInspect->SetOnClickAction([this]() {
            std::cout << "MedicineFront button clicked." << std::endl;
            inspectingObject = "medicineFront";
            });
        hatInspect = new UIButton("HatInspect", "Assets/Images/Twins/Twin_Inspection_Hat.png", glm::vec3(4.6f, -2.05f, 0.0f), glm::vec3(4.89f / 3 * sm, 4.05f / 3 * sm, 0.0f), true, false, "");
        hatInspect->SetHoverTexture("Assets/Images/Twins/Twin_Inspection_Hat_Highlight.png");
        hatInspect->SetOnClickAction([this]() {
            std::cout << "Hat button clicked." << std::endl;
            inspectingObject = "Hat";
            });
        bagInspect = new UIButton("BagInspect", "Assets/Images/Twins/Twin_Inspection_Bag.png", glm::vec3(2.6f, -5.35f, 0.0f), glm::vec3(5.58f / 3 * sm, 4.92f / 3 * sm, 0.0f), true, false, "");
        bagInspect->SetHoverTexture("Assets/Images/Twins/Twin_Inspection_Bag_Highlight.png");
        bagInspect->SetOnClickAction([this]() {
            std::cout << "Bag button clicked." << std::endl;
            inspectingObject = "Bag";
            });

        medicineFrontInspect->setActiveStatus(false);
        hatInspect->setActiveStatus(false);
        bagInspect->setActiveStatus(false);

        //UIs
        //Speaker Sprite emotion
        UIElement* nathanielNormal = new UINormal("Nathaniel_Normal", "Assets/Images/Twins/Nathaniel_Normal.png", glm::vec3(-3.95f, -2.55f, 0.0f), glm::vec3(4.72f * sm, 6.19f * sm, 0.0f), true);
        UIElement* nathanielHappy = new UINormal("Nathaniel_Happy", "Assets/Images/Twins/Nathaniel_Happy.png", glm::vec3(-3.95f, -2.55f, 0.0f), glm::vec3(4.72f * sm, 6.19f * sm, 0.0f), true);
        UIElement* nathanielDisappoint = new UINormal("Nathaniel_Disappoint", "Assets/Images/Twins/Nathaniel_Disappoint.png", glm::vec3(-3.95f, -2.55f, 0.0f), glm::vec3(4.72f * sm, 6.19f * sm, 0.0f), true);
        UIElement* nathanielUpset = new UINormal("Nathaniel_Upset", "Assets/Images/Twins/Nathaniel_Upset.png", glm::vec3(-3.95f, -2.55f, 0.0f), glm::vec3(4.72f * sm, 6.19f * sm, 0.0f), true);
        UIElement* nathanielSad = new UINormal("Nathaniel_Sad", "Assets/Images/Twins/Nathaniel_Sad.png", glm::vec3(-3.95f, -2.55f, 0.0f), glm::vec3(4.72f * sm, 6.19f * sm, 0.0f), true);
        UIElement* nathanielShy = new UINormal("Nathaniel_Shy", "Assets/Images/Twins/Nathaniel_Shy.png", glm::vec3(-3.95f, -2.55f, 0.0f), glm::vec3(4.72f * sm, 6.19f * sm, 0.0f), true);

        UIElement* evelynNormal = new UINormal("Evelyn_Normal", "Assets/Images/Twins/Evelyn_Normal.png", glm::vec3(5.2f, -2.58f, 0.0f), glm::vec3(3.06f * sm, 5.87f * sm, 0.0f), true);
        UIElement* evelynHappy = new UINormal("Evelyn_Happy", "Assets/Images/Twins/Evelyn_Happy.png", glm::vec3(5.2f, -2.58f, 0.0f), glm::vec3(3.06f * sm, 5.87f * sm, 0.0f), true);
        UIElement* evelynDisappoint = new UINormal("Evelyn_Disappoint", "Assets/Images/Twins/Evelyn_Disappoint.png", glm::vec3(5.2f, -2.58f, 0.0f), glm::vec3(3.06f * sm, 5.87f * sm, 0.0f), true);
        UIElement* evelynUpset = new UINormal("Evelyn_Upset", "Assets/Images/Twins/Evelyn_Upset.png", glm::vec3(5.2f, -2.58f, 0.0f), glm::vec3(3.06f * sm, 5.87f * sm, 0.0f), true);
        UIElement* evelynSad = new UINormal("Evelyn_Sad", "Assets/Images/Twins/Evelyn_Sad.png", glm::vec3(5.2f, -2.58f, 0.0f), glm::vec3(3.06f * sm, 5.87f * sm, 0.0f), true);
        UIElement* evelynShy = new UINormal("Evelyn_Shy", "Assets/Images/Twins/Evelyn_Shy.png", glm::vec3(5.2f, -2.58f, 0.0f), glm::vec3(3.06f * sm, 5.87f * sm, 0.0f), true);

        //Dialogue Box
        UIButton* dialogueBox = new UIButton("DialogueBox", "Assets/Images/UI/DialogueBox.png",
            glm::vec3(0.0f, 3.5f, 0.0f), glm::vec3(10.96f, 2.05f, 0.0f),
            true, true, "Assets/Fonts/OverpassMono.ttf");

        //Choices
        UIButton* dialogueChoice1 = new UIButton("DialogueChoiceBox1", "Assets/Images/UI/DialogueChoiceBox.png",
            glm::vec3(0.0f, -2.8f, 0.0f), glm::vec3(7.47f * 0.9f, 1.07f * 0.9f, 0.0f),
            true, true, "Assets/Fonts/OverpassMono-SemiBold.ttf");
        UIButton* dialogueChoice2 = new UIButton("DialogueChoiceBox2", "Assets/Images/UI/DialogueChoiceBox.png",
            glm::vec3(0.0f, -3.8f, 0.0f), glm::vec3(7.47f * 0.9f, 1.07f * 0.9f, 0.0f),
            true, true, "Assets/Fonts/OverpassMono-SemiBold.ttf");
        UIButton* dialogueChoice3 = new UIButton("DialogueChoiceBox3", "Assets/Images/UI/DialogueChoiceBox.png",
            glm::vec3(0.0f, -1.8f, 0.0f), glm::vec3(7.47f * 0.9f, 1.07f * 0.9f, 0.0f),
            true, true, "Assets/Fonts/OverpassMono-SemiBold.ttf");

        dialogueChoice1->SetHoverTexture("Assets/Images/UI/DialogueChoiceBox_Hover.png");
        dialogueChoice2->SetHoverTexture("Assets/Images/UI/DialogueChoiceBox_Hover.png");
        dialogueChoice3->SetHoverTexture("Assets/Images/UI/DialogueChoiceBox_Hover.png");

        //Speak Icons
        UIElement* nathanielIcon = new UINormal("NathanielIcon", "Assets/Images/UI/Speaker_icon_Nathaniel.png", glm::vec3(4.1f, 3.49f, 0.0f), glm::vec3(1.45f, 1.51f, 0.0f), true);
        UIElement* eyelynIcon = new UINormal("EvelynIcon", "Assets/Images/UI/Speaker_icon_Evelyn.png", glm::vec3(4.14f, 3.49f, 0.0f), glm::vec3(1.57f, 1.5f, 0.0f), true);
        UIElement* waiterIcon = new UINormal("WaiterIcon", "Assets/Images/UI/Speaker_icon_Waiter.png", glm::vec3(4.18f, 3.43f, 0.0f), glm::vec3(1.23f, 1.4f, 0.0f), true);

        dialogueManager = make_unique<DialogueManager>("TwinDialogue", dialogueBox, "Nathaniel_Normal","Evelyn_Normal");
        dialogueManager->LoadDialogues("Order", "Assets/Dialogue/Twin/MealResult/Twin_MealResult_Informative.xml");

        //Text
        instructionText = new Text("dialogueinstruction", "Use [Left-click] or [Space] to continue dialogue", "Assets/Fonts/mvboli.ttf", true);
        instructionText->SetScale(0.6f);
        instructionText->SetPosition(glm::vec3(5.9f, -4.8f, 0.0f));
        instructionText->SetColor(glm::vec3(1, 1, 1));

        //Add SpeakSprite1
        dialogueManager->AddSpeakerSprite("Nathaniel_Normal", nathanielNormal);
        dialogueManager->AddSpeakerSprite("Nathaniel_Happy", nathanielHappy);
        dialogueManager->AddSpeakerSprite("Nathaniel_Disappoint", nathanielDisappoint);
        dialogueManager->AddSpeakerSprite("Nathaniel_Upset", nathanielUpset);
        dialogueManager->AddSpeakerSprite("Nathaniel_Sad", nathanielSad);
        dialogueManager->AddSpeakerSprite("Nathaniel_Shy", nathanielShy);

        //Add SpeakSprite2
        dialogueManager->AddSpeakerSprite2("Evelyn_Normal", evelynNormal);
        dialogueManager->AddSpeakerSprite2("Evelyn_Happy", evelynHappy);
        dialogueManager->AddSpeakerSprite2("Evelyn_Disappoint", evelynDisappoint);
        dialogueManager->AddSpeakerSprite2("Evelyn_Upset", evelynUpset);
        dialogueManager->AddSpeakerSprite2("Evelyn_Sad", evelynSad);
        dialogueManager->AddSpeakerSprite2("Evelyn_Shy", evelynShy);

        //Add SpeakerIcon
        dialogueManager->AddSpeakerIcon("N", nathanielIcon);
        dialogueManager->AddSpeakerIcon("E", eyelynIcon);
        dialogueManager->AddSpeakerIcon("W", waiterIcon);
        //Add ChoiceButton
        dialogueManager->AddChoiceButton(dialogueChoice1);
        dialogueManager->AddChoiceButton(dialogueChoice2);
        dialogueManager->AddChoiceButton(dialogueChoice3);


        //setDialogueUI
        dialogueManager->SetDialoguePosition(-0.5f, 3.6f);
        dialogueManager->SetDialogueScale(0.55f);
        dialogueManager->SetChoiceScale(0.56f);

        //Push GamePbjects
        m_gameObjects.push_back(background1a);
        m_gameObjects.push_back(background1b);
        m_gameObjects.push_back(background2a);
        m_gameObjects.push_back(background2b);
        m_gameObjects.push_back(background3a);
        m_gameObjects.push_back(background3b);
        m_gameObjects.push_back(background4a);
        m_gameObjects.push_back(background4b);
        m_gameObjects.push_back(background5a);
        m_gameObjects.push_back(background5b);
        m_gameObjects.push_back(background6a);
        m_gameObjects.push_back(background6b);
        m_gameObjects.push_back(room);
        m_gameObjects.push_back(medicineBack);


        m_gameObjects.push_back(bag);
        m_gameObjects.push_back(bagInspect);

        m_gameObjects.push_back(nathanielNormal);
        m_gameObjects.push_back(nathanielHappy);
        m_gameObjects.push_back(nathanielDisappoint);
        m_gameObjects.push_back(nathanielUpset);
        m_gameObjects.push_back(nathanielSad);
        m_gameObjects.push_back(nathanielShy);

        m_gameObjects.push_back(medicineFront);
        m_gameObjects.push_back(medicineFrontInspect);

        m_gameObjects.push_back(evelynNormal);
        m_gameObjects.push_back(evelynHappy);
        m_gameObjects.push_back(evelynDisappoint);
        m_gameObjects.push_back(evelynUpset);
        m_gameObjects.push_back(evelynSad);
        m_gameObjects.push_back(evelynShy);

        m_gameObjects.push_back(hat);
        m_gameObjects.push_back(hatInspect);

        m_gameObjects.push_back(dialogueBox);
        m_gameObjects.push_back(dialogueChoice1);
        m_gameObjects.push_back(dialogueChoice2);
        m_gameObjects.push_back(dialogueChoice3);
        m_gameObjects.push_back(nathanielIcon);
        m_gameObjects.push_back(eyelynIcon);
        m_gameObjects.push_back(waiterIcon);
        m_gameObjects.push_back(instructionText);

        //add Parallax Effects
        ObjectsparallaxManager = make_unique<ObjectsParallax>();
        backgroundParallaxManager = std::make_unique<BackgroundParallax>();

        float defaultLayer = 0.8f;
        float objectLayerOne = 0.83f;

        // Add objects to different layers
        ObjectsparallaxManager->AddObjectToLayer(room, defaultLayer);   // Layer 1
        ObjectsparallaxManager->AddObjectToLayer(hat, objectLayerOne);    // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(bag, objectLayerOne);    // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(medicineBack, objectLayerOne);   // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(medicineFront, objectLayerOne);   // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(nathanielNormal, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(nathanielHappy, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(nathanielDisappoint, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(nathanielUpset, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(nathanielSad, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(nathanielShy, objectLayerOne); // Layer 2

        ObjectsparallaxManager->AddObjectToLayer(evelynNormal, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(evelynHappy, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(evelynDisappoint, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(evelynUpset, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(evelynShy, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(evelynShy, objectLayerOne); // Layer 2

        //Scrolling effect for Background
        backgroundParallaxManager->AddBackgroundPair(0, background1a, background1b, 0.5f); // Layer 0, slower
        backgroundParallaxManager->AddBackgroundPair(1, background2a, background2b, 1.0f); // Layer 1, normal
        backgroundParallaxManager->AddBackgroundPair(2, background3a, background3b, 1.5f); // Layer 2, faster
        backgroundParallaxManager->AddBackgroundPair(3, background4a, background4b, 2.0f); // Layer 3, fastest
        backgroundParallaxManager->AddBackgroundPair(4, background5a, background5b, 2.5f); // Layer 4, fastest
        backgroundParallaxManager->AddBackgroundPair(5, background6a, background6b, 3.0f); // Layer 5, fastest


    }

    void OnEnter() override {
        //Scene::OnEnter();  // Call base class if there's relevant logic  
        audioManager.PlaySound("cabinMusic", true);
        if (gameStateManager.getRoomState() == RoomState::Prepare && KitchenData::GetInstance()->checkCompletePlate())
        {
            GameStateManager::GetInstance().SetRoomState(RoomState::Serve);
        }
        SetSequencesDialogue();
    }


    void SetSequencesDialogue()
    {
        switch (gameStateManager.getRoomState()) {
        case RoomState::Order:
            dialogueManager->SetDialogueSet("Order");
            orderDialogueKey = "Order";
            break;
        case RoomState::Serve:

            if (characterData->getServeTimeLevel(Cabin::CABIN21) == ONTIME) {
                serveDialogueKey = "Serve_OnTime";
            }
            else {
                serveDialogueKey = "Serve_Late";
            }
            dialogueManager->SetDialogueSet(serveDialogueKey);
            std::cout << "Setting serve dialogue: " << serveDialogueKey << std::endl;

            // Reset flags
            teaDialogueSet = false;
            sandwichDialogueSet = false;
            dessertDialogueSet = false;
            SetMealReactionDialogue();
            //SetScoredDialogue();
            //SetInteractDialogue();

            break;
        }
    }

    void SetMealReactionDialogue() {

        // Get instance of KitchenData to access the player's choices
        KitchenData* kitchen = KitchenData::GetInstance();

        // Determine the dialogue key based on the tea choice as an example
        switch (kitchen->getTea()) {

        case EARLGREYTEA:
            dialogueManager->LoadDialogues("MealReact_Tea_EarlGray", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Tea_Assam_EarlGray.xml");
            teaDialogueKey = "MealReact_Tea_EarlGray";
            break;
        case ASSAMTEA:
            dialogueManager->LoadDialogues("MealReact_Tea_Assam", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Tea_Assam_EarlGray.xml");
            teaDialogueKey = "MealReact_Tea_Assam";
            break;
        case CHAMOMILETEA:
            dialogueManager->LoadDialogues("MealReact_Tea_Charmomile", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Tea_Chamomile.xml");
            teaDialogueKey = "MealReact_Tea_Charmomile";
            break;
        case GREENTEA:
            dialogueManager->LoadDialogues("MealReact_Tea_GreenTea", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Tea_GreenTea.xml");
            teaDialogueKey = "MealReact_Tea_GreenTea";
            break;
        }

        switch (kitchen->getSandwich()) {
        case SALMON:
            dialogueManager->LoadDialogues("MealReact_Sandwich_Salmon", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Sandwich_Salmon_Beef.xml");
            sandwichDialogueKey = "MealReact_Sandwich_Salmon";
            break;
        case BEEF:
            dialogueManager->LoadDialogues("MealReact_Sandwich_Salmon", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Sandwich_Salmon_Beef.xml");
            sandwichDialogueKey = "MealReact_Sandwich_Salmon";
            break;
        case EGG:
            dialogueManager->LoadDialogues("MealReact_Sandwich_Egg", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Sandwich_Egg.xml");
            sandwichDialogueKey = "MealReact_Sandwich_Egg";
            break;
        case CUCUMBER:
            dialogueManager->LoadDialogues("MealReact_Sandwich_Cucumber", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Sandwich_Cucumber.xml");
            sandwichDialogueKey = "MealReact_Sandwich_Cucumber";
            break;
        }

        switch (kitchen->getDessert()) {
        case ECLAIR:
            dialogueManager->LoadDialogues("MealReact_Dessert_Eclair", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Pastry_Eclair_Macaron_Tart.xml");
            dessertDialogueKey = "MealReact_Dessert_Eclair";
            break;
        case MACARON:
            dialogueManager->LoadDialogues("MealReact_Dessert_Macaron", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Pastry_Eclair_Macaron_Tart.xml");
            dessertDialogueKey = "MealReact_Dessert_Macaron";
            break;
        case TART:
            dialogueManager->LoadDialogues("MealReact_Dessert_Tart", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Pastry_Eclair_Macaron_Tart.xml");
            dessertDialogueKey = "MealReact_Dessert_Tart";
            break;
        case SCONE:
            dialogueManager->LoadDialogues("MealReact_Dessert_Scone", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Pastry_Scone.xml");
            dessertDialogueKey = "MealReact_Dessert_Scone";
            break;
        }

        std::cout << "Tea Dialogue Key set to: " << teaDialogueKey << std::endl;
        std::cout << "Sandwich Dialogue Key set to: " << sandwichDialogueKey << std::endl;
        std::cout << "Dessert Dialogue Key set to: " << dessertDialogueKey << std::endl;
    }


    void Update(float dt, long frame) override {

        Scene::Update(dt, frame);
        backgroundParallaxManager->Update(dt);
        ObjectsparallaxManager->UpdateLayers();
        dialogueManager->Update(dt, frame);

        UpdateDialogueProgress();
        HandleKeyInputs();


    }

     void UpdateDialogueProgress() {
            // Manage different room states
            if (gameStateManager.getGameState() != GameState::ROOM1_STATE) return;

            switch (gameStateManager.getRoomState()) {
            case RoomState::Order:
                UpdateRoomState("Order", RoomState::Prepare);
                break;
            case RoomState::Serve:
                //ManageServeState();
                break;
            case RoomState::Score:
                //ManageScoreState();
                break;
            case RoomState::MealReact:
                //ManageMealReactions();
                break;
            case RoomState::InspectionStart:
                //ManageInspectionStartState();
                break;
            case RoomState::Inspection:
                //ManageInspectionState();
                break;
            case RoomState::InspectionEnd:
                //ManageInspectionEndState();

                break;
            }
     }

     void UpdateRoomState(const string& currentDialogueKey, RoomState nextState) {
         if (dialogueManager->IsDialogueFinished(currentDialogueKey)) {
             SetInstruction("Press [E] to leave");
             if (input.Get().GetKeyDown(GLFW_KEY_E)) {
                 gameStateManager.SetRoomState(nextState);
             }
         }
     }

    void PromptForNextDialogue(const string& nextKey, bool& flag) {
        SetInstruction("Press [Space] or [Mouse] to continue.");
        if (!flag && (input.Get().GetKeyDown(GLFW_KEY_SPACE) || input.Get().GetMouseButtonDown(0))) {
            dialogueManager->SetDialogueSet(nextKey);
            flag = true;
        }
    }

    void SetInstruction(const string& message) {
        instructionText->SetContent(message);
    }

    void HandleKeyInputs() {
        if (input.Get().GetKeyDown(GLFW_KEY_SPACE) || input.Get().GetMouseButtonDown(0)) {
            dialogueManager->PlayNextDialogue();
        }
    }

    void Render() override {
        Scene::Render(); // Renders GameObjects

        // Manually call DialogueManager's render function
        dialogueManager->Render();
    }

    void OnExit() override {
        // Scene::OnExit();  // Call base class if there's relevant logic
        audioManager.PlaySound("slideDoor");
        audioManager.PauseSound("cabinMusic");
        BellManager::GetInstance().StopAllRinging();
    }

private:
    Input& input = Application::GetInput();
    Camera& camera = Application::GetCamera();
    unique_ptr<DialogueManager> dialogueManager;
    unique_ptr<ObjectsParallax> ObjectsparallaxManager;
    unique_ptr<BackgroundParallax> backgroundParallaxManager;
    string orderDialogueKey;
    string currentDialogueKey;
    string serveDialogueKey;
    string teaDialogueKey;
    string sandwichDialogueKey;
    string dessertDialogueKey;
    string scoreDialogueKey;
    string inspectStartDialogueKey;
    string inspectMedicineFrontDialogueKey;
    string inspectHatDialogueKey;
    string inspectBagDialogueKey;
    string inspectEndDialogueKey;

    bool orderDialogueSet = false;
    bool serveDialogueSet = false;
    bool teaDialogueSet = false;
    bool sandwichDialogueSet = false;
    bool dessertDialogueSet = false;
    bool scoreDialogueSet = false;
    bool inspectStartDialogueSet = false;
    bool inspectEndDialogueSet = false;
    bool inspectMedicineFrontDialogueSet = false;
    bool inspectHatDialogueSet = false;
    bool inspectBagDialogueSet = false;

    bool isMedicineFrontInspected = false;
    bool isHatInspected = false;
    bool isBagInspected = false;

    string inspectingObject;

};