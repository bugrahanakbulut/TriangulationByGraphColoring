#include <array>;
#include <algorithm>
#include <iostream>
#include <GLM/vec2.hpp>
#include <GLM/mat3x3.hpp>
#include <GLM/mat2x2.hpp>
#include <GLM/common.hpp>
#include "Polygon.h"
#include "Line.h"
#include<windows.h>

using namespace std;
using namespace glm;

unsigned int microsecond = 1000;

vector<Line> FindAllPossibleDiagonals(vector<vec2> vertices);
vector<Line> CheckEdgeAndDiagonalsForIntersection(vector<Line> allLines, vector<Line> polygonEdges);
vector<Line> EleminateDiagonalsInOutsideOfPolygon(bool isPolygonCounterClockwise, vector<vec2> vertices, vector<Line> diagonals);
bool CheckVertexesConvex(bool isPolygonCCw, vec2 a, vec2 b, vec2 c);

void Polygon::FindDiagonals() 
{
	BuildEdges();

	vector<Line> possibleDiagonals = FindAllPossibleDiagonals(Vertices);

	vector<Line> notIntersectedDiagonals = CheckEdgeAndDiagonalsForIntersection(possibleDiagonals, Edges);

	bool ccw = IsCounterClockwise();
	
	Diagonals = EleminateDiagonalsInOutsideOfPolygon(ccw, Vertices, notIntersectedDiagonals);

	BuildDiagonalGraph();

	ColorizeDiagonals();
}

void Polygon::FindDiagonals(int step) 
{
	
	BuildEdges();

	Sleep(microsecond);

	Diagonals = FindAllPossibleDiagonals(Vertices);

	Sleep(microsecond);

	Diagonals = CheckEdgeAndDiagonalsForIntersection(Diagonals, Edges);

	Sleep(microsecond);

	bool ccw = IsCounterClockwise();

	Diagonals = EleminateDiagonalsInOutsideOfPolygon(ccw, Vertices, Diagonals);

	Sleep(microsecond);

	BuildDiagonalGraph();

	ColorizeDiagonals();

}

void Polygon::BuildEdges() 
{
	Edges.clear();

	for(unsigned int index = 0; index < Vertices.size(); index++)
	{
		if (index != Vertices.size() - 1)
			Edges.push_back(Line(Vertices[index], Vertices[index + 1]));
		else 
			Edges.push_back(Line(Vertices[index], Vertices[0]));
	}
}

bool Polygon::IsCounterClockwise()
{
	vec2 leftMostVertex = vec2(9999, 9999);

	int index = -1;

	for (unsigned int i = 0; i < Vertices.size(); i++)
	{
		if (leftMostVertex.x > Vertices[i].x)
		{
			index = i;

			leftMostVertex = Vertices[i];
		}

		else if (leftMostVertex.x == Vertices[i].x && leftMostVertex.y > Vertices[i].y)
		{
			
			index = i;

			leftMostVertex = Vertices[i];
		}
	}

	vec2 prev = (index == 0) ? Vertices.back() : Vertices[index - 1];
	
	vec2 next = (index == Vertices.size() - 1) ? Vertices[0] : Vertices[index + 1];

	mat3x3 oriataionMat = mat3x3(1);

	oriataionMat[0].x = 1;
	oriataionMat[0].y = prev[0];
	oriataionMat[0].z = prev[1];

	oriataionMat[1].x = 1;
	oriataionMat[1].y = leftMostVertex[0];
	oriataionMat[1].z = leftMostVertex[1];

	oriataionMat[2].x = 1;
	oriataionMat[2].y = next[0];
	oriataionMat[2].z = next[1];

	float det = determinant(oriataionMat);

	bool isCCW = det > 0;

	return isCCW;
}

void Polygon::BuildDiagonalGraph()
{
	for (unsigned int i = 0; i < Diagonals.size(); i++) 
	{
		for (int j = i + 1; j < Diagonals.size(); j++)
		{
			if (Diagonals[i].DidIntersect(Diagonals[j]))
			{
				Diagonals[i].IntersectedDiagonals.push_back(&(Diagonals[j]));
				Diagonals[j].IntersectedDiagonals.push_back(&(Diagonals[i]));
			}
		}
	}
}

void Polygon::ColorizeDiagonals()
{
	for (unsigned int i = 0; i < Diagonals.size(); i++)
	{
		if (!Diagonals[i].DidColored)
			Diagonals[i].ColorizeWithIntersectedLines(Color_1, Color_2);
	}
}

vector<Line> FindAllPossibleDiagonals(vector<vec2> vertices)
{
	vector<Line> lines;

	for (unsigned int sourceVertexIndex = 0; sourceVertexIndex < vertices.size(); sourceVertexIndex++)
	{
		for (unsigned int targetVertexIndex = sourceVertexIndex + 2; targetVertexIndex < vertices.size(); targetVertexIndex ++)
		{
			if (sourceVertexIndex != 0 || targetVertexIndex != vertices.size() - 1)
				lines.push_back(Line(vertices[sourceVertexIndex], vertices[targetVertexIndex]));
		}
	}

	return lines;
}

