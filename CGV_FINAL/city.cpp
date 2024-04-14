#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <iostream>
using namespace std;

float cc[20][2];
static float angle = 0.0f; // Camera rotation angle

// Global variables
GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0}; // Light source position
bool isDaylight = true;                          // Whether it's currently daylight

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

void lighting(void)
{
    GLfloat light_ambient[] = {0.2, 0.2, 0.2, 1.0};  // Ambient light color
    GLfloat light_diffuse[] = {0.8, 0.7, 0.2, 1.0};  // Diffuse light color
    GLfloat light_specular[] = {0.9, 0.9, 0.8, 1.0}; // Specular light color

    glEnable(GL_LIGHTING); // Enable lighting
    glEnable(GL_LIGHT0);   // Enable light source 0

    glLightfv(GL_LIGHT0, GL_POSITION, light_position); // Set light position
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);   // Set ambient light color
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);   // Set diffuse light color
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); // Set specular light color
}

void drawSun(void)
{
    glPushMatrix();                                                        // Save current transformation
    glTranslatef(light_position[0], light_position[1], light_position[2]); // Move to sun position
    setMaterialColor(1.0, 1.0, 0.0);                                       // Set sun color to yellow
    glutSolidSphere(25.0, 50, 50);                                         // Reduce the radius of the sun sphere
    glPopMatrix();                                                         // Restore transformation
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    lighting(); // Enable lighting effects
}

void init(void);
void display(void);
void keyboard(unsigned char, int, int);
void resize(int, int);
void draw_star(float, float);
void house(float, float, float);
void apart(float, float, float);
void circle1(float);
void stand(float, float, float);
void time(int);
float h = 5, h1 = 6, d1 = 4, g = 1, g1 = 2;

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1100, 1100);
    glutInitWindowPosition(100, 10);
    glutCreateWindow("3D map");
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(resize);
    glutTimerFunc(100, time, 0); // Set the timer to call the time function in 100 milliseconds

    glutMainLoop();
    return 0;
}

