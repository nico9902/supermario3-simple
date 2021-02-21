#include "SecretBox.h"
#include "Sprites.h"
#include "Mario.h"
#include "Mushroom.h"
#include "SuperLeaf.h"
#include "CoinSpawnable.h"
#include "Sounds.h"
#include "Game.h"
#include "Scoring.h"
#include "KoopaTroopa.h"

SecretBox::SecretBox(QPoint position, spawnable_t spawnable) : Inert()
{
	// attributes
	active = true;
	content = spawnable;
	mario = 0;

	// counters
	hit_counter = -1;
	animation_counter = 0;

	// textures
	texture_active[0] = Sprites::instance()->get("secret-box-0");
	texture_active[1] = Sprites::instance()->get("secret-box-1");
	texture_active[2] = Sprites::instance()->get("secret-box-2");
	texture_active[3] = Sprites::instance()->get("secret-box-3");
	texture_inactive  = Sprites::instance()->get("secret-box-inactive");

	// set texture and correct y-coordinate w.r.t. texture height
	setPixmap(texture_active[0]);
	setPos(position-QPoint(0, pixmap().height()));

	setZValue(3);
}

void SecretBox::animate()
{
	if(active)
		setPixmap(texture_active[(animation_counter++/20)%4]);
	else
		setPixmap(texture_inactive);
}

// @override
void SecretBox::advance()
{
	if(hit_counter >= 0)
	{
		
		// raising phase
		if(hit_counter < 12)
		{
			setY(y()-1);
			hit_counter++;
		}
		// falling phase
		else if(hit_counter >= 12 && hit_counter < 24)
		{
			setY(y()+1);
			hit_counter++;
		}
		// spawn phase
		else
		{
			hit_counter = -1;
			spawn();
		}
	}
}

void SecretBox::hit(Object *what, Direction fromDir)
{
	// do nothing if not active
	if(!active)
		return;

	mario = dynamic_cast<Mario*>(what);
	if((mario && fromDir == DOWN) || (dynamic_cast<KoopaTroopa*>(what) &&
		dynamic_cast<KoopaTroopa*>(what)->isKicked() && content == LEAF
		&& (fromDir == LEFT || fromDir == RIGHT)))
	{
		// start hit-and-spawn
		hit_counter = 0;

		// disable box
		active = false;

		// play box hit sound
		Sounds::instance()->play("bump");

		// spawn coin NOW, other spawnables will be spawn later
		if (content == COIN)
		{
			new CoinSpawnable(QPoint(x(), y()));

			// score increases
			Game::instance()->scorechanged(100);
			new Scoring(QPoint(x(), y() - 16));

			// coins increase
			Game::instance()->coinpointschanged(1);
		}
	}
}

// utility method
void SecretBox::spawn()
{
	mario = Game::instance()->getMario();
	if(content == FLOWER)
	{
		if(mario->isBig())
			;   // spawn flower object ( super leaf)
		else
			new Mushroom(QPoint(x(), y()));
	}		
	else if(content == LEAF)
	{
		if(mario->isBig())
			new SuperLeaf(QPoint(x(), y()));	// spawn leaf object
		else
			new Mushroom(QPoint(x(), y()), true);
	}
	else if(content == LIFE)
		new Mushroom(QPoint(x(), y()), false);
}
