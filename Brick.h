#pragma once

#include "Inert.h"

class Brick : public Inert 
{
	protected:
	
	    bool hitted;				// whether the brick has been hit by Mario
		bool broken;				// whether the brick has been broken by Mario
		bool container;             // whether the brick contain switch block
		bool inactive;              // wether the switch block is spawned
		int  hit_counter;			// counts the number of frames since Mario hit
		int animation_counter;
		int animation_div;
		
		QPixmap texture[4];
		QPixmap texture_inactive;
		
	public:
	 
	    Brick(QPoint position, bool _container = false);
		
		// inherited methods
		virtual std::string name() { return "Brick"; }
		virtual void advance();
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir);
		
		// getters
		bool isContainer() { return container; }
};