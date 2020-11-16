#include <array>
#include <iostream>
#include <GLM/vec2.hpp>
#include <GLM/common.hpp>
#include "Polygon.h"
#include "Line.h"

std::vector<Line> FindAllPossibleDiagonals(std::vector<glm::vec2> vertices);

void Polygon::FindDiagonals() 
{
	std::vector<Line> possibleDiagonals = FindAllPossibleDiagonals(Vertices);
}

std::vector<Line> FindAllPossibleDiagonals(std::vector<glm::vec2> vertices)
{
	std::vector<Line> lines;

	for (unsigned int sourceVertexIndex = 0; sourceVertexIndex < vertices.size(); sourceVertexIndex++)
	{
		for (unsigned int targetVertexIndex = sourceVertexIndex + 2; targetVertexIndex < vertices.size(); targetVertexIndex ++)
		{
			if (sourceVertexIndex != 0 || targetVertexIndex != vertices.size() - 1)
				lines.push_back(Line(vertices[sourceVertexIndex], vertices[targetVertexIndex]));
		}
	}

	return lines;
}