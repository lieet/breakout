#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <vector>
#include "Object.h"
#include "Ball.h"
#include "Block.h"
using namespace std;

float left = 0, right = 8, bottom = 0, top = 6;
float a = 3.15, d = 4.75; //posição da barra do jogador no eixo x
bool pause = false;

// Objetos do jogo
Ball ball(4, 1, 0.09);
vector<Block> blocos;

void init() {
	a = 3.15;
	d = 4.75;

	ball.x = 4;
	ball.y = 1;
	ball.velx = 0.02;
	ball.vely = 0.02;

	glClearColor(0.5, 0.5, 0.5, 0.0);

	//cria barras aleatorias
	for(float i = 0; i < 1.6; i += 0.4){
		for(float j = 0.2; j < 7; j += 1.51){
			Block block(j, 5.5-i, j+1.5, 5.7-i, 1, 1-i, i);
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
	Block player_block(a, 0.4, d, 0.6, 0.2, 0.2, 0.2);
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
	}

	//limpa a tela com a cor de fundo
	/*glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	glRasterPos2f(-1, 0);
	char texto[20];
	sprintf(texto, "Game Over");
	for(int i = 0; i < strlen(texto); i++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);*/

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
		blocos.clear();
		init();
		pause = false;
	}
	//move a barra pra esquerda
	if (key == 'a' && a > 0.2) {
		a -= 0.2;
		d -= 0.2;
	}
	//move a barra pra direita
	if (key == 'd' && d < 7.8) {
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