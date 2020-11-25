#include <iostream>
#include <vector>
#include <glut.h>
#include <GLM/vec2.hpp>
#include "Polygon.h"

using namespace glm;
using namespace std;

int _windowWidth = 1280;
int _windowHeight = 720;

int _delayEachStep = 500;

vec2 _candidateVertex;

Polygon* _polygon = new Polygon();

void StartDrawPolygon();
void StepOne(int v);
void StepTwo(int v);
void StepThree(int v);
void StepFour(int v);
void StepFive(int v);

void draw_polygon(int button, int state, int x, int y)
{
    _candidateVertex = vec2(x, _windowHeight - y);

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (_polygon->DidPolygonClosed)
        {
            _polygon->Vertices.clear();
            _polygon->Diagonals.clear();
        }
		
        // reset

        _polygon->DidPolygonClosed = false;
        
        _polygon->Vertices.push_back(_candidateVertex);
    }

	if (button == 1 && state == GLUT_DOWN)
	{
		_polygon->DidPolygonClosed = true;

		_polygon->FindDiagonals();
	}

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        StartDrawPolygon();
    
}

void mouse_move(int x, int y)
{
	_candidateVertex = glm::vec2(x, _windowHeight - y);
    glutPostRedisplay();
}

void display(void)
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    if (!_polygon->Vertices.empty())
    {
        glBegin(GL_LINE_STRIP);
        
        glColor3f(0, 0, 0);

        for (vec2 pt : _polygon->Vertices)
            glVertex2f(pt[0], pt[1]);

        vec2 endPt = _polygon->DidPolygonClosed ? _polygon->Vertices.front() : _candidateVertex;

        glVertex2f(endPt[0], endPt[1]);
        glEnd();
    }

    if (!_polygon->Diagonals.empty())
    {
        glBegin(GL_LINES);

        for (Line diagonal : _polygon->Diagonals)
		{
            glColor3f(diagonal.LineColor[0], diagonal.LineColor[1], diagonal.LineColor[2]);
			glVertex2f(diagonal.StartPos[0], diagonal.StartPos[1]);
			glVertex2f(diagonal.FinishPos[0], diagonal.FinishPos[1]);
        }

        glEnd();
    }

    glFlush();
    glutSwapBuffers();
}

void StartDrawPolygon() 
{
    _polygon->DidPolygonClosed = true;

    _polygon->BuildDiagonals();

    glutTimerFunc(_delayEachStep, StepOne, 0);
}

void StepOne(int v)
{
    _polygon->BuildDiagonals();

    glutPostRedisplay();

    glutTimerFunc(_delayEachStep, StepTwo, 0);
}

void StepTwo(int v)
{
    _polygon->EleminateDiagonalsWithIntersectedEdges();

	glutPostRedisplay();

    glutTimerFunc(_delayEachStep, StepThree, 0);
}

void StepThree(int v)
{
	_polygon->EleminateDiagonalsInOutsidePolygon();

    glutPostRedisplay();

	glutTimerFunc(_delayEachStep, StepFour, 0);
}

void StepFour(int v)
{
    _polygon->ColorizePolygonDiagonal();

    glutPostRedisplay();

    glutTimerFunc(_delayEachStep, StepFive, 0);
}

void StepFive(int v)
{
    _polygon->RemoveDiagonalsNotUsingForTriangulation();

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(_windowWidth, _windowHeight);
    
    glutCreateWindow("Triangulation");
    
    glutDisplayFunc(display);
    glutPassiveMotionFunc(mouse_move);
    glutMouseFunc(draw_polygon);
    
    glMatrixMode(GL_PROJECTION);
    glOrtho(0.0f, (float)_windowWidth, 0.0f, (float)_windowHeight, -1.0, 1.0);
    glutMainLoop();
    return 0;
}
