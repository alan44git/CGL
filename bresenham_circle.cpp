// C-program for circle drawing
// using Bresenham’s Algorithm
// in computer-graphics
#include<GL/freeglut.h>
#include<GL/gl.h>

// Function to put pixels
// at subsequence points
void drawCircle(int xc, int yc, int x, int y){
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
    glFlush();
}

// Function for circle-generation
// using Bresenham's algorithm
void circleBres(){
		int xc = 50, yc = 50, r = 30;
    int x = 0, y = r;
    int d = 3 - 2 * r;
    drawCircle(xc, yc, x, y);
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
        drawCircle(xc, yc, x, y);
    }
}



int main(int argc, char** argv)
{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE);
		glutInitWindowSize(500,500);
		glutInitWindowPosition(0,0);              
		glutCreateWindow("Bresenham's circle drawing algorithm");
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.0, 0.0, 0.0);  
		gluOrtho2D(0,500,0,500); 
		glutDisplayFunc(circleBres);

		glutMainLoop();
		return 0;
}

