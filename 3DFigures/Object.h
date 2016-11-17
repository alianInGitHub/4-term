#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <glew.h>
#include "common.h"


class Object
{
public:
	Object();
	Object(ObjType _type, glm::vec3 center);
	~Object();

	void SetPlacement(glm::vec3 _placement) { placement = _placement; }

	void SetRotation(glm::vec3 rot) { rotation = rot; }

	void SetScaling(unsigned scaling) { scale = (float)scaling; }

	void Init();

	void Render(glm::mat4 MVT);

	void RenderProjection(glm::mat4 MVT, ProjType ptype);

	void Reshape();

	glm::vec3 GetRotation() { return rotation; }

	glm::vec3 GetPosition() { return placement; }

	float GetScaling() { return scale; }

	ObjType type;

private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	glm::vec3 placement;
	float scale;
	glm::vec3 rotation;

	GLuint vertexbuffer;
	GLuint uvbuffer;

	GLuint programID;
	GLuint MatrixID;
	GLuint Texture;
	GLuint TextureID;
};