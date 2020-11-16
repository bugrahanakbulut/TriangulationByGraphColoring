#include <array>
#include <vector>
#include <GLM/vec2.hpp>

#pragma once

class Polygon
{
private:
	

public:
	bool DidPolygonClosed = false;

	std::vector<glm::vec2> Vertices;

	void FindDiagonals();
};

