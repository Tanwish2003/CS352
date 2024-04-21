#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <iostream>
#include <soil2/SOIL2.h> // Include the SOIL2 header file
using namespace std;

float cc[20][2];
static float angle = 0.0f; // Camera rotation angle

// Global variables
GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0}; // Light source position
bool isDaylight = true;                          // Whether it's currently daylight

// Function to set the material color for OpenGL rendering
void setMaterialColor(float r, float g, float b)
{
    // Create an array for the ambient component of the material, scaled by 0.2
    GLfloat material_ambient[] = {r * 0.2f, g * 0.2f, b * 0.2f, 1.0f};

    // Create an array for the diffuse component of the material, scaled by 0.8
    GLfloat material_diffuse[] = {r * 0.8f, g * 0.8f, b * 0.8f, 1.0f};

    // Create an array for the specular component of the material, scaled by 0.9
    GLfloat material_specular[] = {r * 0.9f, g * 0.9f, b * 0.9f, 1.0f};

    // Create an array for the shininess of the material, set to 50
    GLfloat material_shininess[] = {50.0f};

    // Set the ambient material parameter for the front face of polygons
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);

    // Set the diffuse material parameter for the front face of polygons
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);

    // Set the specular material parameter for the front face of polygons
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);

    // Set the shininess material parameter for the front face of polygons
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

// Declare a texture
GLuint texture;

// Declare two more textures
GLuint texture1, texture2;

// Function to load a texture from a file
void loadTexture(const char *filename, GLuint *texture)
{
    // Declare variables for the width and height of the image
    int width, height;

    // Load the image from the file
    unsigned char *image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);

    // If the image failed to load, print an error message and return
    if (image == NULL)
    {
        fprintf(stderr, "Failed to load image file: %s\n", SOIL_last_result());
        return;
    }

    // Generate a texture ID
    glGenTextures(1, texture);

    // Bind the texture to a texture target
    glBindTexture(GL_TEXTURE_2D, *texture);

    // Specify a two-dimensional texture image
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    // Set the texture minifying function to linear interpolation
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Set the texture magnification function to linear interpolation
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Free the image data
    SOIL_free_image_data(image);

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

// Function to load multiple textures
void loadTextures()
{
    // Load the first texture
    loadTexture("hoarding.png", &texture1);

    // Load the second texture
    loadTexture("hoarding3.png", &texture2);
}

// Function to draw a billboard at a specific location with a given width and height
void drawBillboard(float x, float y, float z, float width, float height)
{
    // Set the color to a specific shade of grey
    glColor3f(0.741, 0.718, 0.420);

    // Begin drawing quadrilaterals
    glBegin(GL_QUADS);

    // Draw the drawStand of the billboard as a quadrilateral
    glVertex3f(x + width / 2 - 2, 0, z);
    glVertex3f(x + width / 2 + 2, 0, z);
    glVertex3f(x + width / 2 + 2, y, z);
    glVertex3f(x + width / 2 - 2, y, z);

    // End drawing
    glEnd();

    // Enable 2D texturing
    glEnable(GL_TEXTURE_2D);

    // Get the current time since the start of the program
    unsigned int currentTime = glutGet(GLUT_ELAPSED_TIME);

    // Determine which texture to use based on the current time
    int textureIndex = (currentTime / 4000) % 2;

    // Bind the appropriate texture
    if (textureIndex == 0)
        glBindTexture(GL_TEXTURE_2D, texture1); // Bind the first texture
    else
        glBindTexture(GL_TEXTURE_2D, texture2); // Bind the second texture

    // Begin drawing quadrilaterals
    glBegin(GL_QUADS);

    // Draw the billboard as a textured quadrilateral
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x, y, z);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x + width, y, z);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x + width, y + height, z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x, y + height, z);

    // End drawing
    glEnd();

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // Disable 2D texturing
    glDisable(GL_TEXTURE_2D);
}
// Variables to store the last known mouse position
int lastMouseX = 0;
int lastMouseY = 0;

// Variable to track if the mouse button is pressed
bool isMousePressed = false;

// Function to handle mouse button events
void mouseXPLORE(int button, int state, int x, int y)
{
    // If the left mouse button is pressed down
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Store the current mouse position and set isMousePressed to true
        lastMouseX = x;
        lastMouseY = y;
        isMousePressed = true;
    }
    // If the left mouse button is released
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        // Set isMousePressed to false
        isMousePressed = false;
    }
}

