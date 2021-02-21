#pragma once
#include "Entity.h"


// Enemy object can kill Mario
// Enemies of this level are: Goomba, KoopaTroopa, KoopaParaTroopa, ParaGoomba, PiranhaPlant, VenusFireTrap
class Enemy : public Entity
{
	protected:

		// animation divisors
		int animation_div;
		
		bool _smash;           // is smashed? 

		// counters
		int smash_counter;     // count the number of frames since enemy is smashed

	public:

		Enemy();

		// pure virtual methods that must be implemented
		virtual std::string name() = 0;
		virtual void animate() = 0;
		virtual void hit(Object *what, Direction fromDir) = 0;

		// enemies can be hurt
		virtual void hurt() = 0;
		virtual void smash() = 0;

		// getters
		bool isSmashed() { return _smash; }

		// setters
		void setSmashed(bool _smashed) { _smash = _smashed; }
};