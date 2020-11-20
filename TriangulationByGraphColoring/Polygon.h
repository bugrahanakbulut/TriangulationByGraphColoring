#include <array>
#include <vector>
#include <GLM/vec2.hpp>
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

	void BuildEdges();

	void FindDiagonals();
};

