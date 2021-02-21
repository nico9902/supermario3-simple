#include "FireBall.h"
#include "Sprites.h"
#include "Mario.h"
#include "Game.h"
#include "Enemy.h"
#include "Goomba.h"
#include "PiranhaPlant.h"
#include "Sounds.h"

FireBall::FireBall(QPoint position, Direction dir, Direction _orentation) : Entity()
{
	//animation texture
	texture[0] = Sprites::instance()->get1("fireball-0");
	texture[1] = Sprites::instance()->get1("fireball-1");
	texture[2] = Sprites::instance()->get1("fireball-2");
	texture[3] = Sprites::instance()->get1("fireball-3");
	texture_crash[0] = Sprites::instance()->get1("fireball-crush-0");
	texture_crash[1] = Sprites::instance()->get1("fireball-crush-1");
	texture_crash[2] = Sprites::instance()->get1("fireball-crush-2");

	setPixmap(texture[0]);
	
	setPos(position - QPoint(0, pixmap().height()));
	
	// set attributes
	orientation = _orentation;

	// fireball is always moving horizontally (slowly)
	moving = true;
	setDirection(dir);
	slow = false;
	crushed = false;
	crushed_counter = -1;
	crushed_duration = 16;

	// fireball is overlaid on top of all other objects
	setZValue(4);
}

void FireBall::animate() 
{
	animation_counter++;

	if (moving && !crushed)
		setPixmap(texture[(animation_counter / 10) % 4]);
	else if (crushed)
		setPixmap(texture_crash[(animation_counter) % 3]);
}

void FireBall::advance()
{
	Mario* mario = Game::instance()->getMario();
	
	// spawned Fireball based on PiranhaPlant orentation
	if (moving)
	{
		if (orientation == UP)
		{
			setY(y() - moving_speed);
			if (dir == LEFT)
				setX(x() - moving_speed);
			else
				setX(x() + moving_speed);
		}
		else if (orientation == DOWN)
		{
			setY(y() + moving_speed);
			if (dir == LEFT)
				setX(x() - moving_speed);
			else
				setX(x() + moving_speed);
		}
	}

    // Fireball crush
	if (crushed)
	{
		crushed_counter++;

		if (crushed_counter > crushed_duration)
		{
			crushed_counter = -1;
			crushed = false;
		}
	}
}

void FireBall::hit(Object *what, Direction fromDir) 
{
	Object::hit(what, fromDir);
	
	// Fireball hit inert object
	if (dynamic_cast<Inert *>(what)) 
	{
		Sounds::instance()->play("bump");
		
		// fireball crush
		crush();
	}

    // Fireball hit Mario
	// if Mario is big Mario return small,
	// else Mario dies
	if (dynamic_cast<Mario*>(what))
	{
		if (dynamic_cast<Mario*>(what)->isBig())
		{
			if (dynamic_cast<Mario*>(what)->isRacoon())
			{
				dynamic_cast<Mario*>(what)->setRacoon2Big(0);
				Game::instance()->setFreezed(true);
				if (dynamic_cast<Mario*>(what)->isFly())
				{
					dynamic_cast<Mario*>(what)->setFly(false);
					dynamic_cast<Mario*>(what)->setPreFly(false);
					dynamic_cast<Mario*>(what)->setJump(false);
				}
			}
			else
			{
				dynamic_cast<Mario*>(what)->setBig(false);
				dynamic_cast<Mario*>(what)->setTransparent(true);
			}
			dynamic_cast<Mario*>(what)->setMoving(false);
		}
		else
		{
			if (!dynamic_cast<Mario*>(what)->isTransparent())
			{
				dynamic_cast<Mario*>(what)->setDying(true);
				moving = false;

				// stop level music
				Game::instance()->stopMusic();

				// play death music
				Sounds::instance()->play("death");
			}
		}
	}
}

void FireBall::crush()
{
	crushed = true;
}

void FireBall::die()
{
	// if fireball leave the scene it disappear
	setVisible(false);
	dying = true;
	
	Entity::die();
}