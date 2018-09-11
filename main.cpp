#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "Object.h"
#include "Ball.h"
#include "Block.h"
using namespace std;

enum GameState {PAUSED, RUNNING, GAME_OVER} game_state; //possíveis estados para o jogo
enum BlockType {PLAYER, GAME_PIECE}; //possíveis tipos de bloco
float left = 0, right = 8, bottom = 0, top = 6; //dimensões da tela
float a, d; //posição da barra do jogador no eixo x
int score = 0, valueBlock = 20;

// Objetos do jogo
Ball ball(0.09);
vector<Block> blocosAtivos;
vector<Block> blocosRemovidos;

//imprime a tela de instruções
void instructions()
{
	glColor3f(0, 0, 0);
	char texto[50];

	glRasterPos2f(3, 2.6);
	sprintf(texto, "q - exit");
	for (int i = 0; i < strlen(texto); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);

	glRasterPos2f(3, 2.8);
	sprintf(texto, "p - pause\\unpause");
	for (int i = 0; i < strlen(texto); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
	
	glRasterPos2f(3, 3);
	sprintf(texto, "r - restart");
	for (int i = 0; i < strlen(texto); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);

	glRasterPos2f(3, 3.2);
	sprintf(texto, "a - move to the left");
	for (int i = 0; i < strlen(texto); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);

	glRasterPos2f(3, 3.4);
	sprintf(texto, "d - move to the right");
	for (int i = 0; i < strlen(texto); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);

	glRasterPos2f(3, 3.6);
	sprintf(texto, "space - start the game");
	for (int i = 0; i < strlen(texto); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);

	glRasterPos2f(3, 3.8);
	sprintf(texto, "Keyboard Keys:");
	for (int i = 0; i < strlen(texto); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
}

void init() {
	a = 3.15;
	d = 4.75;
	score = 0;
	valueBlock = 20;

	ball.x = 4;
	ball.y = 0.7;
	ball.moving = false;

	glClearColor(0.5, 0.5, 0.5, 0.0);

	//cria barras aleatorias
	for(float i = 0; i < 1.6; i += 0.4){
		for(float j = 0.2; j < 7; j += 1.51){
			Block block(j, 5.5-i, j+1.5, 5.7-i, 1, 1-i, i, valueBlock, GAME_PIECE);
			blocosAtivos.push_back(block);
		}
		valueBlock -= 5;
	}

	game_state = RUNNING;
}

//limpa a tela com a cor de fundo
void gameOverState()
{
	glColor3f(0, 0, 0);
	glRasterPos2f(3, 3);
	char texto[20];
	sprintf(texto, "Game Over");
	for (int i = 0; i < strlen(texto); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
}

//Exibe a pontuação do jogador
void printScore()
{
	glColor3f(0, 0, 0);
	glRasterPos2f(0.2, 5.8);
	char texto[20];
	sprintf(texto, "Score: %d", score);
	for (int i = 0; i < strlen(texto); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
}

//Exibe o valor de cada barra
void printValue(float x, float y, int value)
{
	glColor3f(0, 0, 0);
	glRasterPos2f(x, y);
	char texto[20];
	sprintf(texto, "%d", value);
	for (int i = 0; i < strlen(texto); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, texto[i]);
}

void mainGame()
{
	//cria a barra do jogador
	Block player_block(a, 0.4, d, 0.6, 0.2, 0.2, 0.2, 0, PLAYER);
	player_block.Draw();
	player_block.Update();
	ball.checkCollision(player_block);

	//desenha a bola
	ball.Draw();
	ball.Update();
	printScore();

	//verifica se a bola ainda esta em jogo
	if (ball.y < 0) game_state = GAME_OVER;

	//desenha as barras aleatorias
	vector<Block>::iterator iter;
	for (iter = blocosAtivos.begin(); iter != blocosAtivos.end(); ) {
		Block bloco = *iter;
		if (ball.checkCollision(bloco)) { 
			blocosAtivos.erase(iter);
			blocosRemovidos.push_back(bloco);
			score += bloco.value;
		} else {
			bloco.Draw();
			printValue((bloco.xf + bloco.xi)/2, bloco.yi+0.05, bloco.value);
			iter++;
		}
	}
}

void displayCallback() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);

	if (not ball.moving) instructions();

	switch (game_state)
	{
		case GAME_OVER: gameOverState(); break;
		case PAUSED:
		case RUNNING: mainGame(); break;
	}

	glutSwapBuffers();
	glFlush();
}

void keyboardCallback(unsigned char key, int x, int y) {
	if (key == 'q') {
		exit(-1);
	}
	//pausa
	if (key == 'p'){
		if (game_state == PAUSED) {
			ball.moving = true;
			game_state = RUNNING;
		} else if (game_state == RUNNING) {
			ball.moving = false;
			game_state = PAUSED;
		}
	}
	//reinicia o jogo
	if (key == 'r'){
		blocosAtivos.clear();
		blocosRemovidos.clear();
		init();
		game_state = RUNNING;
	}
	if (game_state == RUNNING) {
		//move a barra pra esquerda
		if (key == 'a' && a > 0) {
			if (not ball.moving and a>0) ball.x -= 0.2;
			a -= 0.2;
			d -= 0.2;
		}
		//move a barra pra direita
		if (key == 'd' && d < 8) {
			if (not ball.moving and d<8) ball.x += 0.2;
			a += 0.2;
			d += 0.2;
		}
		//verifica se a barra de espaço foi teclada para iniciar o jogo
		if (key == 32) {
			ball.moving = true;
		}
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