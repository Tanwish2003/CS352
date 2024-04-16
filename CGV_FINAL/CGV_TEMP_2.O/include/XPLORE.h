#ifndef XPLORE_H
#define XPLORE_H

#include <GL/glut.h>

#include "ALL.h"

//-----------------------

void initializeXPLORE();

void displayXPLORE();
void specialXPLORE(int key, int x, int y);
void keyXPLORE(unsigned char key, int x, int y);
void timeXPLORE();
void mouseXPLORE(int button, int state, int x, int y);
void motionXPLORE(int x, int y);


//--------------------

#endif