vector<Line> CheckEdgeAndDiagonalsForIntersection(vector<Line> allLines, vector<Line> polygonEdges)
{
	vector<Line> cleanDiagonals;
	vector<Line> intersectedDiagonals;

	for (Line edge : polygonEdges)
	{
		for (Line candidateDiagonal : allLines)
		{
			/*
			cout << edge.StartPos[0] << " - " << edge.StartPos[1] << " .... " << edge.FinishPos[0] << " - " << edge.FinishPos[1] << "\n";
			cout << candidateDiagonal.StartPos[0] << " - " << candidateDiagonal.StartPos[1] << " .... " << candidateDiagonal.FinishPos[0] << " - " << candidateDiagonal.FinishPos[1] << "\n";
			*/

			bool haveCommonVertex =
				edge.StartPos == candidateDiagonal.StartPos ||
				edge.StartPos == candidateDiagonal.FinishPos ||
				edge.FinishPos == candidateDiagonal.StartPos ||
				edge.FinishPos == candidateDiagonal.FinishPos;	

			if (!haveCommonVertex)
			{
				if (!edge.DidIntersect(candidateDiagonal))
				{
					if (find(intersectedDiagonals.begin(), intersectedDiagonals.end(), candidateDiagonal) != intersectedDiagonals.end())
						continue;

					if (find(cleanDiagonals.begin(), cleanDiagonals.end(), candidateDiagonal) == cleanDiagonals.end())
						cleanDiagonals.push_back(candidateDiagonal);
				}

				else
				{
					intersectedDiagonals.push_back(candidateDiagonal);

					if (find(cleanDiagonals.begin(), cleanDiagonals.end(), candidateDiagonal) != cleanDiagonals.end())
						remove(cleanDiagonals.begin(), cleanDiagonals.end(), candidateDiagonal);
				}
			}
			else
			{
				if (find(intersectedDiagonals.begin(), intersectedDiagonals.end(), candidateDiagonal) != intersectedDiagonals.end())
					continue;

				if (find(cleanDiagonals.begin(), cleanDiagonals.end(), candidateDiagonal) == cleanDiagonals.end())
					cleanDiagonals.push_back(candidateDiagonal);
			}
		}
	}

	return cleanDiagonals;
}

vector<Line> EleminateDiagonalsInOutsideOfPolygon(bool isPolygonCounterClockwise, vector<vec2> vertices, vector<Line> diagonals)
{
	vector<Line> inConeDiagonals;
		
	vector<Line> rejected;

	for (unsigned int i = 0; i < diagonals.size(); i++)
	{
		int indexOfStartingPoint = -1;

		for (unsigned int iterate = 0; iterate < vertices.size(); iterate++)
		{
			if (vertices[iterate] == diagonals[i].StartPos)
			{
				indexOfStartingPoint = iterate;

				break;
			}
		}

		bool isVertexConvex = false;

		vec2 prevVertex = (indexOfStartingPoint == 0) ? vertices[vertices.size() - 1] : vertices[indexOfStartingPoint - 1];

		vec2  nextVertex = (indexOfStartingPoint == vertices.size() - 1) ? vertices[0] : vertices[indexOfStartingPoint + 1];

		isVertexConvex = CheckVertexesConvex(isPolygonCounterClockwise, prevVertex, vertices[indexOfStartingPoint], nextVertex);

		bool inCone = false;

		if (isVertexConvex && isPolygonCounterClockwise)
			inCone = diagonals[i].InLeft(prevVertex) && !diagonals[i].InLeft(nextVertex);

		else if (!isVertexConvex && isPolygonCounterClockwise)
			inCone = !(diagonals[i].InLeft(nextVertex) && !diagonals[i].InLeft(prevVertex));

		if (isVertexConvex && !isPolygonCounterClockwise)
			inCone = diagonals[i].InLeft(nextVertex) && !diagonals[i].InLeft(prevVertex);

		else if (!isVertexConvex && !isPolygonCounterClockwise)
			inCone = !(diagonals[i].InLeft(prevVertex) && !diagonals[i].InLeft(nextVertex));
		
		if (inCone)
			inConeDiagonals.push_back(diagonals[i]);
	}

	return inConeDiagonals;
}

bool CheckVertexesConvex(bool isPolygonCCW, vec2 a, vec2 b, vec2 c)
{
		vec2 ba = b - a;
		vec2 cb = c - b;

		mat2x2 x = mat2x2(ba, cb);

		float det = determinant(x);
		
		return !((det > 0) ^ isPolygonCCW);
}
