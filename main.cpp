#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <vector>
#include "GameInfo.h"
#include "Object.h"
#include "Ball.h"
#include "Block.h"
using namespace std;

enum GameState {PAUSED, RUNNING, GAME_OVER} game_state; //possíveis estados para o jogo
enum BlockType {PLAYER, GAME_PIECE}; //possíveis tipos de bloco
float left = 0, right = 8, bottom = 0, top = 6; //dimensões da tela
float a, d; //posição da barra do jogador no eixo x
int score = 0, valueBlock = 20;
int msToTimerFunc = 15000; //taxa de atualização, em ms, da função timer

// Objetos do jogo
Ball ball(0.09);
vector<Block> blocosAtivos;
vector<Block> blocosRemovidos;

//valor inteiro aleatório entre 0 e maxValue
int randomi(int maxValue) {
	return rand() % maxValue;
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

void mainGame()
{
	printScore(score);

	//desenha a bola
	ball.Draw();
	ball.Update();

	//verifica se a bola ainda esta em jogo
	if (ball.y < 0) game_state = GAME_OVER;

	//cria a barra do jogador
	Block player_block(a, 0.4, d, 0.6, 0.2, 0.2, 0.2, 0, PLAYER);
	player_block.Draw();

	ball.checkCollision(player_block);

	//atualiza as barras aleatorias
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
}

//função executada periodicamente para inserir novos blocos
void reporBlocos(int value) {
	int n = blocosRemovidos.size();
	if (n > 0){
		int index = randomi(n);
		blocosAtivos.push_back(blocosRemovidos.at(index));
		blocosRemovidos.erase(blocosRemovidos.begin() + index);
	}
	glutTimerFunc(msToTimerFunc, reporBlocos, 0);
}

int main(int argc, char **argv) {
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-800)/2, (glutGet(GLUT_SCREEN_HEIGHT)-600)/2);
	glutCreateWindow("Breakout - By Emanoel Dantas e Lucas Alessio");
	glutKeyboardFunc(keyboardCallback);
	glutMouseFunc(NULL);
	glutDisplayFunc(displayCallback);
	glutTimerFunc(msToTimerFunc, reporBlocos, 0);
	glutIdleFunc(displayCallback);
	init();
	glutMainLoop();

	return 0;
}