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


class Room4 : public Scene {

private:
    CharacterData* characterData = CharacterData::GetInstance();
    AudioManager& audioManager;
    Timer* timer;
    Text* instructionText;
    GameStateManager& gameStateManager = GameStateManager::GetInstance();
    Door* door = DoorManager::GetInstance().GetDoorByName("Room4Door");
    Door* kichenDoor = DoorManager::GetInstance().GetDoorByName("KitchenDoor");


    UIElement* pamphlet;
    UIButton* pamphletInspect;
    UIElement* dagger;
    UIButton* daggerInspect;
    UIElement* bag;
    UIButton* bagInspect;

public:
    Room4() :audioManager(AudioManager::GetInstance()) {

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
        UIElement* room = new UINormal("Cabin4", "Assets/Images/Octavia/Octavia_Cabin.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(19.0f * sm, 10.55f * sm, 0.0f), true);
        UIElement* bag = new UINormal("Bag", "Assets/Images/Octavia/Octavia_Bag.png", glm::vec3(-1.7f, -4.85f, 0.0f), glm::vec3(3.75f * sm, 2.7f * sm, 0.0f), true);


        //Inspection Items
        pamphlet = new UINormal("OperaPamphlet", "Assets/Images/Octavia/Octavia_Inspection_Pamphlet.png",    glm::vec3(0.42f, 1.9f, 0.0f),   glm::vec3(5.88f / 4 * sm, 7.4f / 4 * sm, 0.0f), true);
        dagger = new UINormal("Dagger", "Assets/Images/Octavia/Octavia_Inspection_Dagger.png",               glm::vec3(-5.925f, 2.95f, 0.0f),   glm::vec3(2.72f / 4 * sm, 4.44f / 4 * sm, 0.0f), true);


        //Inspection Item Buttons
        pamphletInspect = new UIButton("OperaPamphlet", "Assets/Images/Octavia/Octavia_Inspection_Pamphlet.png", glm::vec3(0.42f, 1.9f, 0.0f), glm::vec3(5.88f / 4 * sm, 7.4f / 4 * sm, 0.0f), true, false, "");
        pamphletInspect->SetHoverTexture("Assets/Images/Octavia/Octavia_Inspection_Pamphlet_Highlight.png");
        pamphletInspect->SetOnClickAction([this]() {
            std::cout << "OperaPamphlet button clicked." << std::endl;
            inspectingObject = "pamphlet";
            });
        daggerInspect = new UIButton("HatInspect", "Assets/Images/Octavia/Octavia_Inspection_Dagger.png", glm::vec3(-5.925f, 2.95f, 0.0f), glm::vec3(2.72f / 4 * sm, 4.44f / 4 * sm, 0.0f), true, false, "");
        daggerInspect->SetHoverTexture("Assets/Images/Octavia/Octavia_Inspection_Dagger_Highlight.png");
        daggerInspect->SetOnClickAction([this]() {
            std::cout << "Dagger button clicked." << std::endl;
            inspectingObject = "dagger";
            });

        pamphletInspect->setActiveStatus(false);
        daggerInspect->setActiveStatus(false);

        //UIs
        //Speaker Sprite emotion
        UIElement* octaviaNormal = new UINormal("Octavia_Normal", "Assets/Images/Octavia/Octavia_Normal.png",                   glm::vec3(4.4f, -1.7f, 0.0f), glm::vec3(6.05f * sm, 7.76f * sm, 0.0f), true);
        UIElement* octaviaHappy = new UINormal("Octavia_Happy", "Assets/Images/Octavia/Octavia_Happy.png",                      glm::vec3(4.4f, -1.7f, 0.0f), glm::vec3(6.05f * sm, 7.76f * sm, 0.0f), true);
        UIElement* octaviaHappy2 = new UINormal("Octavia_Happy2", "Assets/Images/Octavia/Octavia_Happy2.png",                   glm::vec3(4.4f, -1.7f, 0.0f), glm::vec3(6.05f * sm, 7.76f * sm, 0.0f), true);
        UIElement* octaviaDisappoint = new UINormal("Octavia_Disappoint", "Assets/Images/Octavia/Octavia_Disappoint.png",       glm::vec3(4.4f, -1.7f, 0.0f), glm::vec3(6.05f * sm, 7.76f * sm, 0.0f), true);
        UIElement* octaviaUpset = new UINormal("Octavia_Upset", "Assets/Images/Octavia/Octavia_Upset.png",                      glm::vec3(4.4f, -1.7f, 0.0f), glm::vec3(6.05f * sm, 7.76f * sm, 0.0f), true);
        UIElement* octaviaSad = new UINormal("Octavia_Sad", "Assets/Images/Octavia/Octavia_Sad.png",                            glm::vec3(4.4f, -1.7f, 0.0f), glm::vec3(6.05f * sm, 7.76f * sm, 0.0f), true);
        UIElement* octaviaSurprise = new UINormal("Octavia_Surprise", "Assets/Images/Octavia/Octavia_Surprise.png",             glm::vec3(4.4f, -1.7f, 0.0f), glm::vec3(6.05f * sm, 7.76f * sm, 0.0f), true);


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
        UIElement* octaviaIcon = new UINormal("OctaviaIcon", "Assets/Images/UI/Speaker_icon_Octavia.png", glm::vec3(4.14f, 3.52f, 0.0f), glm::vec3(1.92f, 1.62f, 0.0f), true);
        UIElement* waiterIcon = new UINormal("WaiterIcon", "Assets/Images/UI/Speaker_icon_Waiter.png", glm::vec3(4.18f, 3.43f, 0.0f), glm::vec3(1.23f, 1.4f, 0.0f), true);

        dialogueManager = make_unique<DialogueManager>("OctaviaDialogue", dialogueBox, "Octavia_Normal");
        dialogueManager->LoadDialogues("Order", "Assets/Dialogue/Octavia/Octavia_Order.xml");
        //Text
        instructionText = new Text("dialogueinstruction", "Use [Left-click] or [Space] to continue dialogue", "Assets/Fonts/mvboli.ttf", true);
        instructionText->SetScale(0.6f);
        instructionText->SetPosition(glm::vec3(5.9f, -4.8f, 0.0f));
        instructionText->SetColor(glm::vec3(1, 1, 1));

        //Add SpeakSprite
        dialogueManager->AddSpeakerSprite("Octavia_Normal", octaviaNormal);
        dialogueManager->AddSpeakerSprite("Octavia_Happy", octaviaHappy);
        dialogueManager->AddSpeakerSprite("Octavia_Happy2", octaviaHappy2);
        dialogueManager->AddSpeakerSprite("Octavia_Disappoint", octaviaDisappoint);
        dialogueManager->AddSpeakerSprite("Octavia_Upset", octaviaUpset);
        dialogueManager->AddSpeakerSprite("Octavia_Sad", octaviaSad);
        dialogueManager->AddSpeakerSprite("Octavia_Shy", octaviaSurprise);


        //Add SpeakerIcon
        dialogueManager->AddSpeakerIcon("O", octaviaIcon);
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
        m_gameObjects.push_back(bag);

        m_gameObjects.push_back(dagger);
        m_gameObjects.push_back(daggerInspect);

        m_gameObjects.push_back(pamphlet);
        m_gameObjects.push_back(pamphletInspect);

        m_gameObjects.push_back(octaviaNormal);
        m_gameObjects.push_back(octaviaHappy);
        m_gameObjects.push_back(octaviaHappy2);
        m_gameObjects.push_back(octaviaDisappoint);
        m_gameObjects.push_back(octaviaUpset);
        m_gameObjects.push_back(octaviaSad);
        m_gameObjects.push_back(octaviaSurprise);


        m_gameObjects.push_back(dialogueBox);
        m_gameObjects.push_back(dialogueChoice1);
        m_gameObjects.push_back(dialogueChoice2);
        m_gameObjects.push_back(dialogueChoice3);
        m_gameObjects.push_back(octaviaIcon);
        m_gameObjects.push_back(waiterIcon);
        m_gameObjects.push_back(instructionText);

        //add Parallax Effects
        ObjectsparallaxManager = make_unique<ObjectsParallax>();
        backgroundParallaxManager = std::make_unique<BackgroundParallax>();

        float defaultLayer = 0.8f;
        float objectLayerOne = 0.83f;

        // Add objects to different layers
        ObjectsparallaxManager->AddObjectToLayer(room, defaultLayer);   // Layer 1
        ObjectsparallaxManager->AddObjectToLayer(dagger, objectLayerOne);    // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(bag, objectLayerOne);    // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(bag, objectLayerOne);   // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(pamphlet, objectLayerOne);   // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(octaviaNormal, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(octaviaHappy, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(octaviaHappy2, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(octaviaDisappoint, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(octaviaUpset, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(octaviaSad, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(octaviaSurprise, objectLayerOne); // Layer 2


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