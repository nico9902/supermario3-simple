#pragma once

#include "Entity.h"

class FireBall : public Entity 
{
	protected:

	    QPixmap texture[4];
	    QPixmap texture_crash[3];
	    Direction orientation;
	    bool crushed;                   // is crushed?

	    // counters
	    int crushed_counter;            // counts the number of frames since fireball crush

	    // durations
	    int crushed_duration;           // crushed duration

    public:

	    FireBall(QPoint position, Direction dir, Direction _orentation);
		
		// entity methods
		virtual std::string name() { return "FireBall"; }
		virtual void animate();
		virtual void advance();
		virtual void hit(Object *what, Direction fromDir);
		
		void crush();
		
		// @override
		virtual void die();
};