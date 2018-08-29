#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
using namespace std;

float left = -4, right = 4, top = 3, bottom = -3;

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

	glutSwapBuffers();
	glFlush();
}

void keyboardCallback(unsigned char key, int x, int y) {
	if (key == 'q') {
		exit(-1);
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
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Breakout");
	glutKeyboardFunc(keyboardCallback);
	glutMouseFunc(NULL);
	glutDisplayFunc(displayCallback);
	glutIdleFunc(temporizador);
	init();
	glutMainLoop();

	return 0;
}