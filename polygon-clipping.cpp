#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

float xmin = -100, xmax = 100, ymin = -100, ymax = 100;
float polygon[20][2]; // Array to store the polygon vertices
int num_vertices = 0;  // Number of vertices in the polygon

float temp_polygon[20][2]; // Intermediate storage

void draw_line(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

int inside(float x, float y, int edge)
{
    switch (edge)
    {
    case 0:
        return x >= xmin; // Left
    case 1:
        return x <= xmax; // Right
    case 2:
        return y >= ymin; // Bottom
    case 3:
        return y <= ymax; // Top
    }
    return 0;
}

void intersection(float x1, float y1, float x2, float y2, float *xi, float *yi, int edge)
{
    float m = (x2 - x1) != 0 ? (y2 - y1) / (x2 - x1) : 0;

    switch (edge)
    {
    case 0: // Left
        *xi = xmin;
        *yi = y1 + m * (xmin - x1);
        break;
    case 1: // Right
        *xi = xmax;
        *yi = y1 + m * (xmax - x1);
        break;
    case 2: // Bottom
        if (x2 - x1 == 0)
        {
            *xi = x1;
        }
        else
        {
            *xi = x1 + (ymin - y1) / m;
        }
        *yi = ymin;
        break;
    case 3: // Top
        if (x2 - x1 == 0)
        {
            *xi = x1;
        }
        else
        {
            *xi = x1 + (ymax - y1) / m;
        }
        *yi = ymax;
        break;
    }
}

void clip_edge(int edge)
{
    float new_polygon[20][2];
    int new_count = 0;

    for (int i = 0; i < num_vertices; i++)
    {
        int next = (i + 1) % num_vertices;

        float x1 = polygon[i][0], y1 = polygon[i][1];
        float x2 = polygon[next][0], y2 = polygon[next][1];

        int in1 = inside(x1, y1, edge);
        int in2 = inside(x2, y2, edge);

        float xi, yi;

        if (in1 && in2) // Case 2
        {
            new_polygon[new_count][0] = x2;
            new_polygon[new_count][1] = y2;
            new_count++;
        }
        else if (in1 && !in2) // Case 3
        {
            intersection(x1, y1, x2, y2, &xi, &yi, edge);
            new_polygon[new_count][0] = xi;
            new_polygon[new_count][1] = yi;
            new_count++;
        }
        else if (!in1 && in2) // Case 1
        {
            intersection(x1, y1, x2, y2, &xi, &yi, edge);
            new_polygon[new_count][0] = xi;
            new_polygon[new_count][1] = yi;
            new_count++;

            new_polygon[new_count][0] = x2;
            new_polygon[new_count][1] = y2;
            new_count++;
        }
        // Case 4: Both outside – do nothing
    }

    for (int i = 0; i < new_count; i++)
    {
        polygon[i][0] = new_polygon[i][0];
        polygon[i][1] = new_polygon[i][1];
    }

    num_vertices = new_count;
}

void disp()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 0); // Red clipping window
    draw_line(xmin, ymin, xmax, ymin);
    draw_line(xmax, ymin, xmax, ymax);
    draw_line(xmax, ymax, xmin, ymax);
    draw_line(xmin, ymax, xmin, ymin);

    glColor3f(0, 0, 1); // Blue polygon
    for (int i = 0; i < num_vertices; i++)
    {
        int next = (i + 1) % num_vertices;
        draw_line(polygon[i][0], polygon[i][1], polygon[next][0], polygon[next][1]);
    }

    glFlush();
}

void mykey(unsigned char ch, int x, int y)
{
    if (ch == 'c')
    {
        for (int edge = 0; edge < 4; edge++) // Clip against all 4 edges
        {
            clip_edge(edge);
        }
        glutPostRedisplay();
    }
}

void init()
{
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2);
    gluOrtho2D(-320, 320, -240, 240);
    glFlush();
}

void get_polygon_input()
{
    int n;
    printf("Enter the number of vertices for the polygon: ");
    scanf("%d", &n);
    
    num_vertices = n;
    
    printf("Enter the vertices (x, y) for the polygon:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Vertex %d: ", i + 1);
        scanf("%f %f", &polygon[i][0], &polygon[i][1]);
    }
}

int main(int argc, char **argv)
{
    get_polygon_input();  // Get polygon input from terminal

    printf("Press 'c' to clip the polygon\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Polygon Clipping");

    init();

    glutDisplayFunc(disp);
    glutKeyboardFunc(mykey);
    glutMainLoop();

    return 0;
}
	
