#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState {
protected:
	bool keys[256];
	bool mouse[3];

public:
	GameState() {}
	~GameState() {}

	virtual void resize(int w, int h) = 0;
	virtual void update(int fps) = 0;
	virtual void render() = 0;
	virtual void keyDown(unsigned char key, int xx, int yy);
	virtual void keyUp(unsigned char key, int xx, int yy);
	virtual void mousePress(int button, int state, int x, int y);
	virtual void mousePressedMove(int x, int y);
	virtual void mouseReleasedMove(int x, int y);
};

#endif