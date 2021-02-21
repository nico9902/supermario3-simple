#include "KoopaTroopa.h"
#include "KoopaTroopa.h"
#include "Sprites.h"
#include "Sounds.h"
#include "Mario.h"
#include "SecretBox.h"
#include "Scoring.h"
#include "Game.h"

KoopaTroopa::KoopaTroopa(QPoint position, Direction direction, bool isGreen, bool _walk_on_brick)
{
	// set attributes
	green = isGreen;
	dir = direction;
	slow = true;
	reanimate = false;
	reanimate_fast = false;
	kicked = false;
	grabbed = false;
	walk_on_brick = _walk_on_brick;

	// animation divisor
	animation_div = 8;

	// durations
	death_duration = 60;
	reanimate_duration = 240*4;

	// animation counters
	reanimate_counter = -1;
	count_moving = 0;

	// textures
	texture_walk_left[0][0] = Sprites::instance()->get("KoopaTroopa-walk-0");
	texture_walk_left[0][1] = Sprites::instance()->get("KoopaTroopa-walk-1");
	texture_walk_right[0][0] = texture_walk_left[0][0].transformed(QTransform().scale(-1, 1));
	texture_walk_right[0][1] = texture_walk_left[0][1].transformed(QTransform().scale(-1, 1));
	texture_walk_left[1][0] = Sprites::instance()->get("KoopaTroopa-walk-green-0");
	texture_walk_left[1][1] = Sprites::instance()->get("KoopaTroopa-walk-green-1");
	texture_walk_right[1][0] = texture_walk_left[1][0].transformed(QTransform().scale(-1, 1));
	texture_walk_right[1][1] = texture_walk_left[1][1].transformed(QTransform().scale(-1, 1));
	texture_smashed[0][0] = Sprites::instance()->get("KoopaTroopa-smashed-0");
	texture_smashed[0][1] = Sprites::instance()->get("KoopaTroopa-smashed-1");
	texture_kicked[0][0] = Sprites::instance()->get("KoopaTroopa-kicked-0");
	texture_kicked[0][1] = Sprites::instance()->get("KoopaTroopa-kicked-1");
	texture_kicked[0][2] = Sprites::instance()->get("KoopaTroopa-kicked-2");
	texture_kicked[0][3] = Sprites::instance()->get("KoopaTroopa-kicked-3");
	texture_smashed[1][0] = Sprites::instance()->get1("KoopaTroopa-smashed-green-0");
	texture_smashed[1][1] = Sprites::instance()->get1("KoopaTroopa-smashed-green-1");
	texture_kicked[1][0] = Sprites::instance()->get1("KoopaTroopa-kicked-green-0");
	texture_kicked[1][1] = Sprites::instance()->get1("KoopaTroopa-kicked-green-1");
	texture_kicked[1][2] = Sprites::instance()->get1("KoopaTroopa-kicked-green-2");
	texture_kicked[1][3] = Sprites::instance()->get1("KoopaTroopa-kicked-green-3");

	// set texture and correct y-coordinate w.r.t. texture height
	setPixmap(texture_walk_left[green][0]);
	setPos(position - QPoint(0, pixmap().height()));

	setZValue(3);
}

void KoopaTroopa::advance()
{
	Mario* mario = Game::instance()->getMario();

	if (green)
	{
		// KoopaTroopa green start to move when Mario
		// is near to it
		if (x() < mario->x() + 300)
		{
			if (count_moving == 0)
			{
				setFreezed(false);
				count_moving++;
			}
		}
		else
		{
			if (count_moving == 0)
				setFreezed(true);
		}
	}

	// never fall from walkable object
	if (walkable_object && !kicked && !green)
	{
		int delta = dir == RIGHT ? 8 : -8;
		setX(x() + delta);
		if (!touchingDirection(walkable_object))
			dir = inverse(dir);
		setX(x() - delta);
	}

	if (reanimate || reanimate_fast)
	{
		// reanimate_counter increase
		reanimate_counter++;
		// start KoopaTroopa reanimate
		startReanimed();

		// shift of KoopaTroopa's shell during an advanced stage of reanimate
		if (reanimate_counter > (reanimate_duration / 3))
		{
			if (reanimate_counter != 0) {
				if (reanimate_counter % 2 == 0)
					setX(x() + 1);
				else
					setX(x() - 1);
			}
		}

		// animation is more faster in the final stage of reviving
		if (reanimate_counter > (reanimate_duration / 2 + reanimate_duration / 4))
		{
			animation_div = 6;
		}
		if (reanimate_counter > (reanimate_duration / 2 + reanimate_duration / 3))
		{
			animation_div = 4;
		}
	}

    // Mario kick KoopaTroopa
	if (kicked)
	{
		moving = true;
		slow = false;
		moving_speed = 3;
		reanimate = false;
		reanimate_fast = false;
		reanimate_counter = -1;
	}

	Mario *mario_obj = Game::instance()->getMario();
	
	// Mario grab KoopaTroopa
	if(grabbed && !mario_obj->iskick())
	{
		int delta = 12;
		if (mario_obj->getDir() == LEFT)
			setX(mario_obj->x() - delta);

		if (mario_obj->getDir() == RIGHT)
		{
			if (!mario_obj->isRacoon())
				setX(mario_obj->x() + delta);
			else
				setX(mario_obj->x() + 18);
		}
		if (mario_obj->isBig())
			setY(mario_obj->y() + 6);
		else
			setY(mario_obj->y());
	}
	else if (grabbed && mario_obj->iskick())
	{
		kicked = true;
		grabbed = false;
		if (mario_obj->getDir() == RIGHT)
		{
			dir = RIGHT;
			if (mario_obj->isBig())
				setX(x() + 6);
			else
				setX(x() + 16);
		}
		else
		{
			dir = LEFT;
			if (mario_obj->isBig())
				setX(x() - 6);
			else
				setX(x() - 16);
		}
	}

    // KoopaTroopa is smashed
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

	Entity::advance();
}