void apart(float x, float y, float z)
{
    int i;
    int j;
    setMaterialColor(0.7, 0.7, 0.7);
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_POLYGON);
    glVertex3f(x, y, z + 0.5);
    glVertex3f(x + 45, y, z + 0.5);
    glVertex3f(x + 45, y + 100, z + 0.5);
    glVertex3f(x, y + 100, z + 0.5);
    glEnd();

    setMaterialColor(0.8, 0.8, 0.8);
    glColor3f(0.8, 0.8, 0.8);
    for (j = 0; j < 8; j++)
    {

        glPushMatrix();
        glTranslatef(0, -12 * j, 0);
        for (i = 0; i < 4; i++)
        {
            glPushMatrix();
            glTranslatef(11 * i, 0, 0);
            glBegin(GL_POLYGON);
            glVertex3f(x + 2, y + 98, z);
            glVertex3f(x + 10, y + 98, z);
            glVertex3f(x + 10, y + 88, z);
            glVertex3f(x + 2, y + 88, z);
            glEnd();
            glPopMatrix();
        }
        glPopMatrix();
    }

    setMaterialColor(0, 0, 0);
    glColor3f(0, 0, 0);
    for (j = 0; j < 8; j++)
    {

        glPushMatrix();
        glTranslatef(0, -12 * j, 0);
        for (i = 0; i < 4; i++)
        {
            glPushMatrix();
            glTranslatef(11 * i, 0, 0);
            glBegin(GL_LINE_LOOP);
            glVertex3f(x + 2, y + 98, z);
            glVertex3f(x + 10, y + 98, z);
            glVertex3f(x + 10, y + 88, z);
            glVertex3f(x + 2, y + 88, z);
            glEnd();
            glPopMatrix();
        }
        glPopMatrix();
    }

    setMaterialColor(0.6, 0.6, 0.6);
    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_POLYGON);
    glVertex3f(x, y, z + 45 - 0.5);
    glVertex3f(x + 45, y, z + 45 - 0.5);
    glVertex3f(x + 45, y + 100, z + 45 - 0.5);
    glVertex3f(x, y + 100, z + 45 - 0.5);
    glEnd();

    setMaterialColor(0.8, 0.8, 0.8);
    glColor3f(0.8, 0.8, 0.8);

    for (j = 0; j < 8; j++)
    {

        glPushMatrix();
        glTranslatef(0, -12 * j, 0);
        for (i = 0; i < 4; i++)
        {
            glPushMatrix();
            glTranslatef(11 * i, 0, 0);
            glBegin(GL_POLYGON);
            glVertex3f(x + 2, y + 98, z + 45);
            glVertex3f(x + 10, y + 98, z + 45);
            glVertex3f(x + 10, y + 88, z + 45);
            glVertex3f(x + 2, y + 88, z + 45);
            glEnd();
            glPopMatrix();
        }
        glPopMatrix();
    }

    setMaterialColor(0, 0, 0);
    glColor3f(0, 0, 0);

    for (j = 0; j < 8; j++)
    {

        glPushMatrix();
        glTranslatef(0, -12 * j, 0);
        for (i = 0; i < 4; i++)
        {
            glPushMatrix();
            glTranslatef(11 * i, 0, 0);
            glBegin(GL_LINE_LOOP);
            glVertex3f(x + 2, y + 98, z + 45);
            glVertex3f(x + 10, y + 98, z + 45);
            glVertex3f(x + 10, y + 88, z + 45);
            glVertex3f(x + 2, y + 88, z + 45);
            glEnd();
            glPopMatrix();
        }
        glPopMatrix();
    }

    setMaterialColor(0.6, 0.6, 0.6);
    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_POLYGON);
    glVertex3f(x + 0.5, y, z);
    glVertex3f(x + 0.5, y, z + 45);
    glVertex3f(x + 0.5, y + 100, z + 45);
    glVertex3f(x + 0.5, y + 100, z);
    glEnd();

    setMaterialColor(0.8, 0.8, 0.8);
    glColor3f(0.8, 0.8, 0.8);
    for (j = 0; j < 8; j++)
    {

        glPushMatrix();
        glTranslatef(0, -12 * j, 0);
        for (i = 0; i < 4; i++)
        {
            glPushMatrix();
            glTranslatef(0, 0, 11 * i);
            glBegin(GL_POLYGON);
            glVertex3f(x, y + 98, z + 2);
            glVertex3f(x, y + 98, z + 10);
            glVertex3f(x, y + 88, z + 10);
            glVertex3f(x, y + 88, z + 2);
            glEnd();
            glPopMatrix();
        }
        glPopMatrix();
    }

    setMaterialColor(0, 0, 0);
    glColor3f(0, 0, 0);
    for (j = 0; j < 8; j++)
    {

        glPushMatrix();
        glTranslatef(0, -12 * j, 0);
        for (i = 0; i < 4; i++)
        {
            glPushMatrix();
            glTranslatef(0, 0, 11 * i);
            glBegin(GL_LINE_LOOP);
            glVertex3f(x, y + 98, z + 2);
            glVertex3f(x, y + 98, z + 10);
            glVertex3f(x, y + 88, z + 10);
            glVertex3f(x, y + 88, z + 2);
            glEnd();
            glPopMatrix();
        }
        glPopMatrix();
    }

    setMaterialColor(0.6, 0.6, 0.6);
    glColor3f(0.6, 0.6, 0.6);

    glBegin(GL_POLYGON);
    glVertex3f(x + 45 - 0.5, y, z - 0.5);
    glVertex3f(x + 45 - 0.5, y, z + 45 - 0.5);
    glVertex3f(x + 45 - 0.5, y + 100, z + 45 - 0.5);
    glVertex3f(x + 45 - 0.5, y + 100, z - 0.5);
    glEnd();

    setMaterialColor(0.8, 0.8, 0.8);
    glColor3f(0.8, 0.8, 0.8);
    for (j = 0; j < 8; j++)
    {

        glPushMatrix();
        glTranslatef(0, -12 * j, 0);
        for (i = 0; i < 4; i++)
        {
            glPushMatrix();
            glTranslatef(0, 0, 11 * i);
            glBegin(GL_POLYGON);
            glVertex3f(x + 45, y + 98, z + 2);
            glVertex3f(x + 45, y + 98, z + 10);
            glVertex3f(x + 45, y + 88, z + 10);
            glVertex3f(x + 45, y + 88, z + 2);
            glEnd();
            glPopMatrix();
        }
        glPopMatrix();
    }

    setMaterialColor(0, 0, 0);
    glColor3f(0, 0, 0);
    for (j = 0; j < 8; j++)
    {

        glPushMatrix();
        glTranslatef(0, -12 * j, 0);
        for (i = 0; i < 4; i++)
        {
            glPushMatrix();
            glTranslatef(0, 0, 11 * i);
            glBegin(GL_LINE_LOOP);
            glVertex3f(x + 45, y + 98, z + 2);
            glVertex3f(x + 45, y + 98, z + 10);
            glVertex3f(x + 45, y + 88, z + 10);
            glVertex3f(x + 45, y + 88, z + 2);
            glEnd();
            glPopMatrix();
        }
        glPopMatrix();
    }

    setMaterialColor(0.5, 0.5, 0.5);
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex3f(x, y, z - 0.5);
    glVertex3f(x + 45, y, z - 0.5);
    glVertex3f(x + 45, y, z + 45 - 0.5);
    glVertex3f(x, y, z + 45 - 0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x, y + 100, z);
    glVertex3f(x + 45, y + 100, z);
    glVertex3f(x + 45, y + 100, z + 45);
    glVertex3f(x, y + 100, z + 45);
    glEnd();
}