// Function to handle mouse motion events
void motionXPLORE(int x, int y)
{
    // If the mouse button is pressed
    if (isMousePressed)
    {
        // Calculate the change in mouse position
        int deltaX = x - lastMouseX;
        int deltaY = y - lastMouseY;

        // Rotate the camera based on the change in mouse position
        glRotatef(-deltaX * 0.01, 1.0, 0.0, 0.0);
        glRotatef(-deltaY * 0.01, 0.0, 1.0, 0.0);
    }
    // Redraw the scene
    glutPostRedisplay();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    lighting(); // Enable lighting effects
}

float h = 5, h1 = 6, d1 = 4, g = 1, g1 = 2;

void drawHouse(float posX, float posY, float posZ)
{
    // Set the color to dark blue
    setMaterialColor(0.01, 0.05, 0.3);
    glColor3f(0.01, 0.05, 0.3);

    // Draw the front wall of the drawHouse
    glBegin(GL_POLYGON);
    glVertex3f(posX, posY, posZ);
    glVertex3f(posX, posY, posZ + 30);
    glVertex3f(posX, posY + 15, posZ + 30);
    glVertex3f(posX, posY + 15, posZ);
    glEnd();

    // Draw the left wall of the drawHouse
    glBegin(GL_POLYGON);
    glVertex3f(posX - 15, posY, posZ);
    glVertex3f(posX - 15, posY + 15, posZ);
    glVertex3f(posX - 15, posY + 15, posZ + 30);
    glVertex3f(posX - 15, posY, posZ + 30);
    glEnd();

    // Draw the back wall of the drawHouse
    glBegin(GL_POLYGON);
    glVertex3f(posX, posY, posZ + 30);
    glVertex3f(posX - 15, posY, posZ + 30);
    glVertex3f(posX - 15, posY + 15, posZ + 30);
    glVertex3f(posX, posY + 15, posZ + 30);
    glEnd();

    // Draw the right wall of the drawHouse
    glBegin(GL_POLYGON);
    glVertex3f(posX - 15, posY, posZ);
    glVertex3f(posX - 15, posY + 15, posZ);
    glVertex3f(posX, posY + 15, posZ);
    glVertex3f(posX, posY, posZ);
    glEnd();

    // Draw the bottom of the drawHouse
    glBegin(GL_POLYGON);
    glVertex3f(posX - 15, posY, posZ);
    glVertex3f(posX, posY, posZ);
    glVertex3f(posX, posY, posZ + 30);
    glVertex3f(posX - 15, posY, posZ + 30);
    glEnd();

    // Set the color to red
    setMaterialColor(0.51, 0.015, 0.008);
    glColor3f(0.51, 0.015, 0.008);

    // Draw the left side of the roof
    glBegin(GL_POLYGON);
    glVertex3f(posX + 1.69 * 3, posY + 3.5 * 3, posZ);
    glVertex3f(posX - 2.5 * 3, posY + 7.5 * 3, posZ);
    glVertex3f(posX - 2.5 * 3, posY + 7.5 * 3, posZ + 30);
    glVertex3f(posX + 1.69 * 3, posY + 3.5 * 3, posZ + 30);
    glEnd();

    // Draw the right side of the roof
    glBegin(GL_POLYGON);
    glVertex3f(posX - 6.69 * 3, posY + 3.5 * 3, posZ);
    glVertex3f(posX - 6.69 * 3, posY + 3.5 * 3, posZ + 30);
    glVertex3f(posX - 2.5 * 3, posY + 7.5 * 3, posZ + 30);
    glVertex3f(posX - 2.5 * 3, posY + 7.5 * 3, posZ);
    glEnd();

    // Set the color to purple
    setMaterialColor(0.1, 0.015, 0.13);
    glColor3f(0.1, 0.015, 0.13);

    // Draw the front side of the roof
    glBegin(GL_POLYGON);
    glVertex3f(posX, posY + 15, posZ);
    glVertex3f(posX - 15, posY + 5, posZ);
    glVertex3f(posX - 2.5 * 3, posY + 7.5 * 3, posZ);
    glEnd();

    // Draw the back side of the roof
    glBegin(GL_POLYGON);
    glVertex3f(posX, posY + 15, posZ + 30);
    glVertex3f(posX - 15, posY + 15, posZ + 30);
    glVertex3f(posX - 2.5 * 3, posY + 7.5 * 3, posZ + 30);
    glEnd();
}

void drawStar(GLfloat starCenterX, GLfloat starCenterY)
{
    // Set the color to white
    setMaterialColor(1.0, 1.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);

    // Start drawing a polygon
    glBegin(GL_POLYGON);

    // Define the vertices of the star
    glVertex2f(starCenterX, starCenterY);
    glVertex2f(starCenterX + 1.5, starCenterY - 4);
    glVertex2f(starCenterX + 6.5, starCenterY - 5.5);
    glVertex2f(starCenterX + 2.5, starCenterY - 9);
    glVertex2f(starCenterX + 4.5, starCenterY - 14);
    glVertex2f(starCenterX, starCenterY - 11.5);
    glVertex2f(starCenterX - 4.5, starCenterY - 14);
    glVertex2f(starCenterX - 3, starCenterY - 9);
    glVertex2f(starCenterX - 6.5, starCenterY - 5.5);
    glVertex2f(starCenterX - 1.5, starCenterY - 5);
    glVertex2f(starCenterX, starCenterY);

    // End drawing the polygon
    glEnd();
}

