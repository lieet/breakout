#ifndef _GAMEINFO_H_
#define _GAMEINFO_H_

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
void printScore(int score)
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

#endif