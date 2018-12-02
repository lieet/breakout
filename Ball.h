#ifndef _BALL_H_
#define _BALL_H_

#include "Object.h"
#include "Block.h"

class Ball : public Object {
public:
	float velx, vely;		// velocidade em cada coordenada
	float raio;
	bool moving;			// indica se a bola está em movimento

	Ball(float);

	void Draw();
	void DrawBoundingBox();
	void Update();
	void Move(float, float);
	bool checkCollision(Block);
	
	float getXi();
	float getXf();
	float getYi();
	float getYf();
};

#endif