void house(float x, float y, float z)
{
    setMaterialColor(0.01, 0.05, 0.3);
    glColor3f(0.01, 0.05, 0.3);
    glBegin(GL_POLYGON);
    glVertex3f(x, y, z);
    glVertex3f(x, y, z + 30);
    glVertex3f(x, y + 15, z + 30);
    glVertex3f(x, y + 15, z);
    glEnd();

    setMaterialColor(0.01, 0.05, 0.3);
    glColor3f(0.01, 0.05, 0.3);
    glBegin(GL_POLYGON);
    glVertex3f(x - 15, y, z);
    glVertex3f(x - 15, y + 15, z);
    glVertex3f(x - 15, y + 15, z + 30);
    glVertex3f(x - 15, y, z + 30);
    glEnd();

    setMaterialColor(0.01, 0.05, 0.3);
    glColor3f(0.01, 0.05, 0.3);
    glBegin(GL_POLYGON);
    glVertex3f(x, y, z + 30);
    glVertex3f(x - 15, y, z + 30);
    glVertex3f(x - 15, y + 15, z + 30);
    glVertex3f(x, y + 15, z + 30);
    glEnd();

    setMaterialColor(0.01, 0.05, 0.3);
    glColor3f(0.01, 0.05, 0.3);
    glBegin(GL_POLYGON);
    glVertex3f(x - 15, y, z);
    glVertex3f(x - 15, y + 15, z);
    glVertex3f(x, y + 15, z);
    glVertex3f(x, y, z);
    glEnd();

    setMaterialColor(0.01, 0.05, 0.3);
    glColor3f(0.01, 0.05, 1.5);
    glBegin(GL_POLYGON);
    glVertex3f(x - 15, y, z);
    glVertex3f(x, y, z);
    glVertex3f(x, y, z + 30);
    glVertex3f(x - 15, y, z + 30);
    glEnd();

    setMaterialColor(0.51, 0.015, 0.008);
    glColor3f(0.51, 0.015, 0.008);
    glBegin(GL_POLYGON);
    glVertex3f(x + 1.69 * 3, y + 3.5 * 3, z);
    glVertex3f(x - 2.5 * 3, y + 7.5 * 3, z);
    glVertex3f(x - 2.5 * 3, y + 7.5 * 3, z + 30);
    glVertex3f(x + 1.69 * 3, y + 3.5 * 3, z + 30);
    glEnd();

    setMaterialColor(0.51, 0.015, 0.008);
    glColor3f(0.51, 0.015, 0.008);
    glBegin(GL_POLYGON);
    glVertex3f(x - 6.69 * 3, y + 3.5 * 3, z);
    glVertex3f(x - 6.69 * 3, y + 3.5 * 3, z + 30);
    glVertex3f(x - 2.5 * 3, y + 7.5 * 3, z + 30);
    glVertex3f(x - 2.5 * 3, y + 7.5 * 3, z);
    glEnd();

    setMaterialColor(0.1, 0.015, 0.13);
    glColor3f(0.1, 0.015, 0.13);
    glBegin(GL_POLYGON);
    glVertex3f(x, y + 15, z);
    glVertex3f(x - 15, y + 5, z);
    glVertex3f(x - 2.5 * 3, y + 7.5 * 3, z);
    glEnd();

    setMaterialColor(0.1, 0.015, 0.13);
    glColor3f(0.1, 0.015, 0.13);
    glBegin(GL_POLYGON);
    glVertex3f(x, y + 15, z + 30);
    glVertex3f(x - 15, y + 15, z + 30);
    glVertex3f(x - 2.5 * 3, y + 7.5 * 3, z + 30);
    glEnd();
}

