#pragma once

#include "Entity.h"

class Coin : public Entity
{
	protected:
	
	    // textures
	    QPixmap texture_animation;
	
	public:

	    Coin(QPoint position);
		
		// inherited methods
		virtual std::string name() { return "Coin"; }
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir);
		
		// @override
		virtual void advance();
};