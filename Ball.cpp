#include "Ball.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glu.h>

Ball::Ball(float x, float y, float raio)
{
	alive = true;

	this->x = x;
	this->y = y;
	this->raio = raio;

	r = 0;
	g = 0;
	b = 0;

	velx = 0.02;
	vely = 0.02;
}

void Ball::Draw()
{
	glColor4f(r, g, b, 1);
	glBegin(GL_POLYGON);
		for(float a = 0; a < 2*M_PI; a+=0.1) {
			glVertex2f(x + raio*cos(a), y + raio*sin(a));
		}
	glEnd();
}

void Ball::Update()
{
	if (alive) {
		x+=velx;
		y+=vely;

		if (x >= 4)
			velx*=-1;
		else if (x <= -4)
			velx*=-1;
		else if (y >= 3)
			vely*=-1;
		else if (y <= -3) {
			vely*=-1;
			alive = false;
		}
	} else {
		//limpa a tela com a cor de fundo
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0, 0, 0);
		glRasterPos2f(-1, 0);
		char texto[20];
		sprintf(texto, "Game Over");
		for(int i = 0; i < strlen(texto); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
	}
}

bool Ball::checkCollision(Block block)
{
	float point_x = x;
	if (x < block.xi) point_x = block.xi;
	if (x > block.xf) point_x = block.xf;

	float point_y = y;
	if (y < block.yi) point_y = block.yi;
	if (y > block.yf) point_y = block.yf;

	float distancia = sqrt(pow(x-point_x,2)+pow(y-point_y,2));

	if (distancia <= raio) {
		vely*=-1;
		return true;
	}

	return false;
}