#include "Block.h"
#include <stdio.h>
#include <GL/glut.h>
#include <GL/glu.h>

Block::Block(float xi, float yi, float xf, float yf)
{
	this->xi = xi;
	this->yi = yi;
	this->xf = xf;
	this->yf = yf;
}

void Block::Draw()
{
	glRectf(xi, yi, xf, yf);
}

void Block::Update()
{
}