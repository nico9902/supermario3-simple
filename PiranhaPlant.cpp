#include "PiranhaPlant.h"
#include "Sprites.h"
#include "Sounds.h"
#include "Game.h"
#include "FireBall.h"

PiranhaPlant::PiranhaPlant(QPoint position, Direction direction, bool isGreen)
{
	// set attributes
	dir = direction;
	slow = true;
	moving = false;
	emerged = false;
	reentrant = false;
	green = isGreen;

	// animation divisor
	animation_div = 8;

	// counters
	emerged_counter = -1;
	reentrant_counter = -1;
	number_fireball = -1;

	// durations
	death_duration = 30;
	emerged_duration = 9*16;
	reentrant_duration = 3 * 16;

	// textures
	texture_left_down[0][0] = Sprites::instance()->get("PiranhaPlant-2");
	texture_left_down[0][1] = Sprites::instance()->get("PiranhaPlant-3");
	texture_left_down[1][0] = Sprites::instance()->get1("PiranhaPlant-green-0");
	texture_left_down[1][1] = Sprites::instance()->get1("PiranhaPlant-green-1");
	texture_left_up[0][0] = Sprites::instance()->get("PiranhaPlant-4");
	texture_left_up[0][1] = Sprites::instance()->get("PiranhaPlant-5");
	texture_left_up[1][0] = Sprites::instance()->get1("PiranhaPlant-green-2");
	texture_left_up[1][1] = Sprites::instance()->get1("PiranhaPlant-green-3");
	texture_right_up[0][0] = texture_left_up[0][0].transformed(QTransform().scale(-1, 1));
	texture_right_up[0][1] = texture_left_up[0][1].transformed(QTransform().scale(-1, 1));
	texture_right_up[1][0] = texture_left_up[1][0].transformed(QTransform().scale(-1, 1));
	texture_right_up[1][1] = texture_left_up[1][1].transformed(QTransform().scale(-1, 1));
	texture_right_down[0][0] = texture_left_down[0][0].transformed(QTransform().scale(-1, 1));
	texture_right_down[0][1] = texture_left_down[0][1].transformed(QTransform().scale(-1, 1));
	texture_right_down[1][0] = texture_left_down[1][0].transformed(QTransform().scale(-1, 1));
	texture_right_down[1][1] = texture_left_down[1][1].transformed(QTransform().scale(-1, 1));
	texture_crash[0] = Sprites::instance()->get1("fireball-crush-0");
	texture_crash[1] = Sprites::instance()->get1("fireball-crush-1");
	texture_crash[2] = Sprites::instance()->get1("fireball-crush-2");

	// set texture and correct y-coordinate w.r.t. texture height
	setPixmap(texture_left_up[0][0]);
	setPos(position - QPoint(0, pixmap().height()));

	setZValue(1);
}

void PiranhaPlant::advance()
{
	Mario* mario = Game::instance()->getMario();

	// piranha plant emerges from the pipe and remain over the pipe 
	// then it go back (reentrant)
	if (emerged || (emerged_counter>=emerged_duration))
	{
		emerged_counter++;

		// emerges
		if (emerged_counter < (emerged_duration / 2))
		{
			setY(y() - 3);
		}

		if (emerged_counter > emerged_duration - 24)
		{
			ThrowFireball();
		}
		
		if (emerged_counter > emerged_duration)
		{
			emerged = false;
		}

		// go back
		if (emerged_counter >= emerged_duration && emerged_counter < emerged_duration + 16)
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

void PiranhaPlant::animate()
{
	Entity::animate();
	Mario* mario = Game::instance()->getMario();

	// save current texture height (for later correction)
	int prev_h = boundingRect().height();

	// set the proper texture
	if (emerged && (x() < (mario->x() + 100) && x() > (mario->x() - 116)) && !dying)
	{
		if (x() > mario->x() && y() <= mario->y() + 15)
			setPixmap(texture_left_down[green][(animation_counter / (animation_div*6)) % 2]);
		else if(x() > mario->x() && y() > mario->y() + 15)
			setPixmap(texture_left_up[green][(animation_counter / (animation_div*6)) % 2]);
		else if (x() < mario->x() && y() <= mario->y() + 15)
			setPixmap(texture_right_down[green][(animation_counter / (animation_div * 6)) % 2]);
		else if (x() < mario->x() && y() > mario->y() + 15)
			setPixmap(texture_right_up[green][(animation_counter / (animation_div * 6)) % 2]);
	}

	if (dying)
		setPixmap(texture_crash[(animation_counter / (animation_div)) % 3]);

	// correct y position if texture height changed
	int cur_h = boundingRect().height();
	if (prev_h != cur_h)
		setY(y() - (cur_h - prev_h));
}

void PiranhaPlant::hit(Object *what, Direction fromDir)
{
	Object::hit(what, fromDir);

	if (dynamic_cast<Mario*>(what) && fromDir == UP)
		moving = false;
}

void PiranhaPlant::hurt()
{
	Sounds::instance()->play("stomp");

	dying = true;
	emerged_counter = 0;
}

void PiranhaPlant::ThrowFireball()
{
	Mario* mario = Game::instance()->getMario();

	if (number_fireball < 0 && freezed == false)
	{
		if (x() > mario->x() && y() <= mario->y() + 15)
			new FireBall(QPoint(x()- 2, y() + 10), LEFT, DOWN);
		else if (x() > mario->x() && y() > mario->y() + 15)
			new FireBall(QPoint(x() - 2, y() + 6), LEFT, UP);
		else if (x() < mario->x() && y() <= mario->y() + 15)
			new FireBall(QPoint(x() + 4, y() + 10), RIGHT, DOWN);
		else if (x() < mario->x() && y() > mario->y() + 15)
			new FireBall(QPoint(x() + 4, y() + 6), RIGHT, UP);
		
		number_fireball++;
	}
}

void PiranhaPlant::smash()
{
	_smash = true;
}