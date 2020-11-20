#include <glm/vec2.hpp>

#pragma once

using namespace glm;

class Line
{
public:
	vec2 StartPos;
	vec2 FinishPos;

	Line(vec2 startPos, vec2 finishPos);

	bool InLeft(vec2 vertex);

	bool DidIntersect(Line other);

	bool operator== (const Line& other)
	{
		return StartPos == other.StartPos && FinishPos == other.FinishPos;
	}
};


