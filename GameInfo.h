#ifndef _GAMEINFO_H_
#define _GAMEINFO_H_

#include "Constants.h"

void gameOverState()
{
	glColor3f(0, 0, 0);
	glRasterPos3f((left+right)/2, (top+bottom)/2, .5);
	char texto[20];
	sprintf(texto, "Game Over");
	for (int i = 0; i < strlen(texto); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
}

void gameWonState()
{
	glColor3f(0, 0, 0);
	glRasterPos3f((left+right)/2, (top+bottom)/2, .5);
	char texto[20];
	sprintf(texto, "You Won !!!");
	for (int i = 0; i < strlen(texto); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
}

//Exibe a pontuação do jogador
void printScore(int score)
{
	glColor3f(0, 0, 0);
	glRasterPos3f(top-1.5, right-1.5, .5);
	char texto[20];
	sprintf(texto, "Score: %d", score);
	for (int i = 0; i < strlen(texto); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
}

//Exibe o valor de cada barra
void printValue(float x, float y, int value)
{
	glColor3f(0, 0, 0);
	glRasterPos3f(x, y, .5);
	char texto[20];
	sprintf(texto, "%d", value);
	for (int i = 0; i < strlen(texto); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, texto[i]);
}

#endif