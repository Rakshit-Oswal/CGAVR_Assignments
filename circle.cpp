#include <GL/glut.h>
#include <cmath>

void circlepts(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
        glColor3f(1.0, 1.0, 0.0);
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);
    glEnd();
}

void drawCircleMidpoint(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 1 - r; // decision param

    circlepts(xc, yc, x, y);

    while (y > x) {
        if (d < 0) {
            d += 2 * x + 1;
        } else {
            d += 2 * (x - y) + 1;
            y--;
        }
        x++;
        circlepts(xc, yc, x, y);
    }
}

void display() {
    drawCircleMidpoint(300.0, 200.0, 100.0);
    glFlush();
}

void init() {
    glClearColor(0.7, 0.7, 0.7, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //origin at top left
    gluOrtho2D(0, 500.0, 500.0, 0); //left right bottom top
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Circle Drawing");

    init();

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}