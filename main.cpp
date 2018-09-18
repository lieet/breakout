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

enum GameState {PAUSED, RUNNING, GAME_OVER, GAME_WON} game_state; //possíveis estados para o jogo
const float left = 0, right = 8, bottom = 0, top = 6; //dimensões da tela
int score, valueBlock;
int msToTimerFunc = 20000; //taxa de atualização, em ms, da função timer

// Objetos do jogo
Ball ball(0.09);
Block player_block(3.15, 0.4, 4.75, 0.6, 0.2, 0.2, 0.2, 0);
vector<Block> blocosAtivos;
vector<Block> blocosRemovidos;

//valor inteiro aleatório entre 0 e maxValue
int randomi(int maxValue) {
	return rand() % maxValue;
}

void init() {
	score = 0;
	valueBlock = 20;

	ball.x = 4;
	ball.y = 0.7;
	ball.velx = 0.035;
	ball.vely = 0.035;
	ball.moving = false;

	player_block.xi = 3.15;
	player_block.xf = 4.75;

	glClearColor(0.5, 0.5, 0.5, 0.0);

	//cria barras aleatorias
	for(float i = 0; i < 1.6; i += 0.4){
		for(float j = 0.2; j < 7; j += 1.51){
			Block block(j, 5.5-i, j+1.5, 5.7-i, 1, 1-i, i, valueBlock);
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
	ball.Update();

	//verifica se a bola ainda esta em jogo
	if (ball.y < 0)
		game_state = GAME_OVER;

	if (blocosAtivos.empty())
		game_state = GAME_WON;

	//cria a barra do jogador
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

	if (not ball.moving)
	{
		ball.Draw();
		instructions();
	}

	switch (game_state)
	{
		case GAME_OVER: gameOverState(); break;
		case GAME_WON: gameWonState(); break;
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
		if (key == 'a' && player_block.xi > left) {
			if (not ball.moving)
				ball.Move(-0.2, 0);
			player_block.Move(-0.2, 0);
		}
		//move a barra pra direita
		if (key == 'd' && player_block.xf < right) {
			if (not ball.moving)
				ball.Move(0.2, 0);
			player_block.Move(0.2, 0);
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