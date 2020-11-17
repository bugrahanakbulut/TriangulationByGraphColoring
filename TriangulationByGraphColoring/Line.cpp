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

bool Line::DidIntersect(Line other)
{
	bool cLeft = IsInLeftSide(StartPos, FinishPos, other.StartPos);
	bool dLeft = IsInLeftSide(StartPos, FinishPos, other.FinishPos);

	bool aLeft = IsInLeftSide(other.StartPos, other.FinishPos, StartPos);
	bool bLeft = IsInLeftSide(other.StartPos, other.FinishPos, FinishPos);

	std::cout << "Intersection Result : " << ((cLeft ^ dLeft) && (aLeft ^ bLeft)) << "\n";

	return (cLeft ^ dLeft) && (aLeft ^ bLeft);

}

bool IsInLeftSide(vec2 a, vec2 b, vec2 c)
{
	float area = ((b[0] - a[0]) * (c[1] - a[1])) - ((c[0] - a[0]) * (b[1] - a[1]));

	area /= 2;

	return area > 0;
}