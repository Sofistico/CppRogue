#pragma once
#include <libtcod.hpp>
#include "Attacker.h"
#include "Destructible.h"
#include "Ai.h"


class Actor
{
    public:
        int x, y; // Position on map
        int ch; // char for actor
        TCODColor col; // Color
        const char *name; // the actor's name
        bool blocks; // Can we walk on this actor?
        Attacker *attacker; // something that deals damage
        Destructible *destructible; // something that can be damaged
        Ai *ai; // something sef-updating

        Actor( int x, int y, int ch, const TCODColor &col, const char *name );
        void render() const;
        void update();
};