#include "Block.h"
#include <GL/glut.h>
#include <GL/glu.h>

Block::Block(float xi, float yi, float xf, float yf, float r, float g, float b, int v, int tipo)
{
	this->xi = xi;
	this->yi = yi;
	this->xf = xf;
	this->yf = yf;
	this->value = v;

	this->r = r;
	this->g = g;
	this->b = b;

	this->tipo = tipo;
}

void Block::Draw()
{
	glColor3f(r, g, b);
	glRectf(xi, yi, xf, yf);
}

void Block::Update()
{
}