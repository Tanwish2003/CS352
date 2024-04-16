#include <stdio.h>
#include <math.h>
#include <iomanip>
#include <GL/glut.h>
#include <GL/freeglut.h> 
#include <iostream>

#include "../include/MENU.h"
#include "../include/XPLORE.h"
#include "../include/CONTROLS.h"

using namespace std;
// Global variables
bool isDaylight = true;				 // True if it's daylight, false if it's moonlight
float light_position[3] = {0, 0, 0}; // Position of the light source

void setMaterialColor(float r, float g, float b)
{
	GLfloat material_ambient[] = {r * 0.2f, g * 0.2f, b * 0.2f, 1.0f};
	GLfloat material_diffuse[] = {r * 0.8f, g * 0.8f, b * 0.8f, 1.0f};
	GLfloat material_specular[] = {r * 0.9f, g * 0.9f, b * 0.9f, 1.0f};
	GLfloat material_shininess[] = {50.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
}

void display()
{

	// Set the color of the light source based on whether it's daylight or moonlight
	GLfloat light_color[4] = {isDaylight ? 1.0f : 1.0f, isDaylight ? 0.9f : 1.0f, isDaylight ? 0.7f : 1.0f, 1.0f};

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);

	glEnable(GL_LIGHTING); // Enable lighting calculations
	glEnable(GL_LIGHT0);   // Enable light source GL_LIGHT0

	glEnable(GL_COLOR_MATERIAL);					   // Enable color material tracking
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); // Set material properties to follow glColor commands
	switch (state)
	{
	case 0:
		displayMENU();
		break;
	case 1:
		displayXPLORE();
		break;
	case 2:
		displayXPLORE();
		break;
	case 3:
		displayXPLORE();
		break;
	case 4:
		displayCONTROLS();
		break;
	}
	glutPostRedisplay();
}

void key(unsigned char key, int x, int y)
{
	switch (state)
	{
	case 0:
		keyMENU(key, x, y);
		break;
	case 1:
		keyXPLORE(key, x, y);
		break;
	case 2:
		keyXPLORE(key, x, y);
		break;
	case 3:
		keyXPLORE(key, x, y);
		break;
	case 4:
		keyXPLORE(key, x, y);
		break;
	case 5:
		keyXPLORE(key, x, y);
		break;
	}

	switch (key)
	{
	case 'l': // Switch to daylight
		isDaylight = true;
		break;
	case 'k': // Switch to moonlight
		isDaylight = false;
		break;
	case '1': // Set the light source to position 1 (above the city)
		light_position[0] = -2000;
		light_position[1] = 2000;
		light_position[2] = 2000;
		break;
	case '2': // Set the light source to position 2 (top-right corner of the city)
		light_position[0] = 2000;
		light_position[1] = 2000;
		light_position[2] = 0;
		break;
	case '3': // Set the light source to position 3 (bottom-right corner of the city)
		light_position[0] = 2000;
		light_position[1] = 0;
		light_position[2] = 2000;
		break;
	case '4': // Set the light source to position 4 (bottom-left corner of the city)
		light_position[0] = 0;
		light_position[1] = 2000;
		light_position[2] = 2000;
		break;
	case '5': // Set the light source to position 5 (top-left corner of the city)
		light_position[0] = 0;
		light_position[1] = -2000;
		light_position[2] = 0;
		break;
	case '6': // Set the light source to position 6 (center of the city)
		light_position[0] = 2000;
		light_position[1] = -2000;
		light_position[2] = 2000;
		break;
	}
	glutPostRedisplay(); // Force a redisplay
}
void special(int key, int x, int y)
{
	switch (state)
	{
	case 0:
		specialMENU(key, x, y);
		break;
	case 1:
		specialXPLORE(key, x, y);
		break;
	case 2:
		specialXPLORE(key, x, y);
		break;
	case 3:
		specialXPLORE(key, x, y);
		break;
	}

	switch (key)
	{
	case GLUT_KEY_UP: // Move the light source up
		light_position[1] += 100;
		light_position[2] += 100;
		break;
	case GLUT_KEY_DOWN: // Move the light source down
		light_position[1] -= 100;
		light_position[2] -= 100;
		break;
	case GLUT_KEY_LEFT: // Move the light source left
		light_position[0] -= 100;
		light_position[2] -= 100;
		break;
	case GLUT_KEY_RIGHT: // Move the light source right
		light_position[0] += 100;
		light_position[2] += 100;
		break;
	}
	glutPostRedisplay(); // Force a redisplay
}

void time(int value)
{
	switch (state)
	{
	case 1:
		timeXPLORE();
		break;
	case 2:
		timeXPLORE();
		break;
	case 3:
		timeXPLORE();
		break;
	}

	static int angle = 0;

	// Update the position of the light source to simulate the sun moving across the sky
	light_position[0] = 2000 * cos(angle * M_PI / 180);
	light_position[1] = 2000 * sin(angle * M_PI / 180);
	light_position[2] = 2000 * sin(angle * M_PI / 180);

	// Switch between daylight and moonlight every 180 degrees
	isDaylight = (angle < 180);

	// Update the angle
	angle = (angle + 1) % 360;

	// glutTimerFunc(100, time, 0); // Set the timer to call this function again in 100 milliseconds

	glutPostRedisplay(); // Force a redisplay
}

void reshape(int w, int h)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // black background

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv)
{
	printf("hello world\n");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);
	glutCreateWindow("city");

	

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutSpecialFunc(special);
	glutMouseFunc(mouseXPLORE);
	glutMotionFunc(motionXPLORE);
	glutTimerFunc(0, time, 0);

	glutMainLoop();

	return 0;
}
