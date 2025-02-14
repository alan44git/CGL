#include <GL/glut.h>
#include <cmath>

float radius = 0.5f;
int numCircles = 10;

void drawCircle(float centerX, float centerY, float r) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14f / 180.0f;
        glVertex2f(centerX + r * cos(angle), centerY + r * sin(angle));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    float centerX = 0.0f, centerY = 0.0f;

    glColor3f(0, 1, 0);
    drawCircle(centerX, centerY, radius);

    glColor3f(0, 1, 0);
    for (int i = 0; i < numCircles; i++) {
        float angle = 2 * 3.14159f * i / numCircles;
        float x = (centerX + radius * cos(angle))/2;
        float y = (centerY + radius * sin(angle))/2;

        drawCircle(x, y, radius / 2.0f);
    }

    glFlush();
}

void initOpenGL() {
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Outer Circle with Inner Circles");
    initOpenGL();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
