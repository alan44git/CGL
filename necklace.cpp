#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>

void plotCirclePoints(int x_center, int y_center, int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x_center + x, y_center + y);
    glVertex2i(x_center - x, y_center + y);
    glVertex2i(x_center + x, y_center - y);
    glVertex2i(x_center - x, y_center - y);
    glVertex2i(x_center + y, y_center + x);
    glVertex2i(x_center - y, y_center + x);
    glVertex2i(x_center + y, y_center - x);
    glVertex2i(x_center - y, y_center - x);
    glEnd();
}

void bresenhamCircle(int x_center, int y_center, int radius) {
    int x = 0;
    int y = radius;
    int p = 3 - 2 * radius; 

    plotCirclePoints(x_center, y_center, x, y);

    while (x < y) {
        if (p < 0) {
            p = p + 4 * x + 6;
        } else {
            p = p + 4 * (x - y) + 10;
            y--;
        }
        x++;

        plotCirclePoints(x_center, y_center, x, y);
    }
}

void renderFunction() {
    glClear(GL_COLOR_BUFFER_BIT);  
    bresenhamCircle(0, -50, 50);

    bresenhamCircle(50, 0, 20);    
    bresenhamCircle(-50, 0, 20);    
    
    bresenhamCircle(75, 30, 20);    
    bresenhamCircle(-75, 30, 20);    
    
    bresenhamCircle(100, 60, 20);    
    bresenhamCircle(-100, 60, 20);    

    bresenhamCircle(125, 90, 20);    
    bresenhamCircle(-125, 90, 20);    

    bresenhamCircle(145, 125, 20);    
    bresenhamCircle(-145, 125, 20); 

    //beads
    bresenhamCircle(15, -115, 15);    
    bresenhamCircle(-15, -115, 15); 


    //bresenhamCircle(35, -135, 15);    
    //bresenhamCircle(-35, -135, 15); 

    // bresenhamCircle(145, 125, 20);    
    // bresenhamCircle(-145, 125, 20); 

    glFlush();                    
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham's Circle Drawing Algorithm");
    gluOrtho2D(-200, 200, -200, 200);
    glutDisplayFunc(renderFunction);
    glutMainLoop();
    return 0;
}
