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
	Block block(a,-2,d,-2.2, 0.2, 0.2, 0.2);
	block.Draw();
	block.Update();

	//cria barras aleatorias
	for(float i = 0; i < 1.6; i += 0.4){
		for(float j = -3.8; j < 3; j += 1.51){
			Block block(j, 2.5-i, j+1.5, 2.7-i, 1, 1-i, i);
			blocos.push_back(block);
		}
	}

	//desenha as barras aleatorias
	for(Block block: blocos){
		block.Draw();
		block.Update();
	}

	//desenha a bola
	ball.Draw();
	ball.Update();

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
		ball.x = 0;
		ball.y = 0;
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