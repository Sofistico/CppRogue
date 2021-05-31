#include <stdio.h>
#include "libtcod.h"
#include "Actor.h"
#include "Map.h"
#include "Engine.h"


Actor::Actor( int x, int y, int ch, const TCODColor &col, const char *name ) : x( x ), y( y ),
    ch( ch ), col( col ), name( name ), blocks( true ), attacker( NULL ), destructible( NULL ),
    ai( NULL )
{
}


void Actor::render() const
{
    TCODConsole::root->setChar( x, y, ch );
    TCODConsole::root->setCharForeground( x, y, col );
}

void Actor::update()
{
    if( ai ) {
        ai->update( this );
    }
}