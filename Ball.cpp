#include "Ball.h"
#include <stdio.h>
#include <GL/glut.h>
#include <GL/glu.h>

Ball::Ball(float x, float y, float raio)
{
	this->x = x;
	this->y = y;
	this->raio = raio;
	velx = 0.03;
	vely = 0.03;
}

void Ball::Draw()
{
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glPointSize(raio);
	glColor3f(0, 0, 0);
	glBegin(GL_POINTS);
	   glVertex2f(x,y);
	glEnd();
}

void Ball::Update()
{
	x+=velx;
	y+=vely;

	if (x >= 4)
		velx*=-1;
	else if (x <= -4)
		velx*=-1;
	else if (y >= 3)
		vely*=-1;
	else if (y <= -3)
		vely*=-1;
}