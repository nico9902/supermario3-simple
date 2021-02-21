#pragma once

#include "Enemy.h"

class Goomba : public Enemy
{
	protected:

		// attributes
		bool red;                               // is red?
		int count_moving;                       // counts the number of times that moving became true

		// textures
		QPixmap texture_walk_right[2][2];		// brown/red walk animation
		QPixmap texture_dying[2];		        // brown/red dying texture
		QPixmap texture_smash[2];		        // brown/red smash texture

	public:

		Goomba(QPoint position, Direction direction = LEFT, bool isRed = false, bool _moving = true, 
			int _count_moving = 1);

		// pure virtual methods that must be implemented
		virtual std::string name() {return "Goomba";}
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir);
		virtual void hurt();
		virtual void smash();
		virtual void advance();
};