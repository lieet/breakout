#ifndef _BALL_H_
#define _BALL_H_

#include "Object.h"
#include "Block.h"

class Ball : public Object {
public:
	float x, y;				// posição (x, y) do centro do círculo no plano
	float velx, vely;		// velocidade em cada coordenada
	float raio;
	bool moving;			// indica se a bola está em movimento

	Ball(float);

	void Draw();
	void Update();
	void Move(float, float);
	bool checkCollision(Block);
};

#endif