#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "Object.h"
#include <GL/glu.h>

class Block : public Object {
public:
	int value, size;

	Block(float, float, int, int);

	void Draw();
	void DrawBoundingBox();
	void Update();
	void Move(float, float);
	
	float getXi();
	float getXf();
	float getYi();
	float getYf();

	void drawBox(GLfloat size, GLenum type);
	void glutSolidCube(GLdouble size);
};

#endif