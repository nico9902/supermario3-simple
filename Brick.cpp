#include "Brick.h"
#include "BrickDebris.h"
#include "Enemy.h"
#include "Game.h"
#include "Mario.h"
#include "ParaGoomba.h"
#include "KoopaTroopa.h"
#include "Sprites.h"
#include "Sounds.h"
#include "SwitchBlock.h"


Brick::Brick(QPoint position, bool _container) : Inert()
{
	// set attributes
	hitted = false;
	broken = false;
	inactive = false;
	container = _container;
	hit_counter = 0;
	animation_counter = -1;
	animation_div = 10;

	// textures
	texture[0] = Sprites::instance()->get1("brick-0");
	texture[1] = Sprites::instance()->get1("brick-1");
	texture[2] = Sprites::instance()->get1("brick-2");
	texture[3] = Sprites::instance()->get1("brick-3");
	texture_inactive = Sprites::instance()->get("secret-box-inactive");

    // set position
	setPos(position);
	
	// set pixmap
	setPixmap(texture[0]);

	setZValue(2);
}

// manage collisions with Mario
void Brick::advance()
{
	// return Mario from the Game
	Mario* mario = Game::instance()->getMario();

	// do nothing if brick is not visible
	if (this->isVisible() == 0)
		return;

	// hit by Mario: move upwards and downwards
	if (hitted && !inactive)
	{
		if (hit_counter < 10)
			setY(y() - 1);
		else if (hit_counter < 20)
			setY(y() + 1);

		hit_counter++;

		if (hit_counter >= 20)
		{
			hitted = false;
			hit_counter = 0;
			if (container)
			{
				new SwitchBlock(QPoint(x(), y() - 16));
				inactive = true;
			}
		}
	}

	// hit by Mario Big: is broken
	else if (broken)
	{
		// brick is removed by scene
		setVisible(false);
		Game::instance()->getScene()->removeItem(this);

		// spawn debris
		new BrickDebris(QPoint(x(), y() - 15), LEFT);
		new BrickDebris(QPoint(x() + pixmap().width(), y() - 15), RIGHT);
		new BrickDebris(QPoint(x() - 5, y() - 5), LEFT);
		new BrickDebris(QPoint(x() + pixmap().width() + 5, y() - 5), RIGHT);
	}
}

void Brick::animate()
{
	animation_counter++;
	if ((!hitted && !broken) || (hitted && !broken))
		setPixmap(texture[(animation_counter / animation_div) % 4]);
	if (inactive)
		setPixmap(texture_inactive);
}

void Brick::hit(Object *what, Direction fromDir)
{
	Mario* mario = dynamic_cast<Mario*>(what);
	
	// hit by Mario from bottom
	// if brick don't contain switch block,
	// Mario Big breaks brick
	if (mario && fromDir == DOWN)
	{
		if (mario->isBig())
		{
			//QSound::play(":/sounds/block-break.wav");
			if (!container)
				broken = true;
			else
				hitted = true;
		}
		else
		{
			//QSound::play(":/sounds/block-hit.wav");
			hitted = true;
			hit_counter = 0;
		}
	}

	if (mario && (fromDir == LEFT || fromDir == RIGHT))
	{
		// wheter Mario Racoon hit brick whit tail,
		// if brick contain switch block it is spawned, 
		// else brick is broken
		if (mario->isRacoon() && mario->isRound())
		{
			if (!container)
				broken = true;
			else
				hitted = true;
		}
	}

	if (dynamic_cast<KoopaTroopa*>(what) && dynamic_cast<KoopaTroopa*>(what)->isKicked()
		&& (fromDir == LEFT || fromDir == RIGHT))
	{
		// wheter KoopaTroopa's shell hit brick whit tail,
		// if brick contain switch block it is spawned, 
		// else brick is broken
		if (!container)
			broken = true;
		else
			hitted = true;
	}
}

