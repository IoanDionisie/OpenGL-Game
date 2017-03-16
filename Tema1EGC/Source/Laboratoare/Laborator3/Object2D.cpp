#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill)
{
    glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(width, 0, 0), color),
		VertexFormat(corner + glm::vec3(width, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		rectangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	rectangle->InitFromData(vertices, indices);
	return rectangle;
}

Mesh* Object2D::CreateTriangle(std::string name, glm::vec3 topVertex, float length, float angle, glm::vec3 color, bool fill)
{
    glm::vec3 corner = topVertex;

    //the vertices are calculated in the following manner
    //1. we choose the top vertex
    //2. we compute the other two vertices using the edge length and the orientation of the triangle
    //3. the formula is based on the fact that: 
    //      The equilateral triangle has 60 degrees corners, so we know that the other points are 30 off + or - from its orientation
    //      - x_point1 = x_top + edge_length*cos(orientation_angle + 30_degrees) 
    //      - y_point1 = y_top + edge_length*sin(orientation_angle + 30_degrees)
    //      - x_point2 = x_top + edge_length*cos(orientation_angle - 30_degrees) 
    //      - y_point2 = y_top + edge_length*sin(orientation_angle - 30_degrees)
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length * sin(angle + 0.523599), length * cos(angle + 0.523599), 0), color),
		VertexFormat(corner + glm::vec3(length * sin(angle - 0.523599), length * cos(angle - 0.523599), 0), color)
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2};
	
	if (!fill) {
		triangle->SetDrawMode(GL_LINE_LOOP);
	}    
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	triangle->InitFromData(vertices, indices);
	return triangle;
}
