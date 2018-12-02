#include "Block.h"
#include <GL/glut.h>
#include <GL/glu.h>

Block::Block(float x, float y, int v, int size)
{
	this->x = x;
	this->y = y;
	this->value = v;
	this->size = size;

	this->scalex = 3;
	this->scaley = 1;
	this->scalez = .4;
}

void Block::Draw()
{
	glPushMatrix();
		glTranslatef(x, y, 0);
		glScalef(scalex, scaley, scalez);
		this->glutSolidCube(size);
	glPopMatrix();
}

void Block::DrawBoundingBox()
{
	/*glColor3f(1, 1, 1);
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
 	glEnd();*/
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

void Block::drawBox(GLfloat size, GLenum type)
{
	static GLfloat n[6][3] =
	{
		{-1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{1.0, 0.0, 0.0},
		{0.0, -1.0, 0.0},
		{0.0, 0.0, 1.0},
		{0.0, 0.0, -1.0}
	};
	static GLint faces[6][4] =
	{
		{0, 1, 2, 3},
		{3, 2, 6, 7},
		{7, 6, 5, 4},
		{4, 5, 1, 0},
		{5, 6, 2, 1},
		{7, 4, 0, 3}
	};
	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

	for (i = 5; i >= 0; i--) {
		glBegin(type);
			glNormal3fv(&n[i][0]);
			glTexCoord2f(0,0);
			glVertex3fv(&v[faces[i][0]][0]);
			glTexCoord2f(1,0);
			glVertex3fv(&v[faces[i][1]][0]);
			glTexCoord2f(1,1);
			glVertex3fv(&v[faces[i][2]][0]);
			glTexCoord2f(0,1);
			glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void Block::glutSolidCube(GLdouble size)
{
    this->drawBox(size, GL_QUADS);
}