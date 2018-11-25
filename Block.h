#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "Object.h"

class Block : public Object {
public:
	int value, size;

	Block(float, float, float, float, float, int, int);

	void Draw();
	void Update();
	void Move(float, float);
	float getXi();
	float getXf();
	float getYi();
	float getYf();
};

#endif