#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "Object.h"

class Block : public Object {
public:
	float xi, yi, xf, yf;				// retângulo delimitado por (xi, yi) e (xf, yf)

	Block(float, float, float, float, float, float, float);

	void Draw();
	void Update();
};

#endif