#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>

#include <GL/glut.h>
#include "stdlib.h"
#include "math.h"
#include "vector2.h"
#include "SPHMethods.h"
#include "GlutMethods.h"

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Васильев К.В. / НИР / FPS: ");
	Initialization();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyboardHotkeys);
	glutPassiveMotionFunc(MouseMoving);
	glutMouseFunc(MouseInputs);
	glutMainLoop();
}
