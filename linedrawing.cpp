#include <GL/glut.h>
#include <cmath>

//DDA line drawing algorithm
void drawLineDDA(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1,
	  dy = y2 - y1;

    int steps = std::max(std::abs(dx), std::abs(dy));

    float Xinc = dx / (float)steps,
    	  Yinc = dy / (float)steps;
    
    for (int i = 0; i <= steps; i++) {
    	glBegin(GL_POINTS);
		glColor3f(1.0, 1.0, 1.0);
        	glVertex2f(x1, y1);
	glEnd();
        x1 += Xinc;
        y1 += Yinc;
    }
}

//Bresenham's line drawing algorithm
void drawLineBresenham(float x1, float y1, float x2, float y2){
    int dx = std::abs( x2 - x1 ),
	dy = std::abs( y2 - y1 );

    int D = 2*dy - dx;

    //to adjust for cases when slope is negative or positive
    int stepx = (x1 < x2) ? 1 : -1,
	stepy = (y1 < y2) ? 1 : -1;

    glBegin(GL_POINTS);
    while(true){
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(x1, y1);

	if (x1 == x2 && y1 == y2) break;
	if (D > 0){
		D = 2*D - dx;
		x1 += stepx;
		y1 += stepy;
	} else if (D < 0){
		D += 2 * dy;
		x1 += stepx;
	}
    }
    glEnd();
}

void display() {
    drawLineDDA(0.0, 10.0, 300.0, 200.0);
    drawLineBresenham(300.0, 100.0, 400.0, 200.0);
    glFlush();
}

void init() {
    glClearColor(0.7, 0.7, 0.7, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gives the typical OpenGL coordinate system
    //with origin at top left
    gluOrtho2D(0, 500.0, 500.0, 0); //left right bottom top
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Line Drawing");

    init();

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
