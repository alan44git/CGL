#include<GL/freeglut.h>
#include<GL/gl.h>

void displayPoint(float x, float y){
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
}

void simpleLine(void){
	float x1 = 0.0;
	float y1 = 0.0;
	float x2 = 0.5;
	float y2 = 0.5;
	
	float step ;
	float dx = x2-x1;
	float dy = y2-y1;
	if(abs(dx) >abs(dy)){
		step = abs(dx);
	}		
	else step = abs(dy);
	float Xinc = dx/(float) step;
	float Yinc = dy/ (float)step;
	float x = x1;
	float y = y1;
	for(int i=0 ; i<=step ;i++){
		displayPoint(x,y);
		x= x + Xinc;
		y= y + Yinc;
	}
	glFlush();
}

void primitives(){
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
	simpleLine();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Line drawing");
	glutDisplayFunc(primitives);
	glutMainLoop();
	return 0;
}


