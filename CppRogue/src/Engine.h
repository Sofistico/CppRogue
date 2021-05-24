#pragma once
#include "libtcod.hpp"
#include "Actor.h"
#include "Map.h"

class Actor;
class Map;

class Engine
{
    public:
        TCODList<Actor *> actors;
        Actor *player;
        Map *map;
        int fovRadius;

        Engine();
        ~Engine();
        void update();
        void render();

    private:
        bool computeFov;
};

extern Engine engine;