#include <glm/vec2.hpp>

#pragma once


class Line
{
public:
	glm::vec2 StartPos;
	glm::vec2 FinishPos;

	Line(glm::vec2 startPos, glm::vec2 finishPos);

	bool DidIntersect(Line other);

	friend bool operator== (const Line& line1, const Line& line2);

	bool operator== (const Line& other)
	{
		return StartPos == other.StartPos && FinishPos == other.FinishPos;
	}
};


