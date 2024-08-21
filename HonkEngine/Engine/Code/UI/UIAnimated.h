#pragma once

#include "../GameObjects/GameObject.h"

#include <glm/glm.hpp>
#include "../Application.h"
#include "../Engine.h"

class UIAnimated : public GameObject
{
public:
	UIAnimated(const std::string& name, const std::string& texturePath, float row, float col, const glm::vec3& position, bool isOnScreen)
		: GameObject(name)
	{
		this->isOnScreen = isOnScreen;
		SetPosition(position);

		std::vector<Vertex> vertices;
		Vertex v1, v2, v3, v4;


		s_row = row;
		s_col = col;

		animX = col;
		animY = row;

		// Create Jack mesh/texture

		vertices.clear();
		v1.x = -0.5f; v1.y = -0.5f; v1.z = 0.0f; v1.r = 1.0f; v1.g = 0.0f; v1.b = 0.0f; v1.u = 0.0f; v1.v = 0.0f;
		v2.x = 0.5f; v2.y = -0.5f; v2.z = 0.0f; v2.r = 0.0f; v2.g = 1.0f; v2.b = 0.0f; v2.u = 1.0f; v2.v = 0.0f;
		v3.x = 0.5f; v3.y = 0.5f; v3.z = 0.0f; v3.r = 0.0f; v3.g = 0.0f; v3.b = 1.0f; v3.u = 1.0f; v3.v = 1.0f;
		v4.x = -0.5f; v4.y = 0.5f; v4.z = 0.0f; v4.r = 1.0f; v4.g = 1.0f; v4.b = 0.0f; v4.u = 0.0f; v4.v = 1.0f;

		v1.u = 0.0f; v1.v = (s_row - 1.0f) / s_row;
		v2.u = 1.0f / s_col; v2.v = (s_row - 1.0f) / s_row;
		v3.u = 1.0f / s_col; v3.v = 1.0f;
		v4.u = 0.0f; v4.v = 1.0f;

		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
		vertices.push_back(v1);
		vertices.push_back(v3);
		vertices.push_back(v4);


		texture_Id = TextureLoad(texturePath);
		meshVert = CreateMesh(vertices);


	}

	UIAnimated(const std::string& name, const std::string& texturePath, float row, float col, bool isOnScreen)
		: GameObject(name)
	{
		this->isOnScreen = isOnScreen;
		std::vector<Vertex> vertices;
		Vertex v1, v2, v3, v4;

		s_row = row;
		s_col = col;

		animX = col;
		animY = row;


		// Create mesh/texture

		vertices.clear();
		v1.x = -0.5f; v1.y = -0.5f; v1.z = 0.0f; v1.r = 1.0f; v1.g = 0.0f; v1.b = 0.0f; v1.u = 0.0f; v1.v = 0.0f;
		v2.x = 0.5f; v2.y = -0.5f; v2.z = 0.0f; v2.r = 0.0f; v2.g = 1.0f; v2.b = 0.0f; v2.u = 1.0f; v2.v = 0.0f;
		v3.x = 0.5f; v3.y = 0.5f; v3.z = 0.0f; v3.r = 0.0f; v3.g = 0.0f; v3.b = 1.0f; v3.u = 1.0f; v3.v = 1.0f;
		v4.x = -0.5f; v4.y = 0.5f; v4.z = 0.0f; v4.r = 1.0f; v4.g = 1.0f; v4.b = 0.0f; v4.u = 0.0f; v4.v = 1.0f;

		v1.u = 0.0f; v1.v = (s_row - 1.0f) / s_row;
		v2.u = 1.0f / s_col; v2.v = (s_row - 1.0f) / s_row;
		v3.u = 1.0f / s_col; v3.v = 1.0f;
		v4.u = 0.0f; v4.v = 1.0f;

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

		glm::mat4 rMat = glm::mat4(1.0f);
		glm::mat4 sMat = glm::mat4(1.0f);
		glm::mat4 tMat = glm::mat4(1.0f);

		if (isOnScreen)
		{
			glm::vec3 camPos = glm::vec3(camera.GetPosX(), camera.GetPosY(), 0.0f);
			m_transformedPosition = camPos + m_position;
			tMat = glm::translate(glm::mat4(1.0f), m_transformedPosition);
		}
		else
		{
			m_transformedPosition = m_position;
			tMat = glm::translate(glm::mat4(1.0f), m_position);
		}

		rMat = glm::rotate(glm::mat4(1.0f), m_orientation, glm::vec3(0.0f, 0.0f, 1.0f));
		sMat = glm::scale(glm::mat4(1.0f), glm::vec3(m_scale.x, m_scale.y, 1.0f));

		model = tMat * rMat * sMat;

	}

	bool IsPointInside(float x, float y) const
	{
		float minX = m_transformedPosition.x - (m_scale.x / 2.0f);
		float maxX = m_transformedPosition.x + (m_scale.x / 2.0f);
		float minY = m_transformedPosition.y - (m_scale.y / 2.0f);
		float maxY = m_transformedPosition.y + (m_scale.y / 2.0f);

		return ((x >= minX && x <= maxX) && (y >= minY && y <= maxY));
	}

	virtual void Render() override
	{
		UIAnimated::Update(0, 0);

		renderer.SetRenderMode(CDT_TEXTURE, m_alpha);
		renderer.SetTexture(texture_Id, animX / s_col, animY / s_row);
		renderer.SetTransform(model);
		renderer.DrawMesh(meshVert);

	}

	virtual void Clear()
	{
		renderer.UnloadMesh(meshVert);
		renderer.TextureUnload(texture_Id);
	}

	const glm::mat4& GetModelMatrix() const {
		return model;
	}

	const glm::vec3 GetOnscreenPosition() const { return m_transformedPosition; }


	Tex GetTextureID() {
		return texture_Id;
	}

	void SetTextureID(Tex textureID) {

		texture_Id = textureID;

	}

	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}

	void SetAnim(float x, float y)
	{
		animX = x;
		animY = y;
	}




protected:
	float m_alpha = 1.0f;
	glm::vec3 m_transformedPosition;
	bool isOnScreen;
	Renderer& renderer = Application::GetRenderer();
	Camera& camera = Application::GetCamera();
	float s_row, s_col;
	float animX, animY;
	Tex texture_Id;
	Mesh meshVert;
	glm::mat4 model{ 1 };

};