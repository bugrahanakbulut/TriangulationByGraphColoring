#include <GLM/vec2.hpp>
#include <iostream>
#include "Line.h"

using namespace glm;

bool IsInLeftSide(vec2 a, vec2 b, vec2 c);

Line::Line(vec2 startPos, vec2 finishPos)
{
	StartPos = startPos;
	FinishPos = finishPos;
}

bool Line::DidIntersect(Line other, bool isDebugEnable)
{
	if (StartPos == other.StartPos || StartPos == other.FinishPos ||
		FinishPos == other.StartPos || FinishPos == other.FinishPos)
		return false;

	bool cLeft = IsInLeftSide(StartPos, FinishPos, other.StartPos);
	bool dLeft = IsInLeftSide(StartPos, FinishPos, other.FinishPos);

	bool aLeft = IsInLeftSide(other.StartPos, other.FinishPos, StartPos);
	bool bLeft = IsInLeftSide(other.StartPos, other.FinishPos, FinishPos);

	if (isDebugEnable)
		std::cout << "Intersection Result : " << ((cLeft ^ dLeft) && (aLeft ^ bLeft)) << "\n";

	return (cLeft ^ dLeft) && (aLeft ^ bLeft);
}

bool Line::InLeft(vec2 vertex)
{
	return IsInLeftSide(StartPos, FinishPos, vertex);
}

void Line::ColorizeWithIntersectedLines(vec3 selfColor, vec3 otherColor)
{
	DidColored = true;
	LineColor = selfColor;

	for (int i = 0; i < IntersectedDiagonals.size(); i++)
	{
		IntersectedDiagonals[i]->DidColored = true;
		IntersectedDiagonals[i]->LineColor = otherColor;
	}
}

bool IsInLeftSide(vec2 a, vec2 b, vec2 c)
{
	float area = ((b[0] - a[0]) * (c[1] - a[1])) - ((b[1] - a[1]) * (c[0] - a[0]));

	area /= 2;

	return area > 0;
}