#pragma once
#include <libtcod.hpp>


class Actor
{
    public:
        int x, y; // Position on map
        int ch; // char for actor
        TCODColor col; // Color

        Actor( int x, int y, int ch, const TCODColor &col );
        void render() const;
};