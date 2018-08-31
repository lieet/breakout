#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
using namespace std;

float left = -4, right = 4, top = 3, bottom = -3;
float a=-0.75,d=0.75; 

//desenha uma barra
void barra(float x1, float y1, float x2, float y2){
	glRectf(x1, y1, x2, y2);
}

void init() {
	glClearColor(0.5, 0.5, 0.5, 0.0);
}

void displayCallback() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.2, 0.2, 0.2);
	barra(a,-2,d,-2.3); //desenha a barra do jogador

	//desenha barras aleatorias
	glColor3f(1, 0, 0);
	for(float i = 0; i < 1.6; i += 0.4){
		for(float j = -3.8; j < 3; j += 1.51){			
			barra(j, 2.5-i, j+1.5, 2.8-i);
		}
		glColor3f(0, 1-i, i);
	}

	glutSwapBuffers();
	glFlush();
}

void keyboardCallback(unsigned char key, int x, int y) {
	if (key == 'q') {
		exit(-1);
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
	glutCreateWindow("Breakout - By Emanoel Dantas e Lucas Aléssio");
	glutKeyboardFunc(keyboardCallback);
	glutMouseFunc(NULL);
	glutDisplayFunc(displayCallback);
	glutIdleFunc(temporizador);
	init();
	glutMainLoop();

	return 0;
}