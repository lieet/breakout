#ifndef _BALL_H_
#define _BALL_H_

class Ball {
public:
	float x, y;				// posi��o (x, y) no plano
	float velx, vely;		// velocidade em cada coordenada
	float raio;

	Ball(float, float, float);

	void Draw();
	void Update();
};

#endif