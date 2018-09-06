#ifndef _BALL_H_
#define _BALL_H_

#include "Object.h"
#include "Block.h"

class Ball : public Object {
public:
	float x, y;				// posi��o (x, y) do centro do c�rculo no plano
	float velx, vely;		// velocidade em cada coordenada
	float raio;
	bool moving;			// indica se a bola est� em movimento

	Ball(float);

	void Draw();
	void Update();
	bool checkCollision(Block);
};

#endif