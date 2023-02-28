#pragma once
#include <deque>
#include "SDL2/include/SDL.h"
#include "Actor.h"
#include "Map.h"

class Actor;
class Map;

class Engine
{
public:
	//TCODList<Actor*> actors;
	std::deque<Actor*> actors;

	Actor* player;
	Map* map;
	int fovRadius;

	int screenWidth;
	int screenHeight;
	//SDL_Event lastKey;

	Engine(int screenWidth, int screemHeight);
	~Engine();
	void update();
	void render();
	void sendToBack(Actor* owner);

	enum GameStatus {
		STARTUP,
		IDLE,
		NEW_TURN,
		VICTORY,
		DEFEAT
	} gameStatus;

private:
	bool computeFov;
};

extern Engine engine;