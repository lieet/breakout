#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "Object.h"
#include "Ball.h"
#include "Block.h"
using namespace std;

float left = -4, right = 4, top = 3, bottom = -3;
float a=-0.75,d=0.75;
bool pause = false;

// Objetos do jogo
Ball ball(0, 0, 0.09);
vector<Block> blocos;

void init() {
	glClearColor(0.5, 0.5, 0.5, 0.0);

	//cria barras aleatorias
	for(float i = 0; i < 1.6; i += 0.4){
		for(float j = -3.8; j < 3; j += 1.51){
			Block block(j, 2.5-i, j+1.5, 2.7-i, 1, 1-i, i);
			blocos.push_back(block);
		}
	}
}

void displayCallback() {
	if(pause)
		return;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);

	//cria a barra do jogador
	Block player_block(a,-2.6,d,-2.8, 0.2, 0.2, 0.2);
	player_block.Draw();
	player_block.Update();
	ball.checkCollision(player_block);

	//desenha a bola
	ball.Draw();
	ball.Update();

	//desenha as barras aleatorias
	for (Block bloco: blocos){
		ball.checkCollision(bloco);
		bloco.Draw();
		bloco.Update();
	}

	//verifica se colidiu com a barra do jogador
	/* if(y < -2 && y > -2.15 && x > a && x < d){
			y = -2;
			vely*=-1;
	}*/

	glutSwapBuffers();
	glFlush();
}

void keyboardCallback(unsigned char key, int x, int y) {
	if (key == 'q') {
		exit(-1);
	}
	//pausa
	if(key == 'p'){
		pause = not pause;
	}
	//reinicia o jogo
	if(key == 'r'){
		a = -0.75;
		d = 0.75;
		ball.alive = true;
		ball.x = 0;
		ball.y = 0;
		ball.velx = 0.02;
		ball.vely = 0.02;
		blocos.clear();
		init();
		pause = false;
	}
	//move a barra pra esquerda
	if (key == 'a' && a > -3.8) {
		a -= 0.2;
		d -= 0.2;
	}
	//move a barra pra direita
	if (key == 'd' && d < 3.8) {
		a += 0.2;
		d += 0.2;
	}

	glutPostRedisplay();
}

void temporizador() {
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-800)/2, (glutGet(GLUT_SCREEN_HEIGHT)-600)/2);
	glutCreateWindow("Breakout - By Emanoel Dantas e Lucas Alessio");
	glutKeyboardFunc(keyboardCallback);
	glutMouseFunc(NULL);
	glutDisplayFunc(displayCallback);
	glutIdleFunc(temporizador);
	init();
	glutMainLoop();

	return 0;
}