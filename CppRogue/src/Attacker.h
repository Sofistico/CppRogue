#pragma once

class Attacker
{
    public:
        float power; // hit poing given

        Attacker( float power );

        void attack( Actor *owner, Actor *target );
};