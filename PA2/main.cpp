#include<iostream>
#include<algorithm>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h> // (or others, depending on the system in use)
using namespace std;

void init (void)
{
	glClearColor (1.0, 1.0, 1.0, 0.0); // Set display-window color to white.
	glMatrixMode (GL_PROJECTION); // Set projection parameters.
	gluOrtho2D (0, 300, 300, 1);// Orthogonal projection: [x,y,z]--->[x,y,0]
}
void dispPoint (void)
{
	glClear (GL_COLOR_BUFFER_BIT); // Clear display window.
	glColor3f (1.0, 0.0, 0.0); // Set point color to green.
	glPointSize(10.0f); // Set point size
    //Bounding Box Algorithm starts

    //Input Points
    int x0 = 100, y0 = 200;
    int x1 = 200, y1 = 100;
    int x2 = 200, y2 = 200;

    //parameters
    int del_x0 = x1-x0, del_y0= y1-y0;
    int del_x1 = x2-x1, del_y1= y2-y1;
    int del_x2 = x0-x2, del_y2= y0-y2;

    int xmin, ymin, xmax, ymax;

    int tempmax = max(x0,x1);
    xmax = max(tempmax,x2);

    int tempmin = min(x0,x1);
    xmin = min(tempmin,x2);

    tempmax = max(y0,y1);
    ymax = max(tempmax,y2);

    tempmin = min(y0,y1);
    ymin = min(tempmin,y2);

    int q = xmax - xmin;

    int f0 = ((xmin - x0)*del_y0) - ((ymax-y0)*del_x0);
    int f1 = ((xmin - x1)*del_y1) - ((ymax-y1)*del_x1);
    int f2 = ((xmin - x2)*del_y2) - ((ymax-y2)*del_x2);

    int g0 = ((x2 - x0)*del_y0) - ((y2-y0)*del_x0);
    int g1 = ((x0 - x1)*del_y1) - ((y0-y1)*del_x1);
    int g2 = ((x1 - x2)*del_y2) - ((y1-y2)*del_x2);

    float alpha, beta, gamma;

    for(int i=ymin; i<=ymax; i++)
    {
        for(int j=xmin; j<=xmax; j++)
        {
            alpha = f1/g1;
            beta = f2/g2;
            gamma = f0/g0;
            if((alpha+beta+gamma)==1.0 && alpha>=0 && beta>=0 && gamma>=0)
            {
                glBegin(GL_POINTS);// Marks the beginning of the vertices list
                glVertex2i(j,i); // Specify point location.
            }

            f0 = f0 + del_y0;
            f1 = f1 + del_y1;
            f2 = f2 + del_y2;
        }
        f0 = f0 - (q*del_y0);
        f1 = f1 - (q*del_y1);
        f2 = f2 - (q*del_y2);

        /*f0 = f0 + del_x0;
        f1 = f1 + del_x1;
        f2 = f2 + del_x2;*/
    }


    //Bounding algorithm ends
    /*glBegin(GL_TRIANGLES);// Marks the beginning of the vertices list
    glVertex2i (100, 200); // Specify point location.
    glVertex2i (200, 100); // Specify point location.
    glVertex2i (200, 200); // Specify point location.*/
	glEnd( );
	glFlush( );
}
int main (int argc, char** argv)
{
	glutInit (&argc, argv); // Initialize GLUT.
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // Set display mode.
	glutInitWindowPosition (20, 20); // Set top-left display-window position.
	glutInitWindowSize (300, 300); // Set display-window width and height.
	glutCreateWindow("CSL7450: PA-1: Bounding Box Algorithm"); // Create display window.
	init ( ); // Execute initialization procedure.
	glutDisplayFunc (dispPoint); // Send graphics to display window.
	glutMainLoop ( ); // Display everything and wait.
}
