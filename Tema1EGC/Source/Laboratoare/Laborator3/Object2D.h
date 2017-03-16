#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    
    // Create square with given bottom left corner, length, width and color
	Mesh* CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill = false);

    // Create an equilateral triangle with top vertex, edge length, orientation angle and color
	Mesh* CreateTriangle(std::string name, glm::vec3 topVertex, float length, float angle, glm::vec3 color, bool fill = false);

}

