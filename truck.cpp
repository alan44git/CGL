

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cstdlib>
#include <cmath>
using namespace std;

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

void BSA_Algo(int xi, int xf, int yi, int yf)
{
    int P;
    int dx = xf - xi;
    int dy = yf - yi;
    dx = abs(dx);
    dy = abs(dy);
    int x = xi, y = yi;

    int x_change = 1, y_change = 1;
    if(xi > xf) x_change = -1;
    if(yi > yf) y_change = -1;
    glVertex2i(x, y);
    if (dx == 0){
        glBegin(GL_POINTS);
        for (int i = 1; i<dy; i++){
            y = y + y_change;
            glVertex2i(x, y);
        }
        glEnd();
        return;
    }
    if (dy == 0){
        glBegin(GL_POINTS);
        for (int i = 1; i<dx; i++){
            x = x + x_change;
            glVertex2i(x, y);
        }
        glEnd();
        return;
    }
    glBegin(GL_POINTS);
    if (dx > dy){
        P = 2*dy -dx;
        for(int i = 0; i < dx; i++){
            if (P > 0){
                y += y_change;
                P = P + 2*(dy - dx);
            }
            else{
                P = P + 2*dy;
            }
            x += x_change;
            glVertex2i(x, y);
        }
    }
    else{
        P = 2*dx -dy;
        for(int i = 0; i < dy; i++){
            if (P > 0){
                x += x_change;
                P = P + 2*(dx - dy);
            }
            else{
                P = P + 2*dx;
            }
            y += y_change;
            glVertex2i(x, y);
        }
    }
    glEnd();
}

void render_function()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
    gluOrtho2D(-250, 250, -250, 250);
    glBegin(GL_POINTS);
    BSA_Algo(0,150,0,0);
    BSA_Algo(150,150,0,100);
    BSA_Algo(0,0,0,100);
    BSA_Algo(0,150,100,100);

    BSA_Algo(-4,-100,0,0);
    BSA_Algo(-4,-4,0,100);

    BSA_Algo(-4,-40,100,100);
    BSA_Algo(-100,-100,0,40);

    BSA_Algo(-40,-40,100,70);
    BSA_Algo(-40,-70,70,70);

    BSA_Algo(-70,-100,70,40);

    BSA_Algo(-70,-70,60,40);
    BSA_Algo(-70,-40,40,40);
    BSA_Algo(-40,-40,40,60);
    BSA_Algo(-40,-70,60,60);

    bresenhamCircle(-52, -22, 22);
    bresenhamCircle(-52, -20, 10);

    bresenhamCircle(35, -22, 22);
    bresenhamCircle(35, -22, 10);

    bresenhamCircle(115, -22, 22);
    bresenhamCircle(115, -22, 10);




    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham");
    glutDisplayFunc(render_function);
    glutMainLoop();
    return 0;
}

