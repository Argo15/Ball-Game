#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState {
protected:
	bool keys[256];
	bool mouse[10];
	int width, height;

public:
	GameState() {for (int i=0;i<3;i++) mouse[i]=false; for (int i=0;i<256;i++) keys[i]=false;}
	~GameState() {}

	virtual void resize(int w, int h);
	virtual void update(int fps) = 0;
	virtual void render() = 0;
	virtual void keyDown(unsigned char key, int xx, int yy);
	virtual void keyUp(unsigned char key, int xx, int yy);
	virtual void mousePress(int button, int state, int x, int y);
	virtual void mousePressedMove(int x, int y);
	virtual void mouseReleasedMove(int x, int y);
};

#endif