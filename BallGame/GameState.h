#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState {
public:
	GameState() {}
	~GameState() {}

	virtual void resize(int w, int h) = 0;
	virtual void update(int fps) = 0;
	virtual void render() = 0;
};

#endif