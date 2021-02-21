#include "ParaGoomba.h"
#include "Sprites.h"
#include "Sounds.h"
#include "Game.h"

ParaGoomba::ParaGoomba(QPoint position, Wing* _wing_left, Wing* _wing_right,Direction direction) : Enemy()
{
	// set attributes
	dir = direction;
	slow = true;
	fly = true;
	start_fly = false;
	moving = false;
	wing_left = _wing_left;
	wing_right = _wing_right;
	fly_counter = -1;
	number_jumps = 0;
	invdir_counter = -1;
	count_moving = 0;

	// animation divisor
	animation_div = 8;

	// speeds
	jumping_speed = 2;

	// durations
	death_duration = 60;
	fly_duration = 8 * 16;
	invdir_duration = 8*16;

	// textures
	texture_walk_right[0] = Sprites::instance()->get("goomba-red-walk-0");
	texture_walk_right[1] = Sprites::instance()->get("goomba-red-walk-1");;
	texture_smashed = Sprites::instance()->get("goomba-red-smashed");

	// set texture and correct y-coordinate w.r.t. texture height
	setPixmap(texture_walk_right[0]);
	setPos(position - QPoint(0, pixmap().height()));

	setZValue(3);
}

void ParaGoomba::advance()
{
	Mario* mario = Game::instance()->getMario();

	if (x() < mario->x() + 150)
	{
		if (count_moving == 0)
		{
			start_fly = true;
			moving = true;
			count_moving++;
		}
	}

	// never fall from walkable object
	if (walkable_object && !start_fly)
	{
		int delta = dir == RIGHT ? 16 : -16;
		setX(x() + delta);
		if (!touchingDirection(walkable_object))
			dir = inverse(dir);
		setX(x() - delta);
	}

	if (fly)
	{
		if(start_fly && freezed == false)
		{
			fly_counter++;
			smallJump();
		}

		wing_left->setPos(x() - 2, y() - 6);
		wing_right->setPos(x() + 10, y() - 6);
	}
	else
	{
		wing_left->setVisible(false);
		wing_right->setVisible(false);
		wing_left->setDying(true);
		wing_right->setDying(true);
	}

	if (jumping)
	{
		prevPos = pos();

		// move upwards
		setY(y() - jumping_speed);
		if (dir == LEFT)
			setX(x() - moving_speed);
		else
			setX(x() + moving_speed);

		// increase jump frame count
		jump_counter += jumping_speed;

		// end jumping when frame count reaches the defined limit
		if (jump_counter > jumping_duration)
			endJumping();

		solveCollisions();
	}

	if (falling)
	{
		if (dir == LEFT)
			setX(x() - moving_speed);
		else
			setX(x() + moving_speed);
	}

	if (x() < (mario->x() + 100) && x() > mario->x() && fly)
	{
		invdir_counter++;

		if (invdir_counter > invdir_duration)
		{
			dir = LEFT;
			invdir_counter = -1;
		}
	}
	else if (x() > (mario->x() - 116) && x() < mario->x() && fly)
	{
		invdir_counter++;

		if (invdir_counter > invdir_duration)
		{
			dir = RIGHT;
			invdir_counter = -1;
		}
	}

	if (_smash)
	{
		if (smash_counter == -1)
		{
			jumping_duration = 3 * 16;
			startJumping();
			smash_counter++;
			dying = true;
			fly = false;
		}
	}

	Entity::advance();
}

void ParaGoomba::animate()
{
	Entity::animate();

	// save current texture height (for later correction)
	int prev_h = boundingRect().height();

	// set the proper texture
	if (dying && !_smash)
		setPixmap(texture_smashed);
	else if (moving && !_smash)
		setPixmap(texture_walk_right[(animation_counter / animation_div) % 2]);
	else if (jumping && !_smash)
		setPixmap(texture_walk_right[(animation_counter / animation_div) % 2]);
	else if (_smash)
		setPixmap(texture_walk_right[0].transformed(QTransform().scale(1, -1)));

	// correct y position if texture height changed
	int cur_h = boundingRect().height();
	if (prev_h != cur_h)
		setY(y() - (cur_h - prev_h));
}

void ParaGoomba::hit(Object *what, Direction fromDir)
{
	Object::hit(what, fromDir);

	if ((dynamic_cast<Inert*>(what) || dynamic_cast<Enemy*>(what))
		&& (fromDir == LEFT || fromDir == RIGHT))
		dir = inverse(dir);

	if (dynamic_cast<Mario*>(what))
		fly_counter = -1;
}

void ParaGoomba::hurt()
{
	Sounds::instance()->play("stomp");

	if (fly)
	{
		fly = false;
		if (jumping)
			endJumping();
	}
	else
	{
		dying = true;
		moving = false;
	}
}

void ParaGoomba::smallJump()
{
	if (fly_counter >= 0 && fly_counter < (fly_duration / 16))
	{
		if (number_jumps < 1)
		{
			// start a small jump
			jumping_duration = 8;
			falling = false;
			jumping = false;
			startJumping();
			number_jumps++;
		}
	}
	else if (fly_counter >= (fly_duration / 16) && fly_counter < (fly_duration / 8))
	{
		if (number_jumps < 2)
		{
			// start a small jump
			jumping_duration = 8;
			falling = false;
			jumping = false;
			startJumping();
			number_jumps++;
		}
	}
	else if (fly_counter >= (fly_duration / 8) && fly_counter < (fly_duration / 4))
	{
		if (number_jumps < 3)
		{
			// start a small jump
			jumping_duration = 8;
			falling = false;
			jumping = false;
			startJumping();
			number_jumps++;
		}
	}
	else if (fly_counter >= (fly_duration / 4) && fly_counter < (fly_duration / 2))
	{
		if (number_jumps < 4)
		{
			// start a jump
			jumping_duration = 14 * 2;
			falling = false;
			jumping = false;
			startJumping();
			number_jumps++;
		}
	}
	else if (fly_counter > fly_duration)
	{
		number_jumps = 0;
		fly_counter = 0;
	}
}

void ParaGoomba::die()
{
	// if ParaGoomba leave the scene, ParaGoomba died and Wings disappear
	wing_left->setVisible(false);
	wing_right->setVisible(false);
	wing_left->setDying(true);
	wing_right->setDying(true);

	Entity::die();
}

void ParaGoomba::smash()
{
	_smash = true;
}