void house1()
{

    house(120, 0.1, 50);

    house(120, 0.1, 90);

    house(160, 0.1, 90);

    house(80, 0.1, 90);

    house(160, 0.1, 50);

    house(80, 0.1, 50);

    house(-130, 0.1, 120);

    house(-130, 0.1, 160);

    house(-90, 0.1, 120);

    house(-60, 0.1, 120);

    house(-90, 0.1, 160);

    stand(-10, 6, 130);
    stand(30, 6, 130);

    house(-60, 0.1, 160);
    apart(150, 0, -150);
    apart(80, 0, -90);

    apart(150, 0, -90);
    apart(150, 0, -30);

    apart(-150, 0, -30);
    apart(-150, 0, -110);

    apart(-150, 0, -180);
}
void circle1(float c[20][2])
{
    float x = 0, y = 03;
    int i;
    for (i = 0; i < 20; i++)
    {
        c[i][0] = x * cos((i + 1) * 36 * (3.142 / 360)) - y * sin((i + 1) * 36 * (3.142 / 360));
        c[i][1] = x * sin((i + 1) * 36 * (3.142 / 360)) + y * cos((i + 1) * 36 * (3.142 / 360));
    }

    for (i = 0; i < 19; i++)
    {
        glBegin(GL_POLYGON);
        glVertex3f(c[i][0], c[i][1], 0);
        glVertex3f(c[i][0], c[i][1], 40);
        glVertex3f(c[i + 1][0], c[i + 1][1], 40);
        glVertex3f(c[i + 1][0], c[i + 1][1], 0);
        glEnd();
    }

    glBegin(GL_POLYGON);
    glVertex3f(c[0][0], c[0][1], 0);
    glVertex3f(c[0][0], c[0][1], 40);
    glVertex3f(c[19][0], c[19][1], 40);
    glVertex3f(c[19][0], c[19][1], 0);
    glEnd();
}

// void init(void)
// {
// 		glClearColor(0.0,0.0,0.0,0.0);
// glEnable(GL_DEPTH_TEST);
// 	glMatrixMode(GL_MODELVIEW);
// }

void draw_star(GLfloat x, GLfloat y)
{
    setMaterialColor(1.0, 1.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + 1.5, y - 4);
    glVertex2f(x + 6.5, y - 5.5);
    glVertex2f(x + 2.5, y - 9);
    glVertex2f(x + 4.5, y - 14);
    glVertex2f(x, y - 11.5);
    glVertex2f(x - 4.5, y - 14);
    glVertex2f(x - 3, y - 9);
    glVertex2f(x - 6.5, y - 5.5);
    glVertex2f(x - 1.5, y - 5);
    glVertex2f(x, y);
    glEnd();
}

