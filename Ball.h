#ifndef _BALL_H_
#define _BALL_H_

class Ball {
public:
	float x, y;				// posição (x, y) no plano
	float velx, vely;		// velocidade em cada coordenada
	float raio;

	Ball(float, float, float);

	void Draw();
	void Update(float a, float d);
	float getY();
	void setX(float x);
	void setY(float y);
};

#endif