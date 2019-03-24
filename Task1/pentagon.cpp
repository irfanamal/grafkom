#include <GL/glut.h>


void polygon() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2d(0.0, 0.5);
		glVertex2d(0.35, 0.15);
		glVertex2d(0.25, -0.5);
		glVertex2d(-0.25, -0.5);
		glVertex2d(-0.35, 0.15);
	glEnd();
	glFlush();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(900, 600);
	glutCreateWindow("Polygon");
	glutDisplayFunc(polygon);
	glutMainLoop();
	return 0;
}
