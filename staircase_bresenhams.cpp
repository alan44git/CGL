#include<GL/freeglut.h>
#include<GL/gl.h>

void drawLine(int xi, int yi, int xf, int yf){	
	int P;
	int dx = xf - xi;
	int dy = yf - yi;
	int x = xi, y = yi;
	dx = abs(dx);
	dy = abs(dy);
	int x_ch = 1, y_ch = 1;
	if(xi > xf) x_ch = -1;
	if(yi > yf) y_ch = -1;
	glVertex2i(x,y);
	if(dx == 0){
		glBegin(GL_POINTS);
			for(int i = 0; i < dy; i++){
				y = y + y_ch;
				glVertex2i(x,y);
			}
		glEnd();
		return;
	}
	if(dy == 0){
		glBegin(GL_POINTS);
			for(int i = 0; i < dx; i++){
				x = x + x_ch;
				glVertex2i(x,y);
			}
		glEnd();
		return;
	}
	
	glBegin(GL_POINTS);
		if(dx > dy){
			P = 2 * dy - dx;
			for(int i = 0; i < dx; i++){
				if(P > 0){
					y = y + y_ch;
					P = P + 2 * (dy-dx);
				}else{
					P = P + 2 * dy;	
				}
				x += x_ch;
				glVertex2i(x,y);
			}
		}else{
			P = 2 * dx - dy;
			for(int i = 0; i < dy; i++){
				if(P > 0){
					x += x_ch;
					P = P + 2*(dx-dy);	
				}else{
					P = P + 2*dx;
				}
				y += y_ch;
				glVertex2i(x,y);
			}
		}
	glEnd();
}

void render(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glOrtho(-250, 250, -250, 250, -250, 250);
	
	glFlush();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Bresenhams Algorithm");
	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}
