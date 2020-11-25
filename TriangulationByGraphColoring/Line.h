#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#pragma once

using namespace glm;
using namespace std;

class Line
{
public:
	
	vec3 LineColor = vec3(255, 0, 0);

	vec2 StartPos;
	vec2 FinishPos;

	vector<Line*> IntersectedDiagonals;

	Line(vec2 startPos, vec2 finishPos);

	bool DidColored = false;

	bool InLeft(vec2 vertex);

	bool DidIntersect(Line other, bool isDebugEnabled = false);

	void ColorizeWithIntersectedLines(vec3 selfColor, vec3 otherColor);

	bool operator== (const Line& other)
	{
		return StartPos == other.StartPos && FinishPos == other.FinishPos;
	}
};


