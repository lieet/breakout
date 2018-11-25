#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <vector>
#include "Constants.h"
#include "GameInfo.h"
#include "Object.h"
#include "Ball.h"
#include "Block.h"
using namespace std;

int score, valueBlock;
float anglex, angley, z;
enum GameState {PAUSED, RUNNING, GAME_OVER, GAME_WON} game_state; //possíveis estados para o jogo
bool showTextDetails = false;

// Objetos do jogo
Ball ball(1);
Block player_block((left+right)/2, bottom+1, 0.2, 0.2, 0.2, 0, 1);
vector<Block> blocosAtivos;
vector<Block> blocosRemovidos;

//valor inteiro aleatório entre 0 e maxValue
int randomi(int maxValue)
{
	return rand() % maxValue;
}

void drawGameLimits()
{
	glColor4f(1, 1, 1, 1);
	glBegin(GL_LINES); 
		glVertex3f(left, bottom, 1);
  		glVertex3f(left, top, 1);

  		glVertex3f(left, bottom, 1);
  		glVertex3f(right, bottom, 1);

		glVertex3f(right, top, 1);
  		glVertex3f(left, top, 1);
  		
  		glVertex3f(right, top, 1);
  		glVertex3f(right, bottom, 1);
 	glEnd(); 
}

void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 1, 40);

	anglex = 0;
	angley = 0;
	z = 20;

	score = 0;
	valueBlock = 20;

	ball.x = (left+right)/2;
	ball.y = bottom+3;
	ball.velx = ballSpeed;
	ball.vely = ballSpeed;
	ball.moving = false;

	player_block.x = (left+right)/2;

	glClearColor(0.5, 0.5, 0.5, 0.0);

	//cria barras aleatorias
	for (float i = left+5; i < right; i += 5)
	{
		for (float j = top-10; j < top-2; j += 2)
		{
			Block block(i, j, 1, (1-i)/20, i/20, valueBlock, 1);
			blocosAtivos.push_back(block);
		}
		valueBlock -= 5;
	}

	game_state = RUNNING;
}

void mainGame()
{
	drawGameLimits();
	if (showTextDetails)
		printScore(score);

	//desenha a bola
	ball.Update();

	//verifica se a bola ainda esta em jogo
	if (ball.y <= bottom)
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
			if (showTextDetails)
				printValue(bloco.x/2, bloco.y+0.1, bloco.value);
			iter++;
		}
	}
}

void atualizarCamera()
{
	float centerx = (left+right)/2;
	float centery = (bottom+top)/2;

	float radianx = anglex*PI/180;
	float radiany = angley*PI/180;
	float X = z * (-sin(radianx)) * cos(radiany) + centerx;
	float Y = z * (-sin(radiany)) + centery;
	float Z = -z * cos(radianx) * cos(radiany);

	gluLookAt(X, Y, Z, centerx, centery, 0, 0, 1, 0);
}

void displayCallback() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	atualizarCamera();

	glClear(GL_COLOR_BUFFER_BIT);

	if (not ball.moving)
	{
		ball.Draw();
		if (showTextDetails)
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
		if (key == 'd' && player_block.getXi() > left)
		{
			if (not ball.moving)
				ball.Move(-0.4, 0);
			player_block.Move(-0.4, 0);
		}
		if (key == 'a' && player_block.getXf() < right)
		{
			if (not ball.moving)
				ball.Move(0.4, 0);
			player_block.Move(0.4, 0);
		}
		//verifica se a barra de espaço foi teclada para iniciar o jogo
		if (key == 32)
		{
			ball.moving = true;
		}
	}
	//move a camera
	if(key == 'j')
		anglex -= 10;
	else if(key == 'l')
		anglex += 10;
	else if(key == 'k')
		angley -= 10;
	else if(key == 'i')
		angley += 10;
	else if(key == 'u')
		z -= 2;
	else if(key == 'o')
		z += 2;
}

//função executada periodicamente para inserir novos blocos
void reporBlocos(int value)
{
	if (game_state == RUNNING)
	{
		int n = blocosRemovidos.size();
		if (n > 0)
		{
			int index = randomi(n);
			blocosAtivos.push_back(blocosRemovidos.at(index));
			blocosRemovidos.erase(blocosRemovidos.begin() + index);
		}
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