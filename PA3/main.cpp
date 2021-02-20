//compilation command g++ gl.cpp -o gl -lGL -lGLU -lglut
//run command ./gl

#include <GL/glut.h>
#include <bits/stdc++.h>
#include "utils.h"
using namespace std;

vector<vector<float>> vec;
vector<vector<int>> triangles;
vector<float> view = {0, 0, 0};
vector<float> light = {-50, -60, 160};
vector<float> light_vec = {0.0, 0, 0};

float xmin = 1000, xmax = 0, ymin = 1000, ymax = 0, zmin = 1000, zmax = 0;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);

    // objects, camera cordinates and view direction
    float xref = (xmin + xmax) / 2;
    float yref = (ymin + ymax) / 2;
    float zref = zmin;
    // float camx=xref+10,camy=yref,camz=zref-10;
    float camx = xref - 105, camy = 80, camz = zref - 30;
    float Vx = 0, Vy = 1, Vz = 0;
    view[0] = camx - xref, view[1] = camy - yref, view[2] = camz - zref;
    light_vec[0] = xref - light[0], light_vec[1] = yref - light[1], light_vec[2] = zref - light[2];

    // frustom cordinates
    float xwMin = xmin - 5, ywMin = ymin - 5, xwMax = xmax + 5, ywMax = xmax + 5;
    float dnear = 20, dfar = zmax + 200;
    vector<vector<float>> cord = frustom_cordinates(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
    cout << " Frustom Cordinates: " << endl;
    show(cord);

    // world cordinates transformation with respect to camera
    gluLookAt(camx, camy, camz, xref, yref, zref, Vx, Vy, Vz);
    // projection matrix calculation
    glMatrixMode(GL_PROJECTION);
    glFrustum(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
    float model[16];
    glGetFloatv(GL_PROJECTION_MATRIX, model);
    vector<vector<float>> projection_matrix = reshape(model);

    // normalized frustom cordinates
    vector<vector<float>> norm_cord = normalized_cordinates(projection_matrix, cord);
    cout << " \nNormalised Frustom Cordinates: " << endl;
    show(norm_cord);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); // Set fill color to green.
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE); // Wire-frame back face.
    int cnt = 0;
    for (auto tri : triangles)
    {
        int p0 = tri[0], p1 = tri[1], p2 = tri[2];
        vector<vector<float>> points = {vec[p0], vec[p1], vec[p2]};
        vector<float> n = normal_vec(vec[p0], vec[p1], vec[p2]);
        vector<float> l = normalize(light_vec);
        view = normalize(view);
        vector<float> h = normalize(add(light_vec, view));

        vector<float> color = phong_shadding(h, n, l);
        if (dot_prod(n, view) > 0)
        {
            // cout<<points[0][0]<<" "<<points[0][1]<<" "<<points[0][2]<<endl;
            // cout<<points[1][0]<<" "<<points[1][1]<<" "<<points[1][2]<<endl;
            glBegin(GL_LINES);
            glVertex3f(points[0][0], points[0][1], points[0][2]);
            glVertex3f(points[1][0], points[1][1], points[1][2]);
            glEnd();

            glBegin(GL_LINES);
            glVertex3f(points[1][0], points[1][1], points[1][2]);
            glVertex3f(points[2][0], points[2][1], points[2][2]);
            glEnd();

            glBegin(GL_LINES);
            glVertex3f(points[2][0], points[2][1], points[2][2]);
            glVertex3f(points[0][0], points[0][1], points[0][2]);
            glEnd();

            glBegin(GL_TRIANGLES);
            glColor3f(color[0], color[1], color[2]);
            glVertex3f(points[0][0], points[0][1], points[0][2]);
            glVertex3f(points[1][0], points[1][1], points[1][2]);
            glVertex3f(points[2][0], points[2][1], points[2][2]);
            glEnd();
        }
    }

    glFlush();
}

int main(int argc, char **argv)
{
    string line;
    ifstream MyReadFile("cat01.off");
    //float count=0,xmin=1000,xmax=0,ymin=1000,ymax=0,zmin=1000,zmax=0;
    int count = 0;
    getline(MyReadFile, line);
    getline(MyReadFile, line);
    istringstream iss(line);
    vector<string> results(istream_iterator<string>{iss},
                           istream_iterator<string>());

    while (count < stoi(results[0]))
    {
        getline(MyReadFile, line);
        vector<float> v;
        count++;
        istringstream iss(line);
        vector<string> results(istream_iterator<string>{iss},
                               istream_iterator<string>());
        for (auto i : results)
        {
            float s = stof(i);
            v.push_back(s);
        }

        xmin = min(xmin, v[0]);
        xmax = max(xmax, v[0]);
        ymin = min(ymin, v[1]);
        ymax = max(ymax, v[1]);
        zmin = min(zmin, v[2]);
        zmax = max(zmax, v[2]);
        vec.push_back(v);
    }

    while (getline(MyReadFile, line))
    {
        vector<int> v;
        istringstream iss(line);
        vector<string> results(istream_iterator<string>{iss},
                               istream_iterator<string>());
        for (int i = 1; i < 4; i++)
        {
            int s = stoi(results[i]);
            v.push_back(s);
        }
        triangles.push_back(v);
    }

    MyReadFile.close();
    cout << triangles.size();

    // cout<<xmin<<" "<<xmax<<endl;
    // cout<<ymin<<" "<<ymax<<endl;
    // cout<<zmin<<" "<<zmax<<endl;
    // cout<<vec.size();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Programming Assignment 2");
    init();
    glutDisplayFunc(display);
    //glutReshapeFunc (reshapeFcn);
    glutMainLoop();
    return 0;
}
