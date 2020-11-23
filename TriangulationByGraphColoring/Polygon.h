#include <array>
#include <vector>
#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include "Line.h"

#pragma once

using namespace std;
using namespace glm;

class Polygon
{
private:
	bool IsCounterClockwise();
	

public:
	bool DidPolygonClosed = false;

	vector<vec2> Vertices;
	vector<Line> Edges;
	vector<Line> Diagonals;

	vec3 Color_1 = vec3(0, 0, 255);
	vec3 Color_2 = vec3(0, 255, 0);

	void BuildEdges();

	void FindDiagonals();

	void BuildDiagonalGraph();

	void ColorizeDiagonals();
};

