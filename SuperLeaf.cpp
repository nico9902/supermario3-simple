#include "SuperLeaf.h"
#include "Mario.h"
#include "Sounds.h"
#include "Sprites.h"
#include "Game.h"
#include "Scoring.h"

SuperLeaf::SuperLeaf(QPoint position) : Collectable(position)
{
	// set attributes
	number_jump = 0;

	// set texture and position
	setPixmap(Sprites::instance()->get("leaf"));
	setPos(position);

	// play leaf sound
	//Sounds::instance()->play("spawn");

}

void SuperLeaf::animate()
{
	Entity::animate();

	// if leaf fully emerges from spawn position, 
	// start falling and become collidable
	if (y() == spawned_position.y() - pixmap().height())
	{
		collidable = true;
		slow = true;
		moving = false;
		if (number_jump == 0)
		{
			jumping_duration = 4 * 16;
			startJumping();
			number_jump++;
		}
	}
}

void SuperLeaf::advance()
{
	if (falling)
	{
		setX(x() + moving_speed);
		setY(y() + moving_speed);
	}

	
	Entity::advance();
}

void SuperLeaf::hit(Object *what, Direction fromDir)
{
	Object::hit(what, fromDir);

	// if hit by Mario, Mario eats leaf and leaf dies
	Mario* mario = dynamic_cast<Mario*>(what);
	if (mario)
	{
		mario->marioRacoon();
		die();

		// score increases
		Game::instance()->scorechanged(1000);
		new Scoring(QPoint(Game::instance()->getMario()->x(), Game::instance()->getMario()->y() - 16), 5);

		return;
	}
}