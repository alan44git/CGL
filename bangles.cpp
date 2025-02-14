#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;

// Default center and radius of the circles
int cx = 400, cy = 400, R_outer = 150, R_inner = 100; // Outer and inner radii
int num_small_circles = 12;                             // Number of small circles
float small_circle_radius = 50;                          // Set the increased radius of small circles
bool flag = 1;

// Init function for initialization
void init()
{
    glClearColor(1, 1, 1, 0);     // Set clear color to white
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    gluOrtho2D(0, 800, 0, 800);   // Adjust projection to match the new window size
    glColor3f(0, 0, 0);           // Set default drawing color to black
}

// Plot the pixel (x, y)
void plotpixel(int x, int y)
{
    glPointSize(1.5);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Plot the points using circle symmetry
void octant(int xc, int yc, int x, int y)
{
    plotpixel(xc + x, yc + y);
    plotpixel(xc + y, yc + x);
    plotpixel(xc + y, yc - x);
    plotpixel(xc + x, yc - y);
    plotpixel(xc - x, yc - y);
    plotpixel(xc - y, yc - x);
    plotpixel(xc - y, yc + x);
    plotpixel(xc - x, yc + y);
}

// Midpoint circle drawing algorithm
void circleMP(int xc, int yc, int r)
{
    int p = 1 - r, x = 0, y = r;
    while (x < y)
    {
        octant(xc, yc, x, y);
        x++;
        if (p > 0)
        {
            y--;
            p += 2 * (x - y) + 1;
        }
        else
        {
            p += 2 * x + 1;
        }
    }
}

// Angle conversion in degrees
double ang(int q)
{
    return (double)q * 3.142 / 180;
}

// Draw outer circle, inner circle, and small circles around outer circle
void drawCirclesOnOuterCircle(int x, int y, int r_outer, int num_small_circles)
{
    // Place small circles along the circumference of the outer circle (outside the circle)
    for (int i = 0; i < num_small_circles; i++)
    {
        double angle = ang(i * (360 / num_small_circles)); // Angle for each small circle
        int small_x = x + (r_outer + small_circle_radius) * cos(angle);  // X-coordinate of the small circle
        int small_y = y + (r_outer + small_circle_radius) * sin(angle);  // Y-coordinate of the small circle

        // Draw the small circle at the calculated position
        circleMP(small_x, small_y, small_circle_radius);
    }

    // Draw the outer and inner circles
    circleMP(x, y, r_outer);
    circleMP(x, y, R_inner);
}

// Clear the whole screen
void clear_screen()
{
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
}

// Mouse click function
void mouseClick(int button, int state, int x, int y)
{
    cout << "Mouse Clicked" << endl;

    // First point to get the xc, yc
    if (flag && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        cout << "Center Found" << endl;
        cx = x, cy = 800 - y; // Updated for new window size
        glPointSize(5.0);
        glColor3f(0, 0, 1);
        glBegin(GL_POINTS);
        glVertex2i(x, 800 - y); // Updated for new window size
        glEnd();
        glFlush();
        flag = 0;
    }
    // Find the radius of the circle
    else if (!flag && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        cout << "Ohhho !!, I got a radius" << endl;
        glColor3f(0, 0, 1);
        glPointSize(1.0);
        glBegin(GL_POINTS);
        glVertex2i(x, 800 - y); // Updated for new window size
        glEnd();
        glFlush();
        R_outer = abs(x - cx);
        flag = 1;
    }
}

// Menu function
void menu(int ch)
{
    switch (ch)
    {
    case 1:
        drawCirclesOnOuterCircle(cx, cy, R_outer, num_small_circles); // Call function to draw the bangle
        break;
    case 2:
        clear_screen();
        break;
    case 3:
        exit(0);
        break;
    }
}

int main(int agrc, char **agrv)
{
    glutInit(&agrc, agrv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 800); // Increased window size to 800x800
    glutCreateWindow("Bangle with Larger Small Circles (Outside)");
    init();

    glutCreateMenu(menu);
    glutAddMenuEntry("Draw Bangle", 1);
    glutAddMenuEntry("Clear", 2);
    glutAddMenuEntry("Exit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMouseFunc(mouseClick);
    glutMainLoop();
}

