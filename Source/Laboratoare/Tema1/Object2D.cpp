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

Mesh* Object2D::CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(width, 0, 0), color),
		VertexFormat(corner + glm::vec3(width, height, 0), color),
		VertexFormat(corner + glm::vec3(0, height, 0), color)
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

Mesh* Object2D::CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill)
{
	glm::vec3 center_circle = center;

	std::vector<VertexFormat> vertices
	{
		VertexFormat(center_circle, color),
	};

	for (int i = 0; i <= 360; i++) {
		vertices.push_back(VertexFormat(glm::vec3(radius * cos(i * M_PI / 180), radius * sin(i * M_PI / 180), 0), color));
	}

	std::vector<unsigned short> indices = {};

	for (int i = 0; i <= 360; i++) {
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);
	}

	Mesh* circle = new Mesh(name);

	if (!fill) {
		circle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	circle->InitFromData(vertices, indices);
	return circle;
}

Mesh* Object2D::CreateHeart(std::string name, glm::vec3 center, glm::vec3 color, bool fill)
{
	glm::vec3 heart_center = center;

	std::vector<VertexFormat> vertices = {
		VertexFormat(heart_center, color),
	};


	for (float x = -1.139; x <= 1.139; x += 0.001)
	{
		float delta = cbrt(x*x) * cbrt(x*x) - 4 * x*x + 4;
		float y1 = (cbrt(x*x) + sqrt(delta)) / 2;
		float y2 = (cbrt(x*x) - sqrt(delta)) / 2;
		vertices.push_back(VertexFormat(glm::vec3(x, y1, 0), color));
		vertices.push_back(VertexFormat(glm::vec3(x, y2, 0), color));
	}

	std::vector<unsigned short> indices = {};
	
	int indice = 1;

	for (float x = -1.139; x <= 1.139; x += 0.001) {
		indices.push_back(0);
		indices.push_back(indice);
		indice++;
		indice++;
		indices.push_back(indice);
	}

	Mesh* heart = new Mesh(name);

	if (!fill) {
		heart->SetDrawMode(GL_LINE_LOOP);
	}

	heart->InitFromData(vertices, indices);
	return heart;
}