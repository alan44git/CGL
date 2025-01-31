#include <GL/freeglut.h>
#include <GL/gl.h>

void renderFunction()
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // sets the color of window
	glClear(GL_COLOR_BUFFER_BIT); // forces the color on the window, without this it doesn't work
	glColor3f(0.0, 0.0, 0.0); // sets the color of the object 
	gluOrtho2D(0,500,0,500); // setting world-coordinates
	glBegin(GL_POLYGON);
		glVertex2i(50,0);
		glVertex2i(150,0);
		glVertex2i(175,100);
		glVertex2i(100,175);
		glVertex2i(25,100);
	glEnd();
	glBegin(GL_LINES);
		glVertex2i(0,175);
		glVertex2i(225,175);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);              
	glutCreateWindow("Practice 1");
	glutDisplayFunc(renderFunction);
	glutMainLoop();
	return 0;
}
