#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

float xd1, yd1, xd2, yd2; // Coordinates for endpoints of the line
int ymax = 100, ymin = -100, xmax = 100, xmin = -100; // Window coordinates

// Function to round values to the nearest integer
float round_value(float v) {
    return (v + 0.5);
}

// Function to plot a point
void plotpoint(float a, float b) {
    glBegin(GL_POINTS);
    glVertex2f(a, b);
    glEnd();
}

// DDA Line Drawing Algorithm
void dda(float X1, float Y1, float X2, float Y2) {
    float dx, dy, x, y, xinc, yinc;
    int k, steps;

    dx = X2 - X1;
    dy = Y2 - Y1;
    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    xinc = dx / (float)steps;
    yinc = dy / (float)steps;
    
    x = X1, y = Y1;
    plotpoint(x, y);

    for (k = 0; k < steps; k++) {
        x += xinc;
        y += yinc;
        plotpoint(round_value(x), round_value(y));
    }
    glFlush();
}

// Function to calculate the outcode for a point
int code(int x, int y) {
    int c = 0;
    if (y > ymax) c = 8;
    if (y < ymin) c = 4;
    if (x > xmax) c |= 2;
    if (x < xmin) c |= 1;
    return c;
}

// Display function
void disp() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1.0, 0.0, 0.0); // Set color to red
    dda(xmin, ymin, xmax, ymin); // Draw bottom boundary
    dda(xmax, ymin, xmax, ymax); // Draw right boundary
    dda(xmax, ymax, xmin, ymax); // Draw top boundary
    dda(xmin, ymax, xmin, ymin); // Draw left boundary

    glColor3f(0.0, 0.0, 1.0); // Set color to blue
    dda(xd1, yd1, xd2, yd2); // Draw the clipped line
    
    glFlush();
}

// Cohen-Sutherland Line Clipping Algorithm
void cohen(float x1, float y1, float x2, float y2) {
    int c1 = code(x1, y1);
    int c2 = code(x2, y2);
    float m = (y2 - y1) / (x2 - x1);
    
    while ((c1 | c2) > 0) {
        if ((c1 & c2) > 0) {
            // Line is completely outside the window
            return;
        }
        
        int c;
        float x = x1, y = y1;
        
        if (c1 != 0) {
            c = c1;
        } else {
            c = c2;
            x = x2;
            y = y2;
        }
        
        if (c & 8) {
            // Line is above the window
            y = ymax;
            x = x + (1.0 / m) * (ymax - y1);
        } else if (c & 4) {
            // Line is below the window
            y = ymin;
            x = x + (1.0 / m) * (ymin - y1);
        } else if (c & 2) {
            // Line is to the right of the window
            x = xmax;
            y = y1 + m * (xmax - x1);
        } else if (c & 1) {
            // Line is to the left of the window
            x = xmin;
            y = y1 + m * (xmin - x1);
        }
        
        if (c == c1) {
            xd1 = x;
            yd1 = y;
            c1 = code(xd1, yd1);
        } else {
            xd2 = x;
            yd2 = y;
            c2 = code(xd2, yd2);
        }
    }
    disp(); // Redraw the window with the clipped line
}



// Initialization function
void init() {
    glClearColor(1.0, 1.0, 1.0, 0); // Set background color to white
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2); // Set point size
    gluOrtho2D(-320, 320, -240, 240); // Set orthogonal projection
    glFlush();
}

// Keyboard input function to trigger clipping
void mykey(unsigned char ch, int x, int y) {
    if (ch == 'c') {
        cohen(xd1, yd1, xd2, yd2);
    }
}

// Main function
int main(int argc, char **argv) {
    printf("Window coordinates are (-100, 100, -100, 100)\n");
    printf("Enter coordinates of the line (limits: -320, 320, -240, 240)\n");
    
    // Input coordinates for the line
    printf("Coordinates of the first point\n");
    printf("X1: ");
    scanf("%f", &xd1);
    printf("Y1: ");
    scanf("%f", &yd1);
    
    printf("Coordinates of the second point\n");
    printf("X2: ");
    scanf("%f", &xd2);
    printf("Y2: ");
    scanf("%f", &yd2);

    // Initialize GLUT and OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Line Clipping");

    init();
    glutDisplayFunc(disp);
    glutKeyboardFunc(mykey);
    glutMainLoop();
    
    return 0;
}