void KoopaTroopa::animate()
{
	Entity::animate();

	// save current texture height (for later correction)
	int prev_h = boundingRect().height();

	// set the proper texture
	if (dying)
		setPixmap(texture_smashed[green][0]);
	else if (moving && dir == LEFT && !kicked)
		setPixmap(texture_walk_left[green][(animation_counter / animation_div) % 2]);
	else if (moving && dir == RIGHT && !kicked)
		setPixmap(texture_walk_right[green][(animation_counter / animation_div) % 2]);
	else if (reanimate)
		setPixmap(texture_smashed[green][0]);
	else if (reanimate_fast)
		setPixmap(texture_smashed[green][(animation_counter / animation_div) % 2]);
	else if (kicked)
		setPixmap(texture_kicked[green][(animation_counter / animation_div) % 4]);

	// correct y position if texture height changed
	int cur_h = boundingRect().height();
	if (prev_h != cur_h)
		setY(y() - (cur_h - prev_h));
}

void KoopaTroopa::hit(Object *what, Direction fromDir)
{
	Object::hit(what, fromDir);

	if ((dynamic_cast<Inert*>(what) || dynamic_cast<Enemy*>(what))
		&& (fromDir == LEFT || fromDir == RIGHT))
	{
		if(!(dynamic_cast<Enemy*>(what) && kicked))
			dir = inverse(dir);
		else
		{
			if(!kicked)
				dynamic_cast<Enemy*>(what)->hurt();
			else
				dynamic_cast<Enemy*>(what)->smash();
		}
	}

	if (dynamic_cast<Mario*>(what) && (fromDir == LEFT || fromDir == RIGHT)
		&& (isReanimed() || isReanimed_Fast()))
	{
		if (!dynamic_cast<Mario*>(what)->isPregrab())
		{
			dynamic_cast<Mario*>(what)->setKick(true);
			kicked = true;

			// score increases
			Game::instance()->scorechanged(100);
			new Scoring(QPoint(x(), y() - 16));

			if (fromDir == LEFT)
			{
				dir = RIGHT;
				if (dynamic_cast<Mario*>(what)->isBig())
					setX(x() + 6);
				else
					setX(x() + 16);
			}
			else
			{
				dir = LEFT;
				if (dynamic_cast<Mario*>(what)->isBig())
					setX(x() - 6);
				else
					setX(x() - 16);
			}
		}
	}

	if (dynamic_cast<Mario*>(what) && fromDir == UP
		&& kicked)
	{
		kicked = false;
		reanimate = true;
		moving = false;
		dynamic_cast<Mario*>(what)->bounce();
	}

}

void KoopaTroopa::hurt()
{
	Sounds::instance()->play("stomp");
	reanimate = true;
	moving = false;
}

void KoopaTroopa::startReanimed()
{	
	// reanimate without paws
	if (reanimate_counter > (reanimate_duration / 2))
	{
		reanimate = false;
		reanimate_fast = true;
	}
	
	// reanimate with paws
	if (reanimate_counter > reanimate_duration)
	{
		reanimate_fast = false;
		moving = true;
		reanimate_counter = -1;
		animation_div = 8;
		if (grabbed)
		{
			grabbed = false;
			setX(x() + 12);
		}
	}
}

void KoopaTroopa::smash()
{
	_smash = true;
}

QPainterPath KoopaTroopa::shape() const 
{
	QPainterPath path;

	path.addRect(2, boundingRect().top(), boundingRect().width() - 5, boundingRect().height());

	return path;
}