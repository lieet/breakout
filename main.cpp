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
bool showTextDetails = false, acompanharBall = false;

// Objetos do jogo
Ball ball(OBJ_SIZE);
Block player_block((left+right)/2, bottom+1, 0, OBJ_SIZE);
vector<Block> blocosAtivos;
vector<Block> blocosRemovidos;

unsigned char * loadPPM(char *filename, int width, int height)
{
    FILE *arq = fopen(filename, "r");
    char format[3];
    int max;
    fscanf(arq, "%s %d %d %d\n", format, &width, &height, &max);
    unsigned char * data = (unsigned char *) malloc(sizeof(unsigned char)*width*height*3);
    fread(data, sizeof(unsigned char), width*height*3, arq);
    fclose(arq);
    return data;
}

void loadBlockTexture()
{  
    glBindTexture(GL_TEXTURE_2D, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

    int width=1024, height=1024;
	char filepath[] = "concrete.ppm";
	unsigned char *data = loadPPM(filepath, width, height);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);
}

void loadFieldTexture()
{  
    glBindTexture(GL_TEXTURE_2D, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

    int width=1000, height=1000;
	char filepath[] = "ice.ppm";
	unsigned char *data = loadPPM(filepath, width, height);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);
}

//valor inteiro aleatório entre 0 e maxValue
int randomi(int maxValue)
{
	return rand() % maxValue;
}

void drawGameLimits()
{
	loadFieldTexture();
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,1.0);
		glTexCoord2f(0,0);
		glVertex3f(left,bottom,0);
		glTexCoord2f(1,0);
		glVertex3f(right,bottom,0);
		glTexCoord2f(1,1);
		glVertex3f(right,top,0);
		glTexCoord2f(0,1);
		glVertex3f(left,top,0);
 	glEnd(); 
 	glDisable(GL_TEXTURE_2D);
}

void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 1, 40);

	anglex = 0;
	angley = 0;
	z = MAX_ZOOM_IN;

	score = 0;
	valueBlock = 20;

	ball.x = (left+right)/2;
	ball.y = bottom+2.5;
	ball.velx = ballSpeed;
	ball.vely = ballSpeed;
	ball.moving = false;

	player_block.x = (left+right)/2;

	glClearColor(0.25, 0.25, 0.25, 0.0);

	//cria barras aleatorias
	for (float i = left+5; i < right-5; i += 6)
	{
		for (float j = top-10; j < top-2; j += 2)
		{
			Block block(i, j, valueBlock, OBJ_SIZE);
			blocosAtivos.push_back(block);
		}
		valueBlock -= 5;
	}

	game_state = RUNNING;
}

void mainGame()
{	
	if (drawBB)
		drawGameLimits();
	if (showTextDetails)
		printScore(score);

	//desenha a bola
	if (ball.moving)
	{
		ball.Update();
	}
	ball.Draw();
	if (drawBB)
		ball.DrawBoundingBox();

	loadBlockTexture();
	glEnable(GL_TEXTURE_2D);

	//verifica se a bola ainda esta em jogo
	if (ball.y <= bottom)
		game_state = GAME_OVER;

	if (blocosAtivos.empty())
		game_state = GAME_WON;

	//cria a barra do jogador
	player_block.Draw();
	if (drawBB)
		player_block.DrawBoundingBox();
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
			if (drawBB)
				bloco.DrawBoundingBox();
			if (showTextDetails)
				printValue(bloco.x, bloco.y, bloco.value);
			iter++;
		}
	}
}

void atualizarCamera()
{
	float centerx = (left+right)/2.0;
	if (angley >= 50)
		centerx = player_block.x;
	float centery = (bottom+top)/2.0;

	if (acompanharBall)
	{
		centerx = ball.x;
		centery = ball.y;
	}

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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
				ball.Move(-playerMove, 0);
			player_block.Move(-playerMove, 0);
		}
		if (key == 'a' && player_block.getXf() < right)
		{
			if (not ball.moving)
				ball.Move(playerMove, 0);
			player_block.Move(playerMove, 0);
		}
		//verifica se a barra de espaço foi teclada para iniciar o jogo
		if (key == 32)
		{
			ball.moving = true;
		}
	}
	//move a camera
	if(key == 'k' and angley > MIN_ANGLE_Y)
		angley -= 10;
	else if(key == 'i' and angley < MAX_ANGLE_Y)
		angley += 10;
	else if(key == 'u' and z > MAX_ZOOM_IN)
		z -= 2;
	else if(key == 'o' and z < MAX_ZOOM_OUT)
		z += 2;

	if(key == 't')
		showTextDetails = not showTextDetails;
	if(key == 'z')
		acompanharBall = not acompanharBall;

	if (key == 'c')
		printf("c - commands\n\nq - exit\np - pause/unpause\nr - restart\nd/a - move player\nspace - start the game\n\nk/i - move the camera\nu/o - zoom\nz - follow the ball\nt - show text details\n");
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
	glutTimerFunc(updateTimerMs, reporBlocos, 0);
}

int main(int argc, char **argv) {
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-WIDTH)/2, (glutGet(GLUT_SCREEN_HEIGHT)-HEIGHT)/2);
	glutCreateWindow("Breakout - By Emanoel Dantas e Lucas Alessio");
	glutKeyboardFunc(keyboardCallback);
	glutMouseFunc(NULL);
	
	float centerx = (left+right)/2.0;
	float centery = (bottom+top)/2.0;

	//Iluminação
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat vetorPosicao[4] = {centerx, centery, 2, 1.0}; //coordenadas homogêneas
	glLightfv(GL_LIGHT0, GL_POSITION, vetorPosicao); 
	GLfloat vetorCor[4] = {0.5, 0.5, 0.5, 1.0}; //RGBA
	glLightfv(GL_LIGHT0, GL_AMBIENT, vetorCor);
	
	//Especificando o material dos objetos
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glutDisplayFunc(displayCallback);
	glutTimerFunc(updateTimerMs, reporBlocos, 0);
	glutIdleFunc(displayCallback);
	loadBlockTexture();
	init();
	glutMainLoop();

	return 0;
}