#include <glm/vec2.hpp>

#pragma once


class Line
{
public:
	glm::vec2 StartPos;
	glm::vec2 FinishPos;

	Line(glm::vec2 startPos, glm::vec2 finishPos);
};
