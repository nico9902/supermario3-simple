#pragma once

#include "Enemy.h"

class VenusFireTrap : public Enemy
{
	
	protected:

	    // attributes
	    bool emerged;           // is emerged?
	    bool reentrant;         // is hide by pipe?

	    // textures
	    QPixmap texture[2];		// right-down animation
	    QPixmap texture_crash[3];           // crash animation (when is dying)

	    // counters
	    int emerged_counter;    // counts the number of frames since plant emerges
	    int reentrant_counter;
	    int number_fireball;

	    // durations
	    int emerged_duration;
	    int reentrant_duration;

    public:

	    VenusFireTrap(QPoint position);

	    // pure virtual methods that must be implemented
	    virtual std::string name() { return "VenusFireTrap"; }
	    virtual void animate();
	    virtual void hit(Object *what, Direction fromDir);
	    virtual void hurt();
	    virtual void smash();
	    virtual void advance();

	    // getters
	    bool isEmerged() { return emerged; }
};