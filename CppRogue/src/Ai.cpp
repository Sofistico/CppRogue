#include "Ai.h"
#include "Engine.h"

// how many turns the monster chases the player
// after losing his sight
static const int TRACKING_TURNS = 3;

void PlayerAi::update(Actor* owner)
{
	if (owner->destructible && owner->destructible->isDead()) {
		return;
	}

	int dx = 0, dy = 0;
	/*switch (engine.lastKey.type) {
	case SDL_KEYDOWN:
		switch (engine.lastKey.key.keysym.sym)
		{
		case SDLK_KP_8: case SDLK_UP:
			dy = -1;
		case SDLK_KP_2: case SDLK_DOWN:
			dy = 1;
		case SDLK_KP_6: case SDLK_RIGHT:
			dx = 1;
		case SDLK_KP_4: case SDLK_LEFT:
			dx = -1;

		case SDLK_KP_7:
			dy = -1;
			dx = -1;

		case SDLK_KP_9:
			dy = -1;
			dx = 1;

		case SDLK_KP_1:
			dx = -1;
			dy = 1;

		case SDLK_KP_3:
			dx = 1;
			dy = 1;
		}
	default:
		break;
	}*/

	if (dx != 0 || dy != 0) {
		engine.gameStatus = Engine::NEW_TURN;
		if (moveOrAttack(owner, owner->x + dx, owner->y + dy)) {
			engine.map->computeFov();
		}
	}
}

bool PlayerAi::moveOrAttack(Actor* owner, int targetx, int targety)
{
	if (engine.map->isWall(targetx, targety)) {
		return false;
	}
	// look for living actors to attack
	for (auto iterator = engine.actors.begin();
		iterator != engine.actors.end(); iterator++) {
		Actor* actor = *iterator;
		if (actor->destructible && !actor->destructible->isDead()
			&& actor->x == targetx && actor->y == targety) {
			owner->attacker->attack(owner, actor);
			return false;
		}
	}
	// look for corpses
	for (auto iterator = engine.actors.begin();
		iterator != engine.actors.end(); iterator++) {
		Actor* actor = *iterator;
		if (actor->destructible && actor->destructible->isDead()
			&& actor->x == targetx && actor->y == targety) {
			printf("There's a %s here\n", actor->name);
		}
	}

	owner->x = targetx;
	owner->y = targety;
	return true;
}

void MonsterAi::update(Actor* owner)
{
	if (owner->destructible && owner->destructible->isDead()) {
		return;
	}
	if (engine.map->isInFov(owner->x, owner->y)) {
		// we can see the player. move towards him
		moveCount = TRACKING_TURNS;
	}
	else {
		moveCount--;
	}
	if (moveCount > 0) {
		moveOrAttack(owner, engine.player->x, engine.player->y);
	}
}

void MonsterAi::moveOrAttack(Actor* owner, int targetx, int targety)
{
	int dx = targetx - owner->x;
	int dy = targety - owner->y;
	int stepdx = (dx > 0 ? 1 : -1);
	int stepdy = (dy > 0 ? 1 : -1);
	float distance = sqrtf(dx * dx + dy * dy);
	if (distance >= 2) {
		dx = (int)(round(dx / distance));
		dy = (int)(round(dy / distance));

		if (engine.map->canWalk(owner->x + dx, owner->y + dy)) {
			owner->x += dx;
			owner->y += dy;
		}
		else if (engine.map->canWalk(owner->x + stepdx, owner->y)) {
			owner->x += stepdx;
		}
		else if (engine.map->canWalk(owner->x, owner->y + stepdy)) {
			owner->y += stepdy;
		}
	}
	else if (owner->attacker) {
		owner->attacker->attack(owner, engine.player);
	}
}