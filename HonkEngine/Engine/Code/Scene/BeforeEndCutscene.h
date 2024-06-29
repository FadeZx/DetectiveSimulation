#pragma once

#include "Scene.h"
#include <memory>
#include "../GameObjects/RenderGameObject.h"
#include "../GameObjects/AnimateGameObject.h"
#include "../Dialogue/Dialoguemanager.h"
#include "../Text/Text.h"
#include "../UI/UIElement.h"
#include "../Application.h"

class BeforeEndCutscene : public Scene {

private:
    Input& input = Application::GetInput();
    unique_ptr<DialogueManager> dialogueManager;
    AudioManager& audioManager;

    std::vector<UIObject*> scenes;
    std::vector<std::string> dialogueKeys = { "scene1", "scene2" };
    UIElement* transitionObject;
    std::unique_ptr<TransitionEffects> transitionEffects;
    Text* instructionText;
    int currentSceneIndex = 0;
    bool isTransitioning = false;
    bool isFadingOut = false;
    float transitionProgress = 0.0f;
    const float transitionDuration = 0.5f;

public:

    BeforeEndCutscene() :audioManager(AudioManager::GetInstance())
    {
        GameObject* SceneBackground = new UIObject("EndScene1", "Assets/Images/Opening/Opening_Cutscene_4.jpg", true);
        SceneBackground->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
        scenes.push_back(static_cast<UIObject*>(SceneBackground));

        GameObject* SceneBackground2 = new UIObject("EndScene2", "Assets/Images/Opening/Opening_Cutscene_2.jpg", true);
        SceneBackground2->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
        scenes.push_back(static_cast<UIObject*>(SceneBackground2));


        // Create dialogue manager
        UIButton* dialogueBox = new UIButton("DialogueBox", "", glm::vec3(0.0f, -4.5f, 0.0f), glm::vec3(10.96f, 2.05f, 0.0f), true, true, "Assets/Fonts/OverpassMono-SemiBold.ttf");
        dialogueBox->SetTextSize(0.55f);
        dialogueBox->SetTextColor(glm::vec3(1, 1, 1));

        dialogueManager = unique_ptr<DialogueManager>(new DialogueManager("BeforeEndCutscene1", dialogueBox, ""));
        dialogueManager->LoadDialogues("scene1", "Assets/Dialogue/Ending/BeforeEndCutscene1.xml");
        dialogueManager->LoadDialogues("scene2", "Assets/Dialogue/Ending/BeforeEndCutscene2.xml");


        instructionText = new Text("dialogueinstruction", "Use [Left-click] or [Space] to continue", "Assets/Fonts/mvboli.ttf", true);
        instructionText->SetScale(0.4f);
        instructionText->SetPosition(glm::vec3(7.0f, -5.0f, 0.0f));
        instructionText->SetColor(glm::vec3(1, 1, 1));

        transitionObject = new UINormal("Transition", "Assets/Images/black.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(25.0f, 20.0f, 0.0f), true);
        transitionEffects = std::unique_ptr<TransitionEffects>(new TransitionEffects(transitionObject));

        SceneBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        SceneBackground2->SetPosition(glm::vec3(0.0f, 10.8f, 0.0f));

        m_gameObjects.push_back(SceneBackground);
        m_gameObjects.push_back(SceneBackground2);
        m_gameObjects.push_back(dialogueBox);
        m_gameObjects.push_back(instructionText);
        m_gameObjects.push_back(transitionObject);
    }

    void OnEnter() override {
        ResetScene(); // Reset the scene state on entry
        audioManager.StopSound("trainAmbience");
        transitionEffects->FadeIn(2.0f);
    }

    /*void OnExit() override {
        audioManager.StopSound("OpenSceneBGMusic");

    }*/

    void Update(float dt, long frame) override {
        Scene::Update(dt, frame);
        transitionEffects->Update(dt);

        if (isTransitioning) {
            transitionProgress += dt / transitionDuration;
            if (transitionProgress >= 1.0f) {
                transitionProgress = 1.0f;
                isTransitioning = false;
                scenes[currentSceneIndex]->setActiveStatus(true);
                dialogueManager->SetDialogueSet(dialogueKeys[currentSceneIndex]);
            }

            float prevY = glm::mix(0.0f, -10.8f, transitionProgress);
            float nextY = glm::mix(10.8f, 0.0f, transitionProgress);

            if (currentSceneIndex > 0) {
                scenes[currentSceneIndex - 1]->SetPosition(glm::vec3(0.0f, prevY, 0.0f));
            }
            scenes[currentSceneIndex]->SetPosition(glm::vec3(0.0f, nextY, 0.0f));
        }
        else if (!isFadingOut) { // Prevent actions during fade-out
            if (input.Get().GetKeyDown(GLFW_KEY_SPACE) || input.Get().GetMouseButtonDown(0)) {

                if (instructionText->getActiveStatus()) {
                    instructionText->setActiveStatus(false);
                }

                if (dialogueManager->IsDialogueFinished(dialogueKeys[currentSceneIndex])) {
                    if (currentSceneIndex + 1 < scenes.size()) {
                        StartSceneTransition(currentSceneIndex + 1);
                    }
                    else {
                        TransitionOut();
                    }
                }
                else {
                    dialogueManager->PlayNextDialogue();
                }
            }
        }

        dialogueManager->Update(dt, frame);
    }

    void TransitionOut()
    {
        isFadingOut = true;
        transitionEffects->FadeOut(2.0f, [this]() { Application::Get().SetScene("EndScene"); });
    }

    void Render() override {
        Scene::Render(); // Renders GameObjects
        dialogueManager->Render();
    }

    void ResetScene() {
        currentSceneIndex = 0;
        isTransitioning = false;
        isFadingOut = false;
        transitionProgress = 0.0f;
        ChangeScene(0);

        // Reset transition object
        transitionObject->setActiveStatus(true);
        transitionObject->SetAlpha(1.0f);  // Ensure it's initially opaque for fade-in

        // Reset dialogue manager state
        dialogueManager->Reset();  // Ensure this method resets the state of the dialogue manager
    }

private:
    void ChangeScene(int index) {
        for (auto& scene : scenes) {
            scene->setActiveStatus(false);
        }
        scenes[index]->setActiveStatus(true);
        dialogueManager->SetDialogueSet(dialogueKeys[index]);
    }

    void StartSceneTransition(int nextSceneIndex) {
        isTransitioning = true;
        transitionProgress = 0.0f;
        scenes[nextSceneIndex]->setActiveStatus(true);
        currentSceneIndex = nextSceneIndex;
        AudioManager::GetInstance().PlaySound("ProjectorSFX");

    }
};
