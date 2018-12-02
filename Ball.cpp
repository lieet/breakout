#include "Constants.h"
#include "Ball.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>

Ball::Ball(float raio)
{
	this->raio = raio;

	this->r = 0;
	this->g = 0;
	this->b = 0;

	this->scalex = .5;
	this->scaley = .5;
	this->scalez = .5;

	this->velx = ballSpeed;
	this->vely = ballSpeed;
}

void Ball::Draw()
{
	glColor4f(r, g, b, 1);
	glPushMatrix();
		glTranslatef(x, y, 0);
		glScalef(scalex, scaley, scalez);
		glutSolidSphere(1, 50, 50);
	glPopMatrix();
}

void Ball::DrawBoundingBox()
{
	glColor4f(1-r, 1-g, 1-b, 1);
	glBegin(GL_LINE_LOOP);
		for(float a = 0; a < 2*M_PI; a+=0.1) {
			glVertex2f(x + raio/2.0*cos(a), y + raio/2.0*sin(a));
		}
	glEnd();
}

void Ball::Update()
{
	//verifica se a bola esta dentro das dimensões da tela
	if (this->getXi() <= left || this->getXf() >= right)
		velx*=-1;
	if (this->getYf() >= top)
		vely*=-1;
	
	if (moving)
		Move(velx, vely);
}

bool Ball::checkCollision(Block block)
{
	float min_x = x;
	if (block.getXf() < min_x) min_x = block.getXf();
	float min_y = y;
	if (block.getYf() < min_y) min_y = block.getYf();
	float nearest_x = block.getXi();
	if (min_x > nearest_x) nearest_x = min_x;
	float nearest_y = block.getYi();
	if (min_y > nearest_y) nearest_y = min_y;
	float delta_x = x - nearest_x;
	float delta_y = y - nearest_y;
	if (delta_x*delta_x + delta_y*delta_y < raio*raio) {
		if (delta_y != 0)
			vely*=-1;
		if (delta_x != 0)
			velx*=-1;

		return true;
	}
	return false;
}

void Ball::Move(float x, float y)
{
	this->x += x;
	this->y += y;
	Draw();
}

float Ball::getXi()
{
	return x - raio;
}

float Ball::getXf()
{
	return x + raio;
}

float Ball::getYi()
{
	return y - raio;
}

float Ball::getYf()
{
	return y + raio;
}