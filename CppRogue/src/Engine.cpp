#include "libtcod.hpp"
#include <SDL2/SDL.h>
#include "Actor.h"
#include "Map.h"
#include "Engine.h"
#include "Ai.h"
#include "Attacker.h"
#include "Destructible.h"

Engine::Engine(int screenWidth, int screenHeight) : fovRadius(10), gameStatus(STARTUP),
screenWidth(screenWidth), screenHeight(screenHeight)
{
	TCODConsole::initRoot(screenWidth, screenHeight, "libtcod C++ tutorial", false);

	player = new Actor(40, 25, '@', TCODColor::white, "Player");
	player->destructible = new PlayerDestructible(30, 2, "your cadaver");
	player->attacker = new Attacker(5);
	player->ai = new PlayerAi();
	actors.push_back(player);
	map = new Map(80, 45);
}

Engine::~Engine()
{
	actors.empty();
	delete map;
}

void Engine::update()
{
	if (gameStatus == STARTUP) {
		map->computeFov();
	}
	gameStatus = IDLE;

	player->update();
	if (gameStatus == NEW_TURN) {
		for (auto iterator = actors.begin(); iterator != actors.end();
			iterator++) {
			Actor* actor = *iterator;
			if (actor != player) {
				actor->update();
			}
		}
	}
}

void Engine::render()
{
	TCODConsole::root->clear();

	// drawn the map
	map->render();

	// draw the actors
	for (auto iterator = actors.begin();
		iterator != actors.end(); iterator++) {
		Actor* actor = *iterator;
		if (map->isInFov(actor->x, actor->y)) {
			actor->render();
		}
	}

	// show the player's stats
	TCODConsole::root->printf(1, screenHeight - 2, "HP : %d/%d", (int)player->destructible->hp,
		(int)player->destructible->maxHp);
}

void Engine::sendToBack(Actor* actor)
{
	actors.push_back(actor);
	//actors.(actor, 0);
}