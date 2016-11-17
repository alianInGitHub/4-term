#include "stdafx.h"
#include <ocdb.h>
#include "./Object.h"
#include "loader.h"
#include <glm/gtc/matrix_transform.hpp>

Object::Object()
{
	rotation.x = rotation.y = rotation.z = 45.0f;
	placement.x = placement.y = placement.z = 0.0f;
}

Object::Object(ObjType _type, glm::vec3 center) : type(_type), placement(center) 
{ 
	rotation.x = rotation.y = rotation.z = 0.0f;
	scale = 1.0f;
	Init(); 
}


Object::~Object()
{
}



void Object::Init()
{
	programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");

	// Load the texture
	Texture = LoadDDS("uvmap.DDS");

	// Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(programID, "myTextureSampler");
	bool res;
	switch (type)
	{
	case PIRAMID:
		res = loadOBJ("piramid.obj", vertices, normals, uvs);
		break;
	case SPHERE:
		res = loadOBJ("sphere.obj", vertices, normals, uvs);
		break;
	default:
		break;
	}
}

void Object::Render(glm::mat4 MVP)
{
	Reshape();

	glUseProgram(programID);

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Draw the triangle 
	
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Object::RenderProjection(glm::mat4 MVP, ProjType ptype)
{
	std::vector<glm::vec3> projVertices = vertices;

	if (scale != 1.0)
	{
		for (std::vector<glm::vec3>::iterator it = projVertices.begin(); it != projVertices.end(); it++)
		{
			it->x *= scale;
			it->y *= scale;
			it->z *= scale;
		}
	}
	glm::mat3 rotMat(1.0f);
	//rotation
	if (rotation.x != 0)
	{
		rotMat[1][1] = cos(rotation.x);
		rotMat[1][2] = -sin(rotation.x);
		rotMat[2][1] = sin(rotation.x);
		rotMat[2][2] = cos(rotation.x);
		for (std::vector<glm::vec3>::iterator i = projVertices.begin(); i != projVertices.end(); i++)
		{
			(*i) = rotMat * (*i);
		}
		rotMat[1][1] = rotMat[2][2] = 1.0f;
		rotMat[1][2] = rotMat[2][1] = 0.0f;
	}
	if (rotation.y != 0)
	{
		rotMat[0][0] = cos(rotation.y);
		rotMat[0][2] = sin(rotation.y);
		rotMat[2][0] = -sin(rotation.y);
		rotMat[2][2] = cos(rotation.y);
		for (std::vector<glm::vec3>::iterator i = projVertices.begin(); i != projVertices.end(); i++)
		{
			(*i) = rotMat * (*i);
		}
		rotMat[0][0] = rotMat[2][2] = 1.0f;
		rotMat[0][2] = rotMat[2][0] = 0.0f;
	}
	if (rotation.z != 0)
	{
		rotMat[0][0] = cos(rotation.z);
		rotMat[0][1] = -sin(rotation.z);
		rotMat[1][0] = sin(rotation.z);
		rotMat[1][1] = cos(rotation.z);
		for (std::vector<glm::vec3>::iterator i = projVertices.begin(); i != projVertices.end(); i++)
		{
			(*i) = rotMat * (*i);
		}
		rotMat[0][0] = rotMat[1][1] = 1.0f;
		rotMat[0][1] = rotMat[0][1] = 0.0f;
	}

	if (placement != glm::vec3(0, 0, 0))
	{
		glm::mat4 translation(1.0f);
		translation = glm::translate(translation, placement);
		for (std::vector<glm::vec3>::iterator i = projVertices.begin(); i != projVertices.end(); i++)
		{
			glm::vec4 temp(i->x, i->y, i->z, 1.0f);
			temp = translation * temp;
			i->x = temp.x;
			i->y = temp.y;
			i->z = temp.z;
		}
	}
	switch (ptype)
	{
	case XOY:
		for (std::vector<glm::vec3>::iterator it = projVertices.begin(); it != projVertices.end(); it++)
			it->z = 0.0;
		break;
	case XOZ:
		for (std::vector<glm::vec3>::iterator it = projVertices.begin(); it != projVertices.end(); it++)
			it->y = 0.0;
		break;
	case YOZ:
		for (std::vector<glm::vec3>::iterator it = projVertices.begin(); it != projVertices.end(); it++)
			it->x = 0.0;
		break;
	default:
		break;
	}
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, projVertices.size() * sizeof(glm::vec3), &projVertices[0], GL_STATIC_DRAW);
	glUseProgram(programID);
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, projVertices.size());

	glDisableVertexAttribArray(0);
}

void Object::Reshape()
{
	std::vector<glm::vec3> newvertices = vertices;
	glm::mat3 rotMat(1.0f);
	//rotation
	if (rotation.x != 0)
	{
		rotMat[1][1] = cos(rotation.x);
		rotMat[1][2] = -sin(rotation.x);
		rotMat[2][1] = sin(rotation.x);
		rotMat[2][2] = cos(rotation.x);
		for (std::vector<glm::vec3>::iterator i = newvertices.begin(); i != newvertices.end(); i++)
		{
			(*i) = rotMat * (*i);
		}
		rotMat[1][1] = rotMat[2][2] = 1.0f;
		rotMat[1][2] = rotMat[2][1] = 0.0f;
	}
	if (rotation.y != 0)
	{
		rotMat[0][0] = cos(rotation.y);
		rotMat[0][2] = sin(rotation.y);
		rotMat[2][0] = -sin(rotation.y);
		rotMat[2][2] = cos(rotation.y);
		for (std::vector<glm::vec3>::iterator i = newvertices.begin(); i != newvertices.end(); i++)
		{
			(*i) = rotMat * (*i);
		}
		rotMat[0][0] = rotMat[2][2] = 1.0f;
		rotMat[0][2] = rotMat[2][0] = 0.0f;
	}
	if (rotation.z != 0)
	{
		rotMat[0][0] = cos(rotation.z);
		rotMat[0][1] = -sin(rotation.z);
		rotMat[1][0] = sin(rotation.z);
		rotMat[1][1] = cos(rotation.z);
		for (std::vector<glm::vec3>::iterator i = newvertices.begin(); i != newvertices.end(); i++)
		{
			(*i) = rotMat * (*i);
		}
		rotMat[0][0] = rotMat[1][1] = 1.0f;
		rotMat[0][1] = rotMat[0][1] = 0.0f;
	}
	//translation
	if (placement != glm::vec3(0, 0, 0))
	{
		glm::mat4 translation(1.0f);
		translation = glm::translate(translation, placement);
		for (std::vector<glm::vec3>::iterator i = newvertices.begin(); i != newvertices.end(); i++)
		{
			glm::vec4 temp(i->x, i->y, i->z, 1.0f);
			temp = translation * temp;
			i->x = temp.x;
			i->y = temp.y;
			i->z = temp.z;
		}
	}

	if (scale != 1.0)
	{
		for (std::vector<glm::vec3>::iterator i = newvertices.begin(); i != newvertices.end(); i++)
		{
			i->x *= scale;
			i->y *= scale;
			i->z *= scale;
		}
	}
	
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, newvertices.size() * sizeof(glm::vec3), &newvertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
}