void stand(float x, float y, float z)
{
    setMaterialColor(1, 0.8, 0);
    glColor3f(1, 0.8, 0);
    glBegin(GL_POLYGON);
    glVertex3f(x, y, z);
    glVertex3f(x, y - h1, z + d1);
    glVertex3f(x + h, y - h1, z + d1);
    glVertex3f(x + h, y, z);
    glEnd();

    setMaterialColor(1, 0.5, 0);
    glColor3f(1, 0.5, 0);
    glBegin(GL_POLYGON);
    glVertex3f(x, y, z);
    glVertex3f(x + h, y, z);
    glVertex3f(x + h, y - h1, z - d1);
    glVertex3f(x, y - h1, z - d1);
    glEnd();

    setMaterialColor(0.6, 0.12, 0.4);
    glColor3f(0.6, 0.12, 0.4);

    glBegin(GL_POLYGON);
    glVertex3f(x, y - h1, z + d1);
    glVertex3f(x, y - h1 - 2, z + d1);
    glVertex3f(x + 1, y - h1 - 2, z + d1);
    glVertex3f(x + 1, y - h1, z + d1);
    glEnd();

    setMaterialColor(0.6, 0.12, 0.4);
    glColor3f(0.6, 0.12, 0.4);
    glBegin(GL_POLYGON);
    glVertex3f(x + h, y - h1, z + d1);
    glVertex3f(x + h, y - h1 - 2, z + d1);
    glVertex3f(x + h - 1, y - h1 - 2, z + d1);
    glVertex3f(x + h - 1, y - h1, z + d1);
    glEnd();

    setMaterialColor(0.6, 0.12, 0.4);
    glColor3f(0.6, 0.12, 0.4);

    glBegin(GL_POLYGON);
    glVertex3f(x, y - h1, z - d1);
    glVertex3f(x, y - h1 - 2, z - d1);
    glVertex3f(x + 1, y - h1 - 2, z - d1);
    glVertex3f(x + 1, y - h1, z - d1);
    glEnd();

    setMaterialColor(0.6, 0.12, 0.4);
    glColor3f(0.6, 0.12, 0.4);

    glBegin(GL_POLYGON);
    glVertex3f(x + h, y - h1, z - d1);
    glVertex3f(x + h, y - h1 - 2, z - d1);
    glVertex3f(x + h - 1, y - h1 - 2, z - d1);
    glVertex3f(x + h - 1, y - h1, z - d1);
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (isDaylight) // Only draw the sun during daylight
    {
        drawSun();
    }

    lighting(); // Set up lighting

    /* draw the floor */
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.6, 0.4);
    glVertex3f(-200.0, 0.0, -200.0);
    glColor3f(0.8, 0.6, 0.4);
    glVertex3f(-200.0, 0.0, 200.0);
    glColor3f(0.8, 0.6, 0.4);
    glVertex3f(200.0, 0.0, 200.0);
    glColor3f(0.8, 0.6, 0.4);
    glVertex3f(200.0, 0.0, -200.0);
    glEnd();
    glFlush();

    draw_star(20, 240);
    draw_star(180, 220);
    draw_star(-30, 280);
    draw_star(190, 280);
    draw_star(100, 220);
    draw_star(-230, 250);
    draw_star(-190, 210);
    draw_star(-88, 260);
    draw_star(88, 270);
    draw_star(-170, 280);

    setMaterialColor(0.3, 0.015, 0.13);
    glColor3f(0.3, 0.015, 0.13);
    glPushMatrix();
    glTranslatef(-15, 1, 50);
    glutSolidCube(7);
    glPopMatrix();

    setMaterialColor(0.3, 0.015, 0.13);
    glColor3f(0.3, 0.015, 0.13);
    glPushMatrix();
    glTranslatef(-15, 1, -40);
    glutSolidCube(7);
    glPopMatrix();

    setMaterialColor(0.3, 0.015, 0.13);
    glColor3f(0.3, 0.015, 0.13);
    glPushMatrix();
    glTranslatef(-15, 1, 20);
    glutSolidCube(7);
    glPopMatrix();

    setMaterialColor(0.3, 0.015, 0.13);
    glColor3f(0.3, 0.015, 0.13);
    glPushMatrix();
    glTranslatef(-15, 1, -10);
    glutSolidCube(7);
    glPopMatrix();

    setMaterialColor(0.3, 0.015, 0.13);
    glColor3f(0.3, 0.015, 0.13);
    glPushMatrix();
    glTranslatef(-15, 1, -80);
    glutSolidCube(7);
    glPopMatrix();

    setMaterialColor(0.3, 0.015, 0.13);
    glColor3f(0.3, 0.015, 0.13);
    glPushMatrix();
    glTranslatef(-15, 1, -120);
    glutSolidCube(7);
    glPopMatrix();

    setMaterialColor(0.3, 0.015, 0.13);
    glColor3f(0.3, 0.015, 0.13);
    glPushMatrix();
    glTranslatef(-15, 1, -160);
    glutSolidCube(7);
    glPopMatrix();

    setMaterialColor(0.015, 0.3, 0.13);
    glColor3f(0.015, 0.3, 0.13);
    glPushMatrix();
    glTranslatef(-15, 24, 50);
    glScalef(1.1, 2.3, 0.8);
    glutSolidSphere(10, 15, 6);
    glFlush();
    glPopMatrix();

    setMaterialColor(0.015, 0.3, 0.13);
    glColor3f(0.015, 0.3, 0.13);
    glPushMatrix();
    glTranslatef(-15, 24, -40);
    glScalef(1.1, 2.3, 0.8);
    glutSolidSphere(10, 15, 4);
    glFlush();
    glPopMatrix();

    setMaterialColor(0.015, 0.3, 0.13);
    glColor3f(0.015, 0.3, 0.13);
    glPushMatrix();
    glTranslatef(-15, 24, 20);
    glScalef(1.1, 2.3, 0.8);
    glutSolidSphere(10, 15, 4);
    glFlush();
    glPopMatrix();

    setMaterialColor(0.015, 0.3, 0.13);
    glColor3f(0.015, 0.3, 0.13);
    glPushMatrix();
    glTranslatef(-15, 24, -10);
    glScalef(1.1, 2.3, 0.8);
    glutSolidSphere(10, 15, 4);
    glFlush();
    glPopMatrix();

    setMaterialColor(0.015, 0.3, 0.13);
    glColor3f(0.015, 0.3, 0.13);
    glPushMatrix();
    glTranslatef(-15, 24, -80);
    glScalef(1.1, 2.3, 0.8);
    glutSolidSphere(10, 15, 4);
    glFlush();
    glPopMatrix();

    setMaterialColor(0.015, 0.3, 0.13);
    glColor3f(0.015, 0.3, 0.13);
    glPushMatrix();
    glTranslatef(-15, 24, -120);
    glScalef(1.1, 2.3, 0.8);
    glutSolidSphere(10, 15, 4);
    glFlush();
    glPopMatrix();

    setMaterialColor(0.015, 0.3, 0.13);
    glColor3f(0.015, 0.3, 0.13);
    glPushMatrix();
    glTranslatef(-15, 24, -160);
    glScalef(1.1, 2.3, 0.8);
    glutSolidSphere(10, 15, 4);
    glFlush();
    glPopMatrix();

    setMaterialColor(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(0, 0.01, -200); /* road */
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(0, 0.01, 200);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(18, 0.01, 200);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(18, 0.01, -200);
    glEnd();

    setMaterialColor(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(8.5, 0.02, -200); /* road */
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(8.5, 0.02, 200);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(9.5, 0.02, 200);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(9.5, 0.02, -200);
    glEnd();

    setMaterialColor(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(44, 0.01, -200); /* road */
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(44, 0.01, 160);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(54, 0.01, 160);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(54, 0.01, -200);
    glEnd();

    setMaterialColor(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(54, 0.01, -180); /* road */
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(54, 0.01, -160);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(200, 0.01, -160);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(200, 0.01, -180);
    glEnd();

    setMaterialColor(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(18, 0.01, 160); /* road */
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(18, 0.01, 170);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(200, 0.01, 170);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(200, 0.01, 160);
    glEnd();

    setMaterialColor(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-200, 0.01, 90); /* road */
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-200, 0.01, 100);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(0, 0.01, 100);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(0, 0.01, 90);
    glEnd();

    setMaterialColor(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-90, 0.01, -200); /* road */
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-90, 0.01, 90);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-80, 0.01, 90);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-80, 0.01, -200);
    glEnd();
    house1();
    glFlush();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{

    switch (key)
    {
    case 'a':
    case 'A':
        glTranslatef(5.0, 0.0, 0.0);
        break;
    case 'd':
    case 'D':
        glTranslatef(-5.0, 0.0, 0.0);
        break;
    case 'w':
    case 'W':
        glTranslatef(0.0, 0.0, 5.0);
        break;
    case 's':
    case 'S':
        glTranslatef(0.0, 0.0, -5.0);
        break;
    case 'q':
    case 'Q':
        glRotatef(-2, 1.0, 0.0, 0.0);
        break;
    case 'e':
    case 'E':
        glRotatef(2, 0.0, 1.0, 0.0);
        break;
    case 'r':
    case 'R':
        glRotatef(2, 0.0, 0.0, 1.0); // Rotate camera up
        break;
    case 'f':
    case 'F':
        glRotatef(-2, 0.0, 0.0, 1.0); // Rotate camera down
        break;
    case '+':
        glScalef(1.1, 1.1, 1.1); // Zoom in
        break;
    case '-':
        glScalef(0.9, 0.9, 0.9); // Zoom out
        break;
    case 'j':
    case 'J':
        glRotatef(-2, 1.0, 0.0, 0.0); // Rotate camera left around x-axis
        break;
    case 'l':
    case 'L':
        glRotatef(2, 1.0, 0.0, 0.0); // Rotate camera right around x-axis
        break;
    case 'i':
    case 'I':
        glRotatef(-2, 0.0, 1.0, 0.0); // Rotate camera up around y-axis
        break;
    case 'k':
    case 'K':
        glRotatef(2, 0.0, 1.0, 0.0); // Rotate camera down around y-axis
        break;
    case 'u':
    case 'U':
        glRotatef(-2, 0.0, 0.0, 1.0); // Rotate camera counterclockwise around z-axis
        break;
    case 'o':
    case 'O':
        glRotatef(2, 0.0, 0.0, 1.0); // Rotate camera clockwise around z-axis
        break;
    }

    glutPostRedisplay();
}

void time(int value)
{
    static int angle = 0;

    // Update the position of the light source to simulate the sun moving across the sky
    light_position[0] = 500 * cos(angle * M_PI / 180);      // Reduce the radius of the circle
    light_position[1] = 280 + 20 * sin(angle * M_PI / 180); // Oscillate between just above and below the surface
    light_position[2] = 500 * sin(angle * M_PI / 180);      // Reduce the radius of the circle

    // Switch between daylight and moonlight every 180 degrees
    isDaylight = (angle < 180);

    // Update the angle
    angle = (angle + 1) % 360;

    glutPostRedisplay();         // Force a redisplay
    glutTimerFunc(100, time, 0); // Set the timer to call this function again in 100 milliseconds
}
void resize(int width, int height)
{
    if (height == 0)
        height = 1;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(80.0, width / height, 1.0, 600.0);

    glTranslatef(0.0, -15.0, -320.0);

    glMatrixMode(GL_MODELVIEW);
}