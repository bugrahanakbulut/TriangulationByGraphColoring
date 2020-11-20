#include <iostream>
#include <vector>
#include <glut.h>
#include <GLM/vec2.hpp>
#include "Polygon.h"

int _windowWidth = 1280;
int _windowHeight = 720;

glm::vec2 _candidateVertex;

Polygon* _polygon = new Polygon();

void draw_polygon(int button, int state, int x, int y)
{
    _candidateVertex = glm::vec2(x, _windowHeight - y);

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


    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        _polygon->FindDiagonals();

        _polygon->DidPolygonClosed = true;
    }
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

        for (auto& pt : _polygon->Vertices)
            glVertex2f(pt[0], pt[1]);

        auto& endPt = _polygon->DidPolygonClosed ? _polygon->Vertices.front() : _candidateVertex;

        glVertex2f(endPt[0], endPt[1]);
        glEnd();
    }

    if (!_polygon->Diagonals.empty())
    {
        glBegin(GL_LINES);

        glColor3f(255, 0, 0);

        for (Line diagonal : _polygon->Diagonals)
        {
			glVertex2f(diagonal.StartPos[0], diagonal.StartPos[1]);
			glVertex2f(diagonal.FinishPos[0], diagonal.FinishPos[1]);
        }

        glEnd();
    }

    glFlush();
    glutSwapBuffers();
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
