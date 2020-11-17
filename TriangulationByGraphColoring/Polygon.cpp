#include <array>
#include <algorithm>
#include <iostream>
#include <GLM/vec2.hpp>
#include <GLM/common.hpp>
#include "Polygon.h"
#include "Line.h"

using namespace std;
using namespace glm;

vector<Line> FindAllPossibleDiagonals(vector<vec2> vertices);
vector<Line> CheckEdgeAndDiagonalsForIntersection(vector<Line> allLines, vector<Line> polygonEdges);

void Polygon::FindDiagonals() 
{
	BuildEdges();

	vector<Line> possibleDiagonals = FindAllPossibleDiagonals(Vertices);

	Diagonals = CheckEdgeAndDiagonalsForIntersection(possibleDiagonals, Edges);
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
			bool isAdjacent = edge.StartPos == candidateDiagonal.StartPos;
						
			
			cout << edge.StartPos[0] << " - " << edge.StartPos[1] << " .... " << edge.FinishPos[0] << " - " << edge.FinishPos[1] << "\n";
			cout << candidateDiagonal.StartPos[0] << " - " << candidateDiagonal.StartPos[1] << " .... " << candidateDiagonal.FinishPos[0] << " - " << candidateDiagonal.FinishPos[1] << "\n";
			cout << isAdjacent << "\n" << "_____________\n";
			
			
			if (isAdjacent) continue;

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
	}

	return cleanDiagonals;
}

