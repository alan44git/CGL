#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;

int cx = 300, cy = 300, R = 70;
bool flag = 1;

// Color struct
struct color {
    GLubyte r, g, b;
};

void init() {
    glClearColor(1, 1, 1, 0);  
    glClear(GL_COLOR_BUFFER_BIT);  
    gluOrtho2D(0, 600, 0, 600);  
    glColor3f(0, 0, 0); 
}

void plotpixel(int x, int y) {
    glPointSize(1.5);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void octant(int xc, int yc, int x, int y) {
    // Dotted pattern: We will only plot every 3rd point
    if ((x + y) % 3 == 0) {
        plotpixel(xc + x, yc + y); 
        plotpixel(xc + y, yc + x);
        plotpixel(xc + y, yc - x); 
        plotpixel(xc + x, yc - y);
        plotpixel(xc - x, yc - y); 
        plotpixel(xc - y, yc - x);
        plotpixel(xc - y, yc + x); 
        plotpixel(xc - x, yc + y);
    }
}

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

double ang(int q) {
    return (double)q * 3.142 / 180;
}

void drawcircles(int x, int y, int r) {
    circleMP(x, y, r);
    circleMP(x + 2 * r, y, r); 
    circleMP(x - 2 * r, y, r);
    circleMP(x + 2 * r * cos(ang(60)), y + 2 * r * sin(ang(60)), r);
    circleMP(x - 2 * r * cos(ang(60)), y + 2 * r * sin(ang(60)), r);
    circleMP(x - 2 * r * cos(ang(60)), y - 2 * r * sin(ang(60)), r);
    circleMP(x + 2 * r * cos(ang(60)), y - 2 * r * sin(ang(60)), r);
    circleMP(x, y, 3 * r);
    circleMP(x, y, (float)2 * r - r * (0.20));
}

void draw() {
    // No specific rendering here for now
}

void clear_screen() {
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void mouseClick(int button, int state, int x, int y) {
    cout << "Mouse Clicked" << endl;

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

    else if (!flag && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        cout << "Ohhho !!, I got a radius" << endl;
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

void menu(int ch) {
    switch (ch) {
        case 1:
            drawcircles(cx, cy, R);
            break;
        case 2:
            clear_screen();
            break;
        case 4:
            exit(0);
            break;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Circle");
    init();
    glutDisplayFunc(draw);
    glutCreateMenu(menu);
    glutAddMenuEntry("Draw", 1);
    glutAddMenuEntry("Clear", 2);
    glutAddMenuEntry("Exit", 4); 
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMouseFunc(mouseClick);
    glutMainLoop();
}