void draw_window(float x, float y, float z)
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

void drawStand(float posX, float posY, float posZ)
{
    // Set the color to yellow
    setMaterialColor(1, 0.8, 0);
    glColor3f(1, 0.8, 0);

    // Draw the front face of the drawStand
    glBegin(GL_POLYGON);
    glVertex3f(posX, posY, posZ);
    glVertex3f(posX, posY - h1, posZ + d1);
    glVertex3f(posX + h, posY - h1, posZ + d1);
    glVertex3f(posX + h, posY, posZ);
    glEnd();

    // Set the color to orange
    setMaterialColor(1, 0.5, 0);
    glColor3f(1, 0.5, 0);

    // Draw the back face of the drawStand
    glBegin(GL_POLYGON);
    glVertex3f(posX, posY, posZ);
    glVertex3f(posX + h, posY, posZ);
    glVertex3f(posX + h, posY - h1, posZ - d1);
    glVertex3f(posX, posY - h1, posZ - d1);
    glEnd();

    // Set the color to purple
    setMaterialColor(0.6, 0.12, 0.4);
    glColor3f(0.6, 0.12, 0.4);

    // Draw the left side of the drawStand
    glBegin(GL_POLYGON);
    glVertex3f(posX, posY - h1, posZ + d1);
    glVertex3f(posX, posY - h1 - 2, posZ + d1);
    glVertex3f(posX + 1, posY - h1 - 2, posZ + d1);
    glVertex3f(posX + 1, posY - h1, posZ + d1);
    glEnd();

    // Draw the right side of the drawStand
    glBegin(GL_POLYGON);
    glVertex3f(posX + h, posY - h1, posZ + d1);
    glVertex3f(posX + h, posY - h1 - 2, posZ + d1);
    glVertex3f(posX + h - 1, posY - h1 - 2, posZ + d1);
    glVertex3f(posX + h - 1, posY - h1, posZ + d1);
    glEnd();

    // Draw the bottom side of the drawStand
    glBegin(GL_POLYGON);
    glVertex3f(posX, posY - h1, posZ - d1);
    glVertex3f(posX, posY - h1 - 2, posZ - d1);
    glVertex3f(posX + 1, posY - h1 - 2, posZ - d1);
    glVertex3f(posX + 1, posY - h1, posZ - d1);
    glEnd();

    // Draw the top side of the drawStand
    glBegin(GL_POLYGON);
    glVertex3f(posX + h, posY - h1, posZ - d1);
    glVertex3f(posX + h, posY - h1 - 2, posZ - d1);
    glVertex3f(posX + h - 1, posY - h1 - 2, posZ - d1);
    glVertex3f(posX + h - 1, posY - h1, posZ - d1);
    glEnd();
}

void DRAW()
{

    drawHouse(120, 0.1, 50);

    drawHouse(120, 0.1, 90);

    drawHouse(160, 0.1, 90);

    drawHouse(80, 0.1, 90);

    drawHouse(160, 0.1, 50);

    drawHouse(80, 0.1, 50);

    drawHouse(-130, 0.1, 120);

    drawHouse(-130, 0.1, 160);

    drawHouse(-90, 0.1, 120);

    drawHouse(-60, 0.1, 120);

    drawHouse(-90, 0.1, 160);

    drawStand(-10, 6, 130);
    drawStand(30, 6, 130);

    drawHouse(-60, 0.1, 160);
    draw_window(150, 0, -150);
    draw_window(80, 0, -90);

    draw_window(150, 0, -90);
    draw_window(150, 0, -30);

    draw_window(-150, 0, -30);
    draw_window(-150, 0, -110);

    draw_window(-150, 0, -180);
}

void drawFloor()
{
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
}

void drawStars()
{
    drawStar(20, 240);
    drawStar(180, 220);
    drawStar(-30, 280);
    drawStar(190, 280);
    drawStar(100, 220);
    drawStar(-230, 250);
    drawStar(-190, 210);
    drawStar(-88, 260);
    drawStar(88, 270);
    drawStar(-170, 280);
}

void drawCubes()
{
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
}

void drawSpheres()
{

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
}

void drawRoads()
{
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
}

