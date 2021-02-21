#pragma once

#include "Inert.h"
#include "Mario.h"

enum spawnable_t
{
	COIN,
	LEAF,
	LIFE,
	FLOWER,
	STAR
};

class SecretBox : public Inert
{
	protected:
		
		// attributes
		spawnable_t content;
		bool active;
		Mario *mario;

		// textures
		QPixmap texture_active[4];
		QPixmap texture_inactive;

		// counters
		int animation_counter;
		int hit_counter;

	public:

		SecretBox(QPoint position, spawnable_t spawnable = COIN);

		// utility method
		void spawn();

		// inherited methods
		virtual std::string name() {return "SecretBox";}
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir);

		// @ovveride
		virtual void advance();

		// setters
		void setHitcounter(int count) { hit_counter = count; }
		void setActive(bool _active) { active = _active; }

		// getters
		bool isLeaf() { return content == LEAF ? true : false; }
		int getHitcounter() { return hit_counter; }
};