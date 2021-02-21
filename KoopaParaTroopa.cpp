#include "KoopaParaTroopa.h"
#include "Sprites.h"
#include "Sounds.h"
#include "Game.h"
#include "KoopaTroopa.h"

KoopaParaTroopa::KoopaParaTroopa(QPoint position, Wing* _wing, Direction direction) : Enemy()
{
	// set attributes
	dir = direction;
	slow = true;
	fly = true;
	start_fly = false;
	moving = false;
	wing = _wing;
	fly_counter = -1;
	number_jumps = 0;
	count_moving = 0;

	// animation divisor
	animation_div = 8;

	// speeds
	jumping_speed = 2;

	// durations
	death_duration = 60;
	fly_duration = 8 * 16;

	// textures
	texture_walk_left[0] = Sprites::instance()->get("KoopaTroopa-walk-green-0");
	texture_walk_left[1] = Sprites::instance()->get("KoopaTroopa-walk-green-1");
	texture_walk_right[0] = texture_walk_left[0].transformed(QTransform().scale(-1, 1));
	texture_walk_right[1] = texture_walk_left[1].transformed(QTransform().scale(-1, 1));
	texture_smashed[0] = Sprites::instance()->get1("KoopaTroopa-smashed-green-0");
	texture_smashed[1] = Sprites::instance()->get1("KoopaTroopa-smashed-green-1");
	texture_kicked[0] = Sprites::instance()->get1("KoopaTroopa-kicked-green-0");
	texture_kicked[1] = Sprites::instance()->get1("KoopaTroopa-kicked-green-1");
	texture_kicked[2] = Sprites::instance()->get1("KoopaTroopa-kicked-green-2");
	texture_kicked[3] = Sprites::instance()->get1("KoopaTroopa-kicked-green-3");

	// set texture and correct y-coordinate w.r.t. texture height
	setPixmap(texture_walk_right[0]);
	setPos(position - QPoint(0, pixmap().height()));

	setZValue(3);
}

void KoopaParaTroopa::advance()
{
	// wing changes its texture according to the direction of
	// KoopaparaTroopa
	wing->setDirKoopa(dir);

	// if Mario is near to KoopaParaTroopa, it start to move
	Mario* mario = Game::instance()->getMario();
	if (x() < mario->x() + 250)
	{
		if (count_moving == 0)
		{
			start_fly = true;
			moving = true;
			if (mario->x() <= x())
				dir == LEFT;
			else
				dir == RIGHT;
			count_moving++;
		}
	}

	// if is flying, it start a small Jump
	// else wings disappear
	if (fly)
	{
		if (start_fly && freezed == false)
		{
			fly_counter++;
			smallJump();
		}

		// wing position changes according to direction of KoopaParaTroopa
		if (dir == LEFT)
			wing->setPos(x() + 10, y() + 2);
		else
			wing->setPos(x() - 2, y() + 2);
	}
	else
	{
		wing->setVisible(false);
		wing->setDying(true);
		
		setVisible(false);
		Game::instance()->getScene()->removeItem(this);
		new KoopaTroopa(QPoint(x(), y() + 28), dir, true);
	}

	// KoopaParaTroopa jump
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

	// KoopaParaTroopa fall
	if (falling)
	{
		if (dir == LEFT)
			setX(x() - moving_speed);
		else
			setX(x() + moving_speed);
	}

	// KoopaParaTroopa smash ( for example by tail of Mario Racoon)
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

void KoopaParaTroopa::animate()
{
	Entity::animate();

	// save current texture height (for later correction)
	int prev_h = boundingRect().height();

	// set the proper texture
	if (dying && !_smash)
		setPixmap(texture_smashed[0]);
	else if (moving && dir == RIGHT && !_smash)
		setPixmap(texture_walk_right[(animation_counter / animation_div) % 2]);
	else if (moving && dir == LEFT && !_smash)
		setPixmap(texture_walk_left[(animation_counter / animation_div) % 2]);
	else if (jumping && !_smash)
		setPixmap(texture_walk_right[(animation_counter / animation_div) % 2]);
	else if (_smash)
		setPixmap(texture_walk_right[0].transformed(QTransform().scale(1, -1)));

	// correct y position if texture height changed
	int cur_h = boundingRect().height();
	if (prev_h != cur_h)
		setY(y() - (cur_h - prev_h));
}

void KoopaParaTroopa::hit(Object *what, Direction fromDir)
{
	Object::hit(what, fromDir);

	if ((dynamic_cast<Inert*>(what) || dynamic_cast<Enemy*>(what))
		&& (fromDir == LEFT || fromDir == RIGHT))
		dir = inverse(dir);
}

void KoopaParaTroopa::hurt()
{
	Sounds::instance()->play("stomp");

	// if is flying, KoopaParaTroopa end fly and fall
	if (fly)
	{
		fly = false;
		if (jumping)
			endJumping();
		fly_counter = -1;
		start_fly = false;
	}
}

void KoopaParaTroopa::smallJump()
{
	if (fly_counter >= 0)
	{
		if (!falling)
		{
			// start a small jump
			jumping_duration = 2 * 16 - 6;
			falling = false;
			jumping = false;
			startJumping();
		}
	}
	else if (fly_counter > fly_duration)
	{
		fly_counter = 0;
	}
}

void KoopaParaTroopa::die()
{
	// if KoopaParaTroopa leave the scene, KoopaParaTroopa died and Wings disappear
	wing->setVisible(false);
	wing->setDying(true);

	Entity::die();
}

void KoopaParaTroopa::smash()
{
	_smash = true;
}