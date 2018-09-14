#include "Ball.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>

Ball::Ball(float raio)
{
	this->raio = raio;

	r = 0;
	g = 0;
	b = 0;

	velx = 0.035;
	vely = 0.035;
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
	if (moving) {
		x+=velx;
		y+=vely;

		//verifica se a bola esta dentro das dimensões da tela
		if (x <= 0 || x >= 8)
			velx*=-1;
		else if (y <= 0 || y >= 6)
			vely*=-1;
	}
}

//algorithm: https://yal.cc/rectangle-circle-intersection-test/
bool Ball::checkCollision(Block block)
{
	float min_x = x;
	if (block.xf < min_x) min_x = block.xf;
	float min_y = y;
	if (block.yf < min_y) min_y = block.yf;

	float nearest_x = block.xi;
	if (min_x > nearest_x) nearest_x = min_x;
	float nearest_y = block.yi;
	if (min_y > nearest_y) nearest_y = min_y;

	float delta_x = x - nearest_x;
	float delta_y = y - nearest_y;

	if (delta_x*delta_x + delta_y*delta_y < raio*raio) {
		vely*=-1;
		return true;
	}

	return false;
}