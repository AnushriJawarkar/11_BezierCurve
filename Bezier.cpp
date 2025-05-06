
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Point { 
    float x, y;
};

vector<Point> ctrlPoints; 
int numCtrlPoints;

void init() {
    glClearColor(1, 1, 1, 1);  // White background
    glColor3f(0, 0, 1);        // Blue curve
    glPointSize(5.0);          // Bigger points
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
}

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int binomial(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

Point bezierPoint(const vector<Point>& points, float t) {
    int n = points.size() - 1;
    Point p = {0, 0};
    
    for (int i = 0; i <= n; ++i) {
        float coeff = binomial(n, i) * pow(t, i) * pow(1 - t, n - i);
        p.x += points[i].x * coeff;
        p.y += points[i].y * coeff;
    }
    
    return p;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw control points
    glColor3f(1, 0, 0); // Red control points
    glBegin(GL_POINTS);
    for (auto& p : ctrlPoints) {
        glVertex2f(p.x, p.y);
    }
    glEnd();

    // Draw Bezier curve
    glColor3f(0, 0, 1); // Blue curve
    glBegin(GL_LINE_STRIP);
    for (float t = 0; t <= 1.0; t += 0.01) {
        Point p = bezierPoint(ctrlPoints, t);
        glVertex2f(p.x, p.y);
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    cout << "Enter number of control points: ";
    cin >> numCtrlPoints;

    ctrlPoints.resize(numCtrlPoints);
    for (int i = 0; i < numCtrlPoints; i++) {
        cout << "Enter control point " << i + 1 << " (x y): ";
        cin >> ctrlPoints[i].x >> ctrlPoints[i].y;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Simple Bezier Curve");
    
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
/*Enter number of control points: 4
Enter control point 1 (x y): 100 100
Enter control point 2 (x y): 150 300
Enter control point 3 (x y): 300 300
Enter control point 4 (x y): 400 100
*/
