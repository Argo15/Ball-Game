#include <stdlib.h>
#include <GL/glut.h>
#include "Globals.h"
#include "LevelState.h"
#include "MainMenuState.h"

void init() {
	GAMESTATE = new LevelState();		// Bill will work on this
	//GAMESTATE = new MainMenuState();	// Mike will work on this
}

void resize(int w, int h) {
	GAMESTATE->resize(w, h);
}

void render(void) {
	GAMESTATE->update(60);
	GAMESTATE->render();
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