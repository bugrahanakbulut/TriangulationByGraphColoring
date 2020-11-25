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
	bool _isOperating = false;

	void BuildEdges();

	bool IsCounterClockwise();

	void BuildDiagonalGraph();

	void ColorizeDiagonals();

public:
	bool DidPolygonClosed = false;

	vector<vec2> Vertices;
	vector<Line> Edges;

	vector<Line> Diagonals;

	vec3 Color_1 = vec3(0, 0, 255);
	vec3 Color_2 = vec3(0, 255, 0);

	void FindDiagonals();

	void BuildDiagonals();

	void EleminateDiagonalsWithIntersectedEdges();

	void EleminateDiagonalsInOutsidePolygon();

	void ColorizePolygonDiagonal();

	void RemoveDiagonalsNotUsingForTriangulation();
};

