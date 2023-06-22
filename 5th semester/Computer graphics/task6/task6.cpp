#include <windows.h>
#include <GL/gl.h >
#include <GL/glut.h >
#include <cmath>

static GLfloat spin = 0.0;

void display()
{
	glEnable(GL_DEPTH_TEST); // чтобы грани не просвечивались
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очищаяем буферы
	glPushMatrix(); // помещение текущей матрицы в стэк
	glRotatef(spin, 0.0f, 1.0f, 0.0f); 


	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(40, -40, -40);
	glVertex3f(40, -40, 40);
	glVertex3f(40, 40, 40);
	glVertex3f(40, 40, -40);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-40, -40, -40);
	glVertex3f(-40, -40, 40);
	glVertex3f(-40, 40, 40);
	glVertex3f(-40, 40, -40);
	
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(40, 40, -40);
	glVertex3f(40, 40, 40);
	glVertex3f(-40, 40, 40);
	glVertex3f(-40, 40, -40);

	glColor3f(0.5, 0.5, 0);
	glVertex3f(-40, -40, -40);
	glVertex3f(-40, -40, 40);
	glVertex3f(40, -40, 40);
	glVertex3f(40, -40, -40);

	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-40, -40, 40);
	glVertex3f(40, -40, 40);
	glVertex3f(40, 40, 40);
	glVertex3f(-40, 40, 40);

	glColor3f(0.2, 0.5, 0);
	glVertex3f(-40, -40, -40);
	glVertex3f(40, -40, -40);
	glVertex3f(40, 40, -40);
	glVertex3f(-40, 40, -40);
	glEnd();

	Sleep(50);

	glPopMatrix();
	glutSwapBuffers();
}

void spinDisplay(void)
{
	spin = spin + 2.0;
	if (spin > 360.0)
		spin = spin - 360.0;
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-150.0, 150.0, -150.0, 150.0, -200.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(350, 350);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Task №6");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(spinDisplay);
	glutMainLoop();
	return 0;
}