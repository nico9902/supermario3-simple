#include "Goomba.h"
#include "Sprites.h"
#include "Game.h"
#include "Mario.h"
#include "Sounds.h"

Goomba::Goomba(QPoint position, Direction direction, bool isRed, bool _moving, int _count_moving) : Enemy()
{
	// set attributes
	red  = isRed;
	dir = direction;
	slow = true;
	moving = _moving;
	count_moving = _count_moving;

	// animation divisor
	animation_div = 8;

	// durations
	death_duration = 60;

	// textures
	texture_walk_right[0][0]    = Sprites::instance()->get("goomba-brown-walk-0");
	texture_walk_right[0][1]    = Sprites::instance()->get("goomba-brown-walk-1");
	texture_walk_right[1][0]    = Sprites::instance()->get("goomba-red-walk-0");
	texture_walk_right[1][1]    = Sprites::instance()->get("goomba-red-walk-1");
	texture_dying[0]    = Sprites::instance()->get("goomba-brown-smashed");
	texture_dying[1]    = Sprites::instance()->get("goomba-red-smashed");
	texture_smash[0]    = texture_walk_right[0][0].transformed(QTransform().scale(1, -1));

	// set texture and correct y-coordinate w.r.t. texture height
	setPixmap(texture_walk_right[red][0]);
	setPos(position-QPoint(0, pixmap().height()));

	setZValue(3);
}

void Goomba::advance()
{
	// never fall from walkable object
	if(red && walkable_object)
	{
		int delta = dir == RIGHT ? 16 : -16;
		setX(x() + delta);
		if(!touchingDirection(walkable_object))
			dir = inverse(dir);
		setX(x() - delta);
	}

	Mario* mario = Game::instance()->getMario();
	
	// if Goomba is initially stopped
	// it moves only if Mario is near to it 
	if (!moving && x() < mario->x() + 200)
	{
		if (count_moving == 0)
		{
			moving = true;
			count_moving++;
		}
	}

    // Goomba is smashed
	if (_smash)
	{
		if (smash_counter == -1)
		{
			jumping_duration = 3 * 16;
			startJumping();
			smash_counter++;
			dying = true;
		}
	}

    // Goomba dies
	if (dead)
		smash_counter = -1;

	Entity::advance();
}

void Goomba::animate()
{
	Entity::animate();

	// save current texture height (for later correction)
	int prev_h = boundingRect().height();

	// set the proper texture
	if(dying && !_smash)
		setPixmap(texture_dying[red]);
	else if(moving && !_smash)
		setPixmap(texture_walk_right[red][(animation_counter/animation_div)%2]);
	else if (_smash)
		setPixmap(texture_smash[0]);

	// correct y position if texture height changed
	int cur_h= boundingRect().height();
	if(prev_h != cur_h)
		setY(y()-(cur_h-prev_h));
}

void Goomba::hit(Object *what, Direction fromDir)
{
	Object::hit(what, fromDir);

	if( (dynamic_cast<Inert*>(what) || dynamic_cast<Enemy*>(what))
		&& (fromDir == LEFT || fromDir == RIGHT))
		dir = inverse(dir);
}

void Goomba::hurt()
{
	Sounds::instance()->play("stomp");
	dying = true;
	moving = false;
}


void Goomba::smash()
{
	_smash = true;
}