void deleteTextures()
{
    glDeleteTextures(1, &texture1);
    glDeleteTextures(1, &texture2);
}
void display(void)
{
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the sun if it's daylight
    if (isDaylight)
    {
        drawSun();
    }

    // Set up lighting
    lighting();

    // Load textures
    loadTextures();

    // Draw the billboard
    drawBillboard(-5, 25, 200, 20, 10);

    // Draw the floor
    drawFloor();

    // Draw stars
    drawStars();

    // Draw cubes
    drawCubes();

    // Draw spheres
    drawSpheres();

    // Draw roads
    drawRoads();

    // Draw the house
    DRAW();

    // Delete textures
    deleteTextures();

    // Flush the OpenGL commands and swap the buffers
    glFlush();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    // Define the translation and rotation amounts
    float translateAmount = 5.0;
    float rotateAmount = 2.0;
    float scaleAmount = 0.1;

    switch (key)
    {
    // Move left
    case 'a':
    case 'A':
        glTranslatef(translateAmount, 0.0, 0.0);
        break;

    // Move right
    case 'd':
    case 'D':
        glTranslatef(-translateAmount, 0.0, 0.0);
        break;

    // Move forward
    case 'w':
    case 'W':
        glTranslatef(0.0, 0.0, translateAmount);
        break;

    // Move backward
    case 's':
    case 'S':
        glTranslatef(0.0, 0.0, -translateAmount);
        break;

    // Rotate left around x-axis
    case 'q':
    case 'Q':
        glRotatef(-rotateAmount, 1.0, 0.0, 0.0);
        break;

    // Rotate right around y-axis
    case 'e':
    case 'E':
        glRotatef(rotateAmount, 0.0, 1.0, 0.0);
        break;

    // Rotate up around z-axis
    case 'r':
    case 'R':
        glRotatef(rotateAmount, 0.0, 0.0, 1.0);
        break;

    // Rotate down around z-axis
    case 'f':
    case 'F':
        glRotatef(-rotateAmount, 0.0, 0.0, 1.0);
        break;

    // Zoom in
    case '+':
        glScalef(1.0 + scaleAmount, 1.0 + scaleAmount, 1.0 + scaleAmount);
        break;

    // Zoom out
    case '-':
        glScalef(1.0 - scaleAmount, 1.0 - scaleAmount, 1.0 - scaleAmount);
        break;

    // Additional rotation controls
    case 'j':
    case 'J':
        glRotatef(-rotateAmount, 1.0, 0.0, 0.0);
        break;
    case 'l':
    case 'L':
        glRotatef(rotateAmount, 1.0, 0.0, 0.0);
        break;
    case 'i':
    case 'I':
        glRotatef(-rotateAmount, 0.0, 1.0, 0.0);
        break;
    case 'k':
    case 'K':
        glRotatef(rotateAmount, 0.0, 1.0, 0.0);
        break;
    case 'u':
    case 'U':
        glRotatef(-rotateAmount, 0.0, 0.0, 1.0);
        break;
    case 'o':
    case 'O':
        glRotatef(rotateAmount, 0.0, 0.0, 1.0);
        break;
    }

    // Redraw the scene
    glutPostRedisplay();
}
void resize(int width, int height)
{
    // Prevent division by zero
    if (height == 0)
        height = 1;

    // Set the projection matrix as the current matrix
    glMatrixMode(GL_PROJECTION);

    // Reset the projection matrix
    glLoadIdentity();

    // Set up a perspective projection
    gluPerspective(80.0, static_cast<float>(width) / height, 1.0, 600.0);

    // Move the camera back
    glTranslatef(0.0, -15.0, -320.0);

    // Set the modelview matrix as the current matrix
    glMatrixMode(GL_MODELVIEW);
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

// The main function
int main(int argc, char **argv)
{
    // Initialize the GLUT library
    glutInit(&argc, argv);

    // Set the initial display mode (double buffering and RGB color)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Set the initial window size
    glutInitWindowSize(1100, 1100);

    // Set the initial window position
    glutInitWindowPosition(100, 10);

    // Create the window with a title
    glutCreateWindow("3D CITY- METROPOLIS");

    // Call the initialization function
    init();

    // Set the display callback for the window
    glutDisplayFunc(display);

    // Set the keyboard callback for the window
    glutKeyboardFunc(keyboard);

    // Set the mouse callback for the window
    glutMouseFunc(mouseXPLORE);

    // Set the motion callback for the window
    glutMotionFunc(motionXPLORE);

    // Set the reshape callback for the window
    glutReshapeFunc(resize);

    // Set a timer to call the 'time' function after 100 milliseconds
    glutTimerFunc(100, time, 0);

    // Enter the GLUT event processing loop
    glutMainLoop();

    // Return 0 to indicate successful execution
    return 0;
}
