#pragma once

#include "Enemy.h"

class PiranhaPlant : public Enemy
{
	
	protected:

	    // attributes
	    bool emerged;                // is emerged?
	    bool reentrant;              // is hide by pipe?
	    bool green;                  // is green?

	    // textures
	    QPixmap texture_right_down[2][2];		// right-down animation
	    QPixmap texture_right_up[2][2];		    // right-up animation
	    QPixmap texture_left_down[2][2];	    // left-down animation
	    QPixmap texture_left_up[2][2];		    // left-up animation
	    QPixmap texture_crash[3];               // crash animation (when is dying)

	    // counters
	    int emerged_counter;        // counts the number of frames since plant emerges
	    int reentrant_counter;      // counts the number of frames since plant remerges
	    int number_fireball;        // counts the number of fireball spawned by plant

	    // durations
	    int emerged_duration;       // emerged duration
	    int reentrant_duration;     // reentrant duration

    public:

	    PiranhaPlant(QPoint position, Direction direction = LEFT, bool isGreen=false);

	    // pure virtual methods that must be implemented
	    virtual std::string name() { return "PiranhaPlant"; }
	    virtual void animate();
	    virtual void hit(Object *what, Direction fromDir);
	    virtual void hurt();
	    virtual void smash();
	    virtual void advance();

	    // getters
	    bool isEmerged() { return emerged; }

	    // methods
	    void ThrowFireball();
};