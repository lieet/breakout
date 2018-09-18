#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "Object.h"

class Block : public Object {
public:
	float xi, yi, xf, yf;				// retângulo delimitado por (xi, yi) e (xf, yf)
	int value;							// pontuação pela remoção do bloco

	Block(float, float, float, float, float, float, float, int);

	void Draw();
	void Update();
	void Move(float, float);
};

#endif