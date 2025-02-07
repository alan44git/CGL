#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;

// Default center and radius of the circle
int cx = 300, cy = 300, R = 70;
bool flag = 1;

// Color struct
struct color {
    GLubyte r, g, b;
};

// Init function for initialization
void init() {
    glClearColor(1, 1, 1, 0);  // Set clear color to white
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer
    gluOrtho2D(0, 600, 0, 600);  // Set the orthographic projection
    glColor3f(0, 0, 0);  // Set default drawing color to black
}

// Plot the pixel (x, y)
void plotpixel(int x, int y) {
    glPointSize(1.5);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Plot the points using circle symmetry
void octant(int xc, int yc, int x, int y) {
    plotpixel(xc + x, yc + y); plotpixel(xc + y, yc + x);
    plotpixel(xc + y, yc - x); plotpixel(xc + x, yc - y);
    plotpixel(xc - x, yc - y); plotpixel(xc - y, yc - x);
    plotpixel(xc - y, yc + x); plotpixel(xc - x, yc + y);
}

// Midpoint circle drawing algorithm
void circleMP(int xc, int yc, int r) {
    int p = 1 - r, x = 0, y = r;
    while (x < y) {
        octant(xc, yc, x, y);
        x++;
        if (p > 0) {
            y--;
            p += 2 * (x - y) + 1;
        } else {
            p += 2 * x + 1;
        }
    }
}

// Convert degrees to radians
double ang(int q) {
    return (double)q * 3.142 / 180;
}

// Plot a pixel for filling
void plottofill(int x, int y, color c) {
    glPointSize(1.0);
    glColor3ub(c.r, c.g, c.b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Seed fill algorithm
void seedfill(int x, int y, color oc, color nc) {
    color c;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &c);
    if (c.r == oc.r && c.b == oc.b && c.g == oc.g) {
        plottofill(x, y, nc);
        seedfill(x + 1, y, oc, nc);
        seedfill(x - 1, y, oc, nc);
        seedfill(x, y + 1, oc, nc);
        seedfill(x, y - 1, oc, nc);
    }
}

// Draw all the circles
void drawcircles(int x, int y, int r) {
    circleMP(x, y, r);
    circleMP(x + 2 * r, y, r); circleMP(x - 2 * r, y, r);
    circleMP(x + 2 * r * cos(ang(60)), y + 2 * r * sin(ang(60)), r);
    circleMP(x - 2 * r * cos(ang(60)), y + 2 * r * sin(ang(60)), r);
    circleMP(x - 2 * r * cos(ang(60)), y - 2 * r * sin(ang(60)), r);
    circleMP(x + 2 * r * cos(ang(60)), y - 2 * r * sin(ang(60)), r);
    circleMP(x, y, 3 * r);
    circleMP(x, y, (float)2 * r - r * (0.20));
}

// Display function
void draw() {
    // Empty for now
}

// Clear the whole screen
void clear_screen() {
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
}

// Mouse click function
void mouseClick(int button, int state, int x, int y) {
    cout << "Mouse Clicked" << endl;

    // First point to get the xc, yc
    if (flag && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        cout << "Center Found" << endl;
        cx = x, cy = 600 - y;
        glPointSize(5.0);
        glColor3f(1, 0, 0);
        glBegin(GL_POINTS);
        glVertex2i(x, 600 - y);
        glEnd();
        glFlush();
        flag = 0;
    }
    // Find the radius of the circle
    else if (!flag && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        cout << "radius found" << endl;
        glColor3f(0, 0, 1);
        glPointSize(1.0);
        glBegin(GL_POINTS);
        glVertex2i(x, 600 - y);
        glEnd();
        glFlush();
        R = abs(x - cx);
        flag = 1;
    }
}

// Menu function
void menu(int ch) {
    color oc = {255, 255, 255};
    color nc = {255, 0, 0};
    switch (ch) {
        case 1:
            drawcircles(cx, cy, R);
            break;
        case 2:
            clear_screen();
            break;
        // case 3:
            // cout << "Fill the Centered Circle" << endl;
            // seedfill(cx + 5, cy, oc, nc);
            // break;
        case 3:
            exit(0);
            break;
    }
}

int main(int agrc, char **agrv) {
    glutInit(&agrc, agrv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Circle");
    init();
    glutDisplayFunc(draw);
    glutCreateMenu(menu);
    glutAddMenuEntry("Draw", 1);
    glutAddMenuEntry("Clear", 2);
    // glutAddMenuEntry("Color Fill", 3);
    glutAddMenuEntry("Exit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMouseFunc(mouseClick);
    glutMainLoop();
}
