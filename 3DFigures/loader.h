#ifndef LOADER_H
#define LOADER_H


#include <glew.h>
#include <vector>
#include <glm\vec3.hpp>
#include <glm\vec2.hpp>


#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

bool loadOBJ(std::string filename,
	std::vector<glm::vec3> &vertices,
	std::vector<glm::vec3> &normals,
	std::vector<glm::vec2> &uvs);

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

GLuint LoadDDS(const char * imagepath);

std::vector<std::vector<std::string>> mysql(const char query[], bool getInfo, unsigned rowNumb);

//void CalculateCameraMatrices(glm::mat4 &mvp, float cx, float cy);

#endif