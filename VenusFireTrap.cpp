#include "VenusFireTrap.h"
#include "Sprites.h"
#include "Sounds.h"
#include "Game.h"

VenusFireTrap::VenusFireTrap(QPoint position)
{
	// set attributes
	slow = true;
	moving = false;
	emerged = false;
	reentrant = false;

	// animation divisor
	animation_div = 8;

	// counters
	emerged_counter = -1;
	reentrant_counter = -1;
	number_fireball = -1;

	// durations
	death_duration = 30;
	emerged_duration = 9 * 16;
	reentrant_duration = 3 * 16;

	// textures
	texture[0] = Sprites::instance()->get1("VenusFireTrap-0");
	texture[1] = Sprites::instance()->get1("VenusFireTrap-1");
	texture_crash[0] = Sprites::instance()->get1("fireball-crush-0");
	texture_crash[1] = Sprites::instance()->get1("fireball-crush-1");
	texture_crash[2] = Sprites::instance()->get1("fireball-crush-2");

	// set texture and correct y-coordinate w.r.t. texture height
	setPixmap(texture[0]);
	setPos(position - QPoint(0, pixmap().height()));

	setZValue(1);
}

void VenusFireTrap::advance()
{
	Mario* mario = Game::instance()->getMario();

	// piranha plant emerges from the pipe and remain over the pipe 
	// then it go back (reentrant)
	if (emerged || (emerged_counter >= emerged_duration))
	{
		emerged_counter++;

		// emerges
		if (emerged_counter < (emerged_duration / 2))
		{
			setY(y() - 3);
		}

		if (emerged_counter > emerged_duration)
		{
			emerged = false;
		}

		// go back
		if (emerged_counter >= emerged_duration && emerged_counter < emerged_duration + 12)
		{
			setY(y() + 3);
		}

		// remain hide by pipe (reentrant)
		if (emerged_counter > emerged_duration + 16)
		{
			emerged_counter = -1;
			reentrant = true;
			number_fireball = -1;
		}
	}

	// time in wich it remain hide from pipe
	if (reentrant)
	{
		reentrant_counter++;

		if (reentrant_counter > reentrant_duration)
		{
			reentrant = false;
			reentrant_counter = -1;
		}
	}

	// if Mario is near to pipe, plant emerges
	if (!emerged && !reentrant
		&& !mario->isDying())
	{
		if ((!mario->isRacoon() && !(x() <= (mario->x() + 21) && x() >= (mario->x() - 22)))
			|| (mario->isRacoon() && !(x() <= (mario->x() + 28) && x() >= (mario->x() - 28))))
		{
			if (x() < (mario->x() + 100) && x() > (mario->x() - 116))
			{
				emerged = true;
			}
		}
	}

	if (_smash)
	{
		if (smash_counter == -1)
		{
			dying = true;
		}
	}

	Entity::advance();
}

void VenusFireTrap::animate()
{
	Entity::animate();
	Mario* mario = Game::instance()->getMario();

	// save current texture height (for later correction)
	int prev_h = boundingRect().height();

	// set the proper texture
	if (emerged && (x() < (mario->x() + 100) && x() > (mario->x() - 116)) && !dying)
	{
		setPixmap(texture[(animation_counter / animation_div) % 2]);
	}

	if (dying)
		setPixmap(texture_crash[(animation_counter / (animation_div)) % 3]);

	// correct y position if texture height changed
	int cur_h = boundingRect().height();
	if (prev_h != cur_h)
		setY(y() - (cur_h - prev_h));
}

void VenusFireTrap::hit(Object *what, Direction fromDir)
{
	Object::hit(what, fromDir);

	if (dynamic_cast<Mario*>(what) && fromDir == UP)
		moving = false;
}

void VenusFireTrap::hurt()
{
	Sounds::instance()->play("stomp");

	emerged_counter = 0;
}

void VenusFireTrap::smash()
{
	_smash = true;
}