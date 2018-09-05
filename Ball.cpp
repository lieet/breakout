#include "Ball.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>

Ball::Ball(float x, float y, float raio)
{
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
	x+=velx;
	y+=vely;

	//verifica se a bola esta dentro das dimensões da tela
	if (x <= 0 || x >= 8)
		velx*=-1;
	else if (y <= 0 || y >= 6)
		vely*=-1;
}

bool Ball::checkCollision(Block block)
{
	float point_x = x;
	if (x < block.xi) point_x = block.xi;
	if (x > block.xf) point_x = block.xf;

	float point_y = y;
	if (y < block.yi) point_y = block.yi;
	if (y > block.yf) point_y = block.yf;

	float distancia = (x-point_x)*(x-point_x) + (y-point_y)*(y-point_y);

	if (distancia <= raio*raio) {
		vely*=-1;
		return true;
	}

	return false;
}