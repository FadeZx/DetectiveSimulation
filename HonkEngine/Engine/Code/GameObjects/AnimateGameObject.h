#pragma once

#include "GameObject.h"

#include <glm/glm.hpp>
#include "Application.h"
#include "Engine.h"

class AnimateGameObject : public GameObject
{
public:
	AnimateGameObject(const std::string& name, const std::string& texturePath,float row,float col)
		: GameObject(name)
	{
		std::vector<Vertex> vertices;
		Vertex v1, v2, v3, v4;


		s_row = row;
		s_col = col;

		animX = col;
		animY = row;

		// Create Jack mesh/texture

		vertices.clear();
		v1.x = -0.5f; v1.y = -0.5f; v1.z = 0.0f; v1.r = 1.0f; v1.g = 0.0f; v1.b = 0.0f;
		v2.x = 0.5f; v2.y = -0.5f; v2.z = 0.0f; v2.r = 0.0f; v2.g = 1.0f; v2.b = 0.0f; 
		v3.x = 0.5f; v3.y = 0.5f; v3.z = 0.0f; v3.r = 0.0f; v3.g = 0.0f; v3.b = 1.0f; 
		v4.x = -0.5f; v4.y = 0.5f; v4.z = 0.0f; v4.r = 1.0f; v4.g = 1.0f; v4.b = 0.0f; 


		v1.u = 0.0f; v1.v = (s_row - 1.0f)/s_row;
		v2.u = 1.0f/s_col ; v2.v = (s_row - 1.0f) / s_row;
		v3.u = 1.0f/s_col ; v3.v = 1.0f;
		v4.u = 0.0f; v4.v = 1.0f ;


		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
		vertices.push_back(v1);
		vertices.push_back(v3);
		vertices.push_back(v4);

		texture_Id = TextureLoad(texturePath);
		meshVert = CreateMesh(vertices);

		//std::cout << "RenderObject Created: " << m_name << std::endl;
		
	}

	virtual void Update(float dt, long frame) override
	{
		//std::cout << "RenderObjectUpdated: " << m_name << std::endl;

		glm::mat4 rMat = glm::mat4(1.0f);
		glm::mat4 sMat = glm::mat4(1.0f);
		glm::mat4 tMat = glm::mat4(1.0f);

		tMat = glm::translate(glm::mat4(1.0f), glm::vec3(m_position.x, m_position.y, 0.0f));
		rMat = glm::rotate(glm::mat4(1.0f), m_orientation, glm::vec3(0.0f, 0.0f, 1.0f));
		sMat = glm::scale(glm::mat4(1.0f), glm::vec3(m_scale.x, m_scale.y, 1.0f));

		//std::cout << "scale" << m_scale.x << " " << m_scale.y << std::endl;
		
		model = tMat * rMat * sMat;

	}
	virtual void Render() override
	{
		

		//std::cout << "Rendering GameObject: " << m_name << std::endl;
		renderer.SetRenderMode(CDT_TEXTURE, 1.0f);
		renderer.SetTexture(texture_Id,animX/s_col, animY/ s_row);
		//std::cout << "Render::TextureID " << texture_Id << std::endl;	
		renderer.SetTransform(model);
		renderer.DrawMesh(meshVert);
		//DrawMesh(meshVert);
		//plication::Get().DrawTexture(*textureId, model);
		//Engine::DrawTexture(texture_id, glm::mat4{1});
	}

	virtual void Clear()
	{
		renderer.UnloadMesh(meshVert);
		renderer.TextureUnload(texture_Id);
	}

	void SetAnim(float x, float y)
	{
		animX = x;
		animY = y;
	}

protected:

	Renderer& renderer = Application::GetRenderer();;
	float s_row, s_col;
	float animX, animY;
	Tex texture_Id;
	Mesh meshVert;
	glm::mat4 model{ 1 };

};