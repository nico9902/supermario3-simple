#pragma once

#include "Enemy.h"
#include "Wing.h"

class KoopaParaTroopa : public Enemy
{
	
	protected:
	
	    // attributes
	    Wing* wing;                       // wing
	    bool fly;                         // is fly?
	    bool start_fly;                   // start fly (Mario is near to ParaGoomba)

	    // counters
	    int fly_counter;                  // counts the frames since ParaGoomba fly
	    int number_jumps;
	    int count_moving;

	    // durations
	    int fly_duration;                 // fly duration

	    // textures
	    QPixmap texture_walk_right[2];    // walk animation
	    QPixmap texture_walk_left[2];	  // walk animation
	    QPixmap texture_smashed[2];		  // smashed texture
	    QPixmap texture_kicked[4];		  // smashed texture
		
	public:

	    KoopaParaTroopa(QPoint position, Wing* _wing, Direction direction = LEFT);

	    // pure virtual methods that must be implemented
	    virtual std::string name() { return "KoopaParaTroopa"; }
	    virtual void animate();
	    virtual void hit(Object *what, Direction fromDir);
	    virtual void hurt();
	    virtual void smash();
	    virtual void advance();

	    // @override
	    virtual void die();

	    void smallJump();
};