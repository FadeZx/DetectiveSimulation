#pragma once

#include <iostream>
#include <vector>
#include "../GameObjects/Gameobject.h"

class Scene
{
public:
	virtual ~Scene()
	{
		for (auto& object : m_gameObjects)
		{
			if (object) {
				object->Clear();
				//delete object;
			}
		}
	}

	virtual void Update(float dt, long frame)
	{
		for (auto& object : m_gameObjects) {
			object->Update(dt, frame);
			//std::cout << "Gameobject Update" << std::endl;
		}



		for (auto& object : m_toAddGameObjects)
			m_gameObjects.push_back(object);

		//std::cout << "GAME OBJECTS: " << m_gameObjects.size() << std::endl;

		m_toAddGameObjects.clear();
	}

	virtual void Render()
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		for (auto& object : m_gameObjects)
			object->Render();
	}

	void AddGameObject(GameObject* newGameObject)
	{
		m_toAddGameObjects.push_back(newGameObject);
	}

	GameObject* GetGameObjectByName(const std::string& name) {
		for (auto& object : m_gameObjects) {
			if (object->GetName() == name) {
				return object;
			}
		}
		return nullptr; // Return nullptr if no object with the given name is found
	}

protected:
	std::vector<GameObject*> m_gameObjects;
	std::vector<GameObject*> m_toAddGameObjects;
};