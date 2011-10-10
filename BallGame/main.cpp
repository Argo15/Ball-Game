#include <stdlib.h>
#include <GL/freeglut.h>
#include "Globals.h"
#include "LevelState.h"
#include "MainMenuState.h"

int currentTime = 0;
int vsync = 0;

void init() {
	//GameState::GAMESTATE = new LevelState();		// Bill will work on this
	GameState::GAMESTATE = new MainMenuState();		// Mike will work on this
}

void resize(int w, int h) {
	GameState::GAMESTATE->resize(w, h);
}

void render(void) {
	int lastTime = currentTime;
	currentTime = glutGet( GLUT_ELAPSED_TIME );
	int timePassed = currentTime - lastTime;
	vsync += timePassed;
	if (vsync > (1000/60)){
		GameState::GAMESTATE->update(1000.0/(float)timePassed);
		GameState::GAMESTATE->render();
		vsync = 0;
	}
}

void keyDown(unsigned char key, int xx, int yy) {
	GameState::GAMESTATE->keyDown(key, xx, yy);
}

void keyUp(unsigned char key, int xx, int yy) {
	GameState::GAMESTATE->keyUp(key, xx, yy);
}

void mousePress(int button, int state, int x, int y) {
	GameState::GAMESTATE->mousePress(button, state, x, y);
}

void mousePressedMove(int x, int y) {
	GameState::GAMESTATE->mousePressedMove(x, y);
}

void mouseReleasedMove(int x, int y) {
	GameState::GAMESTATE->mouseReleasedMove(x, y);
}

void specialKeyDown(int key, int xx, int yy)
{

}

void mouseWheel(int button, int dir, int x, int y)
{
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
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(specialKeyDown);
	glutMouseFunc(mousePress);
	glutMotionFunc(mousePressedMove);
	glutPassiveMotionFunc(mouseReleasedMove);

	// enter GLUT event processing cycle
	init();
	glutMainLoop();

	return 1;
}
