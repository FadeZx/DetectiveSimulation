#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "../GameObjects/Gameobject.h"

class Scene
{
public:
	virtual ~Scene()
	{
		m_gameObjects.clear();
	}

	virtual void Update(float dt,long frame)
	{
		for (auto& object : m_gameObjects) {
			object->Update(dt, frame);
			//std::cout << "Gameobject Update" << std::endl;
		}
			

		 
		for (auto& object : m_toAddGameObjects) {
			m_gameObjects.push_back(std::move(object));
		}
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
		m_toAddGameObjects.push_back(std::unique_ptr<GameObject>(newGameObject));
	}

	GameObject* GetGameObjectByName(const std::string& name) {
		for (auto& object : m_gameObjects) {
			if (object->GetName() == name) {
				return object.get();
			}
		}
		return nullptr; // Return nullptr if no object with the given name is found
	}

protected:
	std::vector<std::unique_ptr<GameObject>> m_gameObjects;
	std::vector<std::unique_ptr<GameObject>> m_toAddGameObjects;

};