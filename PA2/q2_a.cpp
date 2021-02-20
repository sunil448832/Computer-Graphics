//compilation command g++ gl.cpp -o gl -lGL -lGLU -lglut
//run command ./gl

#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0); // display window color .
    glMatrixMode(GL_PROJECTION);      // projection parameters.
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

void draw(int x0, int y0, int x1, int y1, int x2, int y2)
{
    int d_x0 = x1 - x0, d_y0 = y1 - y0;
    int d_x1 = x2 - x1, d_y1 = y2 - y1;
    int d_x2 = x0 - x2, d_y2 = y0 - y2;

    int xmin = min(x0, min(x1, x2)), ymin = min(y0, min(y1, y2));
    int xmax = max(x0, max(x1, x2)), ymax = max(y0, max(y1, y2));
    int q = xmax - xmin;
    int f0 = (xmin - x0) * d_y0 - (ymax - y0) * d_x0;
    int f1 = (xmin - x1) * d_y1 - (ymax - y1) * d_x1;
    int f2 = (xmin - x2) * d_y2 - (ymax - y2) * d_x2;
    glBegin(GL_POINTS);
    for (GLint y = ymax; y >= ymin; y--)
    {

        for (GLint x = xmin; x <= xmax; x++)
        {

            if ((f0 < 0) && (f1 < 0) && (f2 < 0))
            {
                glVertex2i(x, y);
            }

            //fi ← fi + ∆yi , i ∈ 0, 1, 2
            f0 = f0 + d_y0;
            f1 = f1 + d_y1;
            f2 = f0 + d_y2;
        }
        //fi ← fi − q∆yi, i ∈ 0, 1, 2
        f0 = f0 - q * d_y0;
        f1 = f1 - q * d_y1;
        f2 = f0 - q * d_y2;

        //fi ← fi + ∆xi, i ∈ 0, 1, 2
        f0 = f0 + d_x0;
        f1 = f1 + d_x1;
        f2 = f0 + d_x2;
    }
    glEnd();

    glFlush();
}
void traingle(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear display window.
    //glPointSize(5);
    glColor3f(0.0, 0.0, 0.0);
    // glBegin(GL_POINTS);
    // glVertex2i(10, 10);
    // glEnd();
    //int x0 = 44, y0 = 22, x1 = 100, y1 = 50, x2 = 200, y2 = 200;
    int x0 = 100, y0 = 200;
    int x1 = 200, y1 = 100;
    int x2 = 200, y2 = 200;
    draw(x0, y0, x1, y1, x2, y2);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);                                 // Initialize GLUT.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);           // Set display mode.
    glutInitWindowPosition(20, 20);                        // Set top-left display-window position.
    glutInitWindowSize(500, 500);                          // Set display-window width and height.
    glutCreateWindow("CSL7450: Incremental Line Drawing"); // Create display window.
    init();                                                // Execute initialization procedure.

    cout << "Enter the cordinates in x0 y0 x1 y1 x2 y2 format" << endl;
    //int x0, y0, x1, y1, x2, y2;
    //cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2;
    glutDisplayFunc(traingle); // Send graphics to display window.
    glutMainLoop();            // Display everything and wait.
}