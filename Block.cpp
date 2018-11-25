#include "Block.h"
#include <GL/glut.h>
#include <GL/glu.h>

Block::Block(float x, float y, float r, float g, float b, int v, int size)
{
	this->x = x;
	this->y = y;
	this->value = v;
	this->size = size;

	this->scalex = 3;
	this->scaley = 1;
	this->scalez = 1;

	this->r = r;
	this->g = g;
	this->b = b;
}

void Block::Draw()
{
	glColor4f(r, g, b, 1);
	glPushMatrix();
		glTranslatef(x, y, 0);
		glScalef(scalex, scaley, scalez);
		glutSolidCube(size);
	glPopMatrix();
}

void Block::Update()
{
}

void Block::Move(float x, float y)
{
	this->x += x;
	this->y += y;
	Draw();
}

float Block::getXi()
{
	return x - scalex;
}

float Block::getXf()
{
	return x + scalex;
}

float Block::getYi()
{
	return y - scaley;
}

float Block::getYf()
{
	return y + scaley;
}