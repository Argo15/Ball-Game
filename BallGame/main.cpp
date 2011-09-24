#include <GL/glut.h>

void init() {
	glShadeModel(GL_SMOOTH);				// GL_SMOOTH or GL_FLAT
	glClearDepth(1.0f);						// depth cleared to
	glEnable(GL_DEPTH_TEST);				// enable depth testing
	glEnable(GL_TEXTURE_2D);				// enable texturing
	glDepthFunc(GL_LEQUAL);					// lesser than or equal to depth
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);	// Really Nice Perspective Calculations
	glEnable(GL_NORMALIZE);
}

void resize(int w, int h) {
	if(h == 0)
		h = 1;
	GLfloat aspect = GLfloat(w) / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0,aspect,1,1000);
	glMatrixMode(GL_MODELVIEW);
}

void render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslated(0,0,-5.0);

	glBegin(GL_TRIANGLES);
		glVertex3f(-2.0f,-2.0f, 0.0f);
		glVertex3f( 2.0f, 0.0f, 0.0);
		glVertex3f( 0.0f, 2.0f, 0.0);
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1280,720);
	glutCreateWindow("Ball Game");

	// register callbacks
	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutIdleFunc(render);

	// enter GLUT event processing cycle
	init();
	glutMainLoop();

	return 1;
}