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
	this->scalez = .4;

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

void Block::DrawBoundingBox()
{
	glColor3f(1-r, 1-g, 1-b);
	float left = this->getXi();
	float bottom = this->getYi();
	float right = this->getXf();
	float top = this->getYf();
	glBegin(GL_LINES); 
		glVertex3f(left, bottom, scalez);
  		glVertex3f(left, top, scalez);

  		glVertex3f(left, bottom, scalez);
  		glVertex3f(right, bottom, scalez);

		glVertex3f(right, top, scalez);
  		glVertex3f(left, top, scalez);
  		
  		glVertex3f(right, top, scalez);
  		glVertex3f(right, bottom, scalez);
 	glEnd();
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
	return x - scalex/2.0;
}

float Block::getXf()
{
	return x + scalex/2.0;
}

float Block::getYi()
{
	return y - scaley/2.0;
}

float Block::getYf()
{
	return y + scaley/2.0;
}