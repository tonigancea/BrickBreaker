#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

	Mesh* CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill = false);

	Mesh* CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill = false);

	Mesh* CreateHeart(std::string name, glm::vec3 center, glm::vec3 color, bool fill);

}

