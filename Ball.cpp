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

void Ball::Update()
{
	//verifica se a bola esta dentro das dimensões da tela
	if (this->getXi() <= left || this->getXf() >= right)
		velx*=-1;
	if (this->getYi() <= bottom || this->getYf() >= top)
		vely*=-1;
	
	if (moving)
		Move(velx, vely);
}

bool Ball::checkCollision(Block block)
{
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
	return x - 2*scalex;
}

float Ball::getXf()
{
	return x + 2*scalex;
}

float Ball::getYi()
{
	return y - 2*scaley;
}

float Ball::getYf()
{
	return y + 2*scaley;
}