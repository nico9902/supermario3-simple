#pragma once

#include "Enemy.h"
#include "Wing.h"

class ParaGoomba : public Enemy
{
	
	protected:
	
	    // attributes
		Wing* wing_left;                  // left wing
		Wing* wing_right;                 // right wing
		bool fly;                         // is fly?
		bool start_fly;                   // start fly (Mario is near to ParaGoomba)
		
		// counters
		int fly_counter;                  // counts the frames since ParaGoomba fly
		int number_jumps;                 // counts the number of jumps
		int invdir_counter;               // counts the frames after that ParaGoomba reverse direction
		int count_moving;                 
		
		// durations
		int fly_duration;                 // fly duration
		int invdir_duration;              // duration after that ParaGoomba reverse direction
		
		// textures
		QPixmap texture_walk_right[2];	  // brown/red walk animation
	    QPixmap texture_smashed;		  // brown/red smashed texture

    public:
	    
		ParaGoomba(QPoint position, Wing* _wing_left, Wing* _wing_right, Direction direction = LEFT);

	    // pure virtual methods that must be implemented
		virtual std::string name() { return "ParaGoomba"; }
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir);
	    virtual void hurt();
	    virtual void smash();
	    virtual void advance();

	    // @override
	    virtual void die();
	
	    void smallJump();
};