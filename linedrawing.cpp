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

void midPoint(int X1, int Y1, int X2, int Y2) 
{ 
    int dx = std::abs(X2 - X1),
        dy = std::abs(Y2 - Y1); 

    int x, y;

    int stepx = (X1 < X2) ? 1 : -1,
        stepy = (Y1 < Y2) ? 1 : -1;

    if (dx > dy) { // Slope < 1
        int d = 2 * (dy - dx);
        x = X1;
        y = Y1;

        glBegin(GL_POINTS);
        glColor3f(0.0, 1.0, 0.0); 
        glVertex2i(x, y);

        while (x != X2) {
            x += stepx;
            //to the right
            if (d < 0) {
                d +=  dy;
            }
            //to the top right 
            else {
                y += stepy;
                d += (dy - dx);
            }
            glVertex2i(x, y);
        }
    } else { // Slope > 1
        int d = 2 * (dx - dy);
        x = X1;
        y = Y1;
     
        glBegin(GL_POINTS);
        glColor3f(0.0, 1.0, 0.0); 
        glVertex2i(x, y);

        while (y != Y2) {
            y += stepy;
            //to the right
            if (d < 0) {
                d += dx;
            }
            //to the top right 
            else {
                x += stepx;
                d += (dx - dy);
            }
            glVertex2i(x, y);
        }
    }
    glEnd();
}

void display() {
    drawLineDDA(300.0, 200.0, 0.0, 10.0);
    drawLineBresenham(300.0, 100.0, 400.0, 200.0);
    midPoint(200.0, 0.0, 300.0, 300.0);
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
    glutCreateWindow("DDA Line Drawing");

    init();

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
