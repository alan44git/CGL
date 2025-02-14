// C-program for circle drawing
// using Bresenham’s Algorithm
// in computer-graphics
#include<GL/freeglut.h>
#include<GL/gl.h>
#include<math.h>
// Function to put pixels
// at subsequence points
void plotCircle(int xc, int yc, int x, int y){
    glBegin(GL_POINTS);
		  glVertex2i(xc+x, yc+y);
		  glVertex2i(xc-x, yc+y);
		  glVertex2i(xc+x, yc-y);
		  glVertex2i(xc-x, yc-y);
		  glVertex2i(xc+y, yc+x);
		  glVertex2i(xc-y, yc+x);
		  glVertex2i(xc+y, yc-x);
		  glVertex2i(xc-y, yc-x);
    glEnd();
}

// Function for circle-generation
// using Bresenham's algorithm
void bresenhams(int xc, int yc, int r){
    int x = 0, y = r;
    int d = 3 - 2 * r;
    plotCircle(xc, yc, x, y);
    while (y >= x){
      
        // check for decision parameter
        // and correspondingly 
        // update d, y
        if (d > 0) {
            y--; 
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;

        // Increment x after updating decision parameter
        x++;
        
        // Draw the circle using the new coordinates
        plotCircle(xc, yc, x, y);
    }
}

double ang(int q) {
    return (double)q * 3.142 / 180;
}

void pattern1(int x, int y, int r) {
    bresenhams(x, y, r);
    bresenhams(x + 2 * r, y, r); 
    bresenhams(x - 2 * r, y, r);
    bresenhams(x + 2 * r * cos(ang(60)), y + 2 * r * sin(ang(60)), r);
    bresenhams(x - 2 * r * cos(ang(60)), y + 2 * r * sin(ang(60)), r);
    bresenhams(x - 2 * r * cos(ang(60)), y - 2 * r * sin(ang(60)), r);
    bresenhams(x + 2 * r * cos(ang(60)), y - 2 * r * sin(ang(60)), r);
    bresenhams(x, y, 3 * r);
    bresenhams(x, y, (float)2 * r - r * (0.20));
}

void draw(){
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen
    int cx = 300, cy = 300, R = 70;
    pattern1(cx, cy, R);  // solid line multiple circles
    glFlush();  // Ensure the drawing is rendered
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Specify color and single buffer
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham's Circle Drawing Algorithm");

    glClearColor(1.0, 1.0, 1.0, 0.0);  // Set background color (white)
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen
    glColor3f(0.0, 0.0, 0.0);  // Set the drawing color (black)
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);  // Set the 2D orthographic view

    glutDisplayFunc(draw);  // Set the display function
    glutMainLoop();  // Enter the GLUT event loop
    return 0;
}


