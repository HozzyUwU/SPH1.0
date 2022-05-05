#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <ctime>

#include <GL/glut.h>
#include "stdlib.h"
#include "math.h"
#include "vector2.h"
#include "SPHMethods.h"

// Definiing debugging variables
#define FPS_TIME 1 // Seconds
int Pause = 1; // Paused at start
std::clock_t last_time = clock();
unsigned int frames_rendered = 0;

// Defining program variables
char* windowTitle; // Pointer for changing fps counter in title each "FPS_TIME" seconds
float windowWidth = 800.0;
float windowHeight = 800.0;

// Mouse and pointer to solver
vector2f mousePos;
Solver* SPH;

// Defining start environment
void Start(int whSize)
{
	int particleCtr = 0;

	for (int x = 0; x < whSize; x++)
	{
		for (int y = 0; y < whSize+3; y++)
		{
			SPH->addParticle(vector2f(((x+3.0) * 2.0 + 100 / 4.f) * 0.01, (y+2.0) * 2.0 * 0.01));
			particleCtr++;
		}
	}

	std::cout << "Number of Particles: " << particleCtr << std::endl;
}

// Initialization
void Initialization()
{
	// Creating new Solver and calling setup method
	SPH = new Solver();
	SPH->initialize();

	// Calling Start Environment
	Start(20);

	// OpenGL stuff
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, SPH->worldSizeWidth, 0.0, SPH->worldSizeHeight);
	glutIgnoreKeyRepeat(false);

	// Allocating memory for title
	windowTitle = (char*)malloc(sizeof(char) * 50);

	// UI info
	std::cout << std::endl << "\tKeybinds: " << std::endl;
	std::cout << "Space   - Resume/Pause" << std::endl;
	std::cout << "LMB	- Heavy particle" << std::endl;
	std::cout << "RMB	- Ring of particles" << std::endl;
}

// Rendering particles
void Render()
{
	// Setting up color and size
	glColor3f(0.0f, 0.0f, 1.0f);
	glPointSize(10.f);

	// Drawing points
	for (int x = 0; x < SPH->currentParticles; x++)
	{
		glBegin(GL_POINTS);
		glVertex2d(SPH->particles[x]->position.x, SPH->particles[x]->position.y);
		glEnd();
	}
}

void Display()
{
	glViewport(0, 0, windowWidth, windowHeight);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 1.0f);

	// Checking for pause
	if (Pause == 0)
		SPH->update();


	Render();

	glutSwapBuffers();


	if ((clock() - last_time) / CLOCKS_PER_SEC >= FPS_TIME)
	{
		memset(windowTitle, 0, 50);
		sprintf(windowTitle, "Васильев К.В. / НИР / FPS: %d", frames_rendered / FPS_TIME);
		glutSetWindowTitle(windowTitle);

		frames_rendered = 0;
		last_time = clock();
	}
	frames_rendered++;
}

// Redisplays the window's normal plane
void Idle()
{
	glutPostRedisplay();
}

// Prevents reshaping of the window
void Reshape(int width, int height)
{
	glutReshapeWindow(windowWidth, windowHeight);
}

// Function to process keyboard
void KeyboardHotkeys(unsigned char hotkey, int x, int y)
{
	// Pausing
	if (hotkey == ' ') { Pause = 1 - Pause; }
}

// Function to process mouse moving
void MouseMoving(int x, int y)
{
	mousePos.x = x;
	mousePos.y = y;
}

void MouseInputs(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		SPH->addParticle(PARTICLE_MASS * 2, vector2f((mousePos.x / windowWidth) * SPH->worldSizeWidth, (((-1 * mousePos.y + windowHeight) / windowHeight)) * SPH->worldSizeHeight));
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		for (float i = 0; i < 360; i = i + 40)
		{
			SPH->addParticle(vector2f((mousePos.x / windowWidth) * SPH->worldSizeWidth + 0.02 * unitVecFromDeg(i).x, (((-1 * mousePos.y + windowHeight) / windowHeight)) * SPH->worldSizeHeight + 0.02 * unitVecFromDeg(i).y));
		}
	}
}

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
