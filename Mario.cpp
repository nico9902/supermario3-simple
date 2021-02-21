#include "Mario.h"
#include "Game.h"
#include "Sprites.h"
#include "Sounds.h"
#include "Enemy.h"
#include "KoopaTroopa.h"
#include "PiranhaPlant.h"
#include "VenusFireTrap.h"
#include "Scoring.h"

Mario::Mario(QPoint position, bool _goup) : Entity()
{
	// set flags
	moving  = false;
	running = false;
	big = false;
	crouch = false;
	kick = false;
	grab = false;
	pre_grab = false;
	transparent = false;
	racoon = false;
	round = false;
	pre_fly = false;
	fly = false;
	pre_come_down = false;
	come_down = false;
	go_up = _goup;
	return2scene = false;

	// set counters
	moving_start_counter = -1;
	moving_stop_counter  = -1;
	dir_change_counter = -1;
	transformation_counter = -1;
	dying_counter = -1;
	kick_counter = -1;
	transparent_counter = -1;
	big2racoon_counter = -1;
	racoon2big_counter = -1;
	round_counter = -1;
	comedown_counter = -1;
	goup_counter = -1;

	// animation divisors
	animation_div = 1;

	// durations
	jumping_duration = 4*16;
	death_duration = 10*16;
	kick_duration = 4;
	transparent_duration = 10 * 16;
	big2racoon_duration = 1 * 16;
	racoon2big_duration = 6 * 16;
	round_duration = 2 * 16;
	comedown_duration = 4 * 16;

	// textures
	texture_stand[0]      = Sprites::instance()->get("mario-small-stand");
	texture_stand[1]      = Sprites::instance()->get("mario-big-stand");
	texture_jumping[0]    = Sprites::instance()->get("mario-small-jump");
	texture_jumping[1]    = Sprites::instance()->get("mario-big-jump");
	texture_falling[0]    = Sprites::instance()->get("mario-small-fall");
	texture_falling[1]    = Sprites::instance()->get("mario-big-fall");
	texture_brake[0]      = Sprites::instance()->get("mario-small-brake");
	texture_brake[1]      = Sprites::instance()->get("mario-big-brake");
	texture_crouch		  = Sprites::instance()->get("mario-big-crouch");
	texture_walking[0][0] = Sprites::instance()->get("mario-small-walk-0");
	texture_walking[0][1] = Sprites::instance()->get("mario-small-walk-1");
	texture_walking[0][2] = Sprites::instance()->get("mario-small-walk-2");
	texture_walking[0][3] = Sprites::instance()->get("mario-small-walk-3");
	texture_walking[1][0] = Sprites::instance()->get("mario-big-walk-0");
	texture_walking[1][1] = Sprites::instance()->get("mario-big-walk-1");
	texture_walking[1][2] = Sprites::instance()->get("mario-big-walk-2");
	texture_walking[1][3] = Sprites::instance()->get("mario-big-walk-3");
	texture_small2big[0]  = Sprites::instance()->get("mario-half"); 
	texture_small2big[1]  = texture_stand[0];
	texture_small2big[2]  = Sprites::instance()->get("mario-half"); 
	texture_small2big[3]  = texture_stand[0];
	texture_small2big[4]  = Sprites::instance()->get("mario-half"); 
	texture_small2big[5]  = texture_stand[0];
	texture_small2big[6]  = Sprites::instance()->get("mario-half"); 
	texture_small2big[7]  = texture_stand[1];
	texture_small2big[8]  = Sprites::instance()->get("mario-half"); 
	texture_small2big[9]  = texture_stand[1];
	texture_small2big[10] = Sprites::instance()->get("mario-half"); 
	texture_small2big[11] = texture_stand[1];
	texture_big2small[0] = texture_stand[1];
	texture_big2small[1] = Sprites::instance()->get("mario-half");
	texture_big2small[2] = texture_stand[1];
	texture_big2small[3] = Sprites::instance()->get("mario-half");
	texture_big2small[4] = texture_stand[1];
	texture_big2small[5] = Sprites::instance()->get("mario-half");
	texture_big2small[6] = texture_stand[0];
	texture_big2small[7] = Sprites::instance()->get("mario-half");
	texture_big2small[8] = texture_stand[0];
	texture_big2small[9] = Sprites::instance()->get("mario-half");
	texture_big2small[10] = texture_stand[0];
	texture_big2small[11] = Sprites::instance()->get("mario-half");
	texture_dead = Sprites::instance()->get("mario-dead");
	texture_kick[0][0] = Sprites::instance()->get("mario-small-kick");
	texture_kick[1][0] = Sprites::instance()->get("mario-big-kick");
	texture_kick[1][0].setMask(texture_kick[1][0].createMaskFromColor(QColor(41, 88, 124)));
	texture_grab[0][0] = Sprites::instance()->get("mario-small-grab-0");
	texture_grab[0][1] = Sprites::instance()->get("mario-small-grab-1");
	texture_grab[1][0] = Sprites::instance()->get("mario-big-grab-0");
	texture_grab[1][1] = Sprites::instance()->get("mario-big-grab-1");
	texture_stand_racoon = Sprites::instance()->get1("mario-racoon-stand");
	texture_stand_racoon.setMask(texture_stand_racoon.createMaskFromColor(QColor(41, 88, 124)));
	texture_walking_racoon[0] = Sprites::instance()->get1("mario-racoon-walk-0");
	texture_walking_racoon[0].setMask(texture_walking_racoon[0].createMaskFromColor(QColor(41, 88, 124)));
	texture_walking_racoon[1] = Sprites::instance()->get1("mario-racoon-walk-1");
	texture_walking_racoon[1].setMask(texture_walking_racoon[1].createMaskFromColor(QColor(41, 88, 124)));
	texture_walking_racoon[2] = Sprites::instance()->get1("mario-racoon-walk-2");
	texture_walking_racoon[2].setMask(texture_walking_racoon[2].createMaskFromColor(QColor(41, 88, 124)));
	texture_walking_racoon[3] = Sprites::instance()->get1("mario-racoon-walk-3");
	texture_walking_racoon[3].setMask(texture_walking_racoon[3].createMaskFromColor(QColor(41, 88, 124)));
	texture_jumping_racoon = Sprites::instance()->get1("mario-racoon-jump");
	texture_jumping_racoon.setMask(texture_jumping_racoon.createMaskFromColor(QColor(41, 88, 124)));
	texture_falling_racoon = Sprites::instance()->get1("mario-racoon-fall");
	texture_falling_racoon.setMask(texture_falling_racoon.createMaskFromColor(QColor(41, 88, 124)));
	texture_brake_racoon = Sprites::instance()->get1("mario-racoon-brake");
	texture_brake_racoon.setMask(texture_brake_racoon.createMaskFromColor(QColor(41, 88, 124)));
	texture_crouch_racoon = Sprites::instance()->get1("mario-racoon-crouch");
	texture_crouch_racoon.setMask(texture_crouch_racoon.createMaskFromColor(QColor(41, 88, 124)));
	texture_kick_racoon = Sprites::instance()->get1("mario-racoon-kick");
	texture_kick_racoon.setMask(texture_kick_racoon.createMaskFromColor(QColor(41, 88, 124)));
	texture_grab_racoon[0] = Sprites::instance()->get1("mario-racoon-grab-0");
	texture_grab_racoon[0].setMask(texture_grab_racoon[0].createMaskFromColor(QColor(41, 88, 124)));
	texture_grab_racoon[1] = Sprites::instance()->get1("mario-racoon-grab-1");
	texture_grab_racoon[1].setMask(texture_grab_racoon[1].createMaskFromColor(QColor(41, 88, 124)));
	texture_big2racoon[0] = Sprites::instance()->get1("fireball-crush-0");
	texture_big2racoon[1] = Sprites::instance()->get1("fireball-crush-1");
	texture_big2racoon[2] = Sprites::instance()->get1("fireball-crush-2");
	texture_round_racoon[0] = Sprites::instance()->get1("mario-racoon-round-0");
	texture_round_racoon[0].setMask(texture_round_racoon[0].createMaskFromColor(QColor(41, 88, 124)));
	texture_round_racoon[1] = Sprites::instance()->get1("mario-racoon-round-1");
	texture_round_racoon[1].setMask(texture_round_racoon[1].createMaskFromColor(QColor(41, 88, 124)));
	texture_round_racoon[2] = texture_round_racoon[1].transformed(QTransform().scale(-1, 1));
	texture_round_racoon[3] = Sprites::instance()->get1("mario-racoon-round-2");
	texture_round_racoon[3].setMask(texture_round_racoon[3].createMaskFromColor(QColor(41, 88, 124)));
	texture_pre_fly_racoon[0] = Sprites::instance()->get1("mario-racoon-pre-fly-0");
	texture_pre_fly_racoon[0].setMask(texture_pre_fly_racoon[0].createMaskFromColor(QColor(41, 88, 124)));
	texture_pre_fly_racoon[1] = Sprites::instance()->get1("mario-racoon-pre-fly-1");
	texture_pre_fly_racoon[1].setMask(texture_pre_fly_racoon[1].createMaskFromColor(QColor(41, 88, 124)));
	texture_pre_fly_racoon[2] = Sprites::instance()->get1("mario-racoon-pre-fly-2");
	texture_pre_fly_racoon[2].setMask(texture_pre_fly_racoon[2].createMaskFromColor(QColor(41, 88, 124)));
	texture_fly_racoon[0] = Sprites::instance()->get1("mario-racoon-fly-0");
	texture_fly_racoon[0].setMask(texture_fly_racoon[0].createMaskFromColor(QColor(41, 88, 124)));
	texture_fly_racoon[1] = Sprites::instance()->get1("mario-racoon-fly-1");
	texture_fly_racoon[1].setMask(texture_fly_racoon[1].createMaskFromColor(QColor(41, 88, 124)));
	texture_fly_racoon[2] = Sprites::instance()->get1("mario-racoon-fly-2");
	texture_fly_racoon[2].setMask(texture_fly_racoon[2].createMaskFromColor(QColor(41, 88, 124)));
	texture_come_down[0] = Sprites::instance()->get1("mario-comedown-small");
	texture_come_down[1] = Sprites::instance()->get1("mario-comedown-big");
	texture_come_down[2] = Sprites::instance()->get1("mario-comedown-racoon");

	// set texture and correct y-coordinate w.r.t. texture height
	setPixmap(texture_stand[big]);
	setPos(position-QPoint(0, pixmap().height()));

	// Mario is at a higher layer than other objects
	setZValue(3);
}

// modify Mario collider
QPainterPath Mario::shape() const 
{
	QPainterPath path;

	if(!(big))
		path.addRect(2, boundingRect().top(), boundingRect().width() - 5, boundingRect().height());
	else
		path.addRect(2, boundingRect().top(), boundingRect().width() - 5, boundingRect().height());
	
	return path;
}

// Mario jumps
void Mario::jump()
{
	// do nothing if already jumping
	if(jumping)
		return;
	jumping_duration = 4 * 16;
	//printf("%d\n", jumping_duration);
    // start a jump
	jumping_speed = 3;	// reset jumping speed (modified in advance())
    startJumping();

    // if jumping has started, play jump sound
    if(jumping)
        Sounds::instance()->play("jump");
}

// bounce
void Mario::bounce()
{
	// start a small jump
	jumping_duration = 1.5*16;
	falling = false;
	startJumping();
}

// @override advance() for to add vertical/horizontal acceleration
void Mario::advance()
{
	// update moving acceleration / deceleration counters
	if(moving_stop_counter >= 0)
		moving_stop_counter++;
	else
		moving_start_counter++;

	// update direction change counter
	if(dir_change_counter >= 0)
		dir_change_counter++;
	if(dir_change_counter > 20)
		dir_change_counter = -1;

	// slow down jumping speed during last iterations
	if (jump_counter >= jumping_duration - 16)
		jumping_speed = 2;

	// slow down falling speed during first iterations
	if (falling_counter <= 16)
		falling_speed = 2;
	else
		falling_speed = 3;

	// horizontal acceleration when moving starts and moving stop is not active yet
	if(moving_start_counter >=0 && moving_stop_counter <0)
	{
		if(moving_start_counter < 25)
		{
			moving_speed = moving_start_counter % 2;		// = 0.5 speed
			animation_div = 7;
		}
		if(moving_start_counter == 25)
		{
			moving_speed = 1;
			animation_div = 5;
		}
		if(moving_start_counter >  25 && moving_start_counter < 100 && running)
		{
			moving_speed = moving_start_counter % 2 + 1;	// 1.5 speed
			animation_div = 3;
		}
		if(moving_start_counter >= 100 && moving_start_counter < 150 && running)
		{
			moving_speed = 2;
			animation_div = 3;
		}
		if(moving_start_counter >= 150 && moving_start_counter < 200 && running)
		{
			moving_speed = moving_start_counter % 2 + 2;	// 2.5 speed
			animation_div = 3;

			if (racoon)
			{
				pre_fly = true;
			}
		}
		if(moving_start_counter >= 200 && running)
		{
			moving_speed = 3;
			animation_div = 3;
		}
	}
	// horizontal deceleration when moving ends
	else if(moving_start_counter >=0 && moving_stop_counter >=0)
	{
		// decelerate for the same extent of the initial acceleration (max 30 frames)
		if(moving_stop_counter < std::min(moving_start_counter, 30))
		{
			moving_speed = moving_stop_counter % 2;		// = 0.5 speed
			animation_div = 7;
			moving = true;
		}
		// finally stop
		else
		{
			moving = false;
			moving_start_counter = -1;
			moving_stop_counter = -1;
			pre_fly = false;
		}
	}

	if (dying)
	{
		// Mario became non-collidable and it stops
		collidable = false;
		moving = false;

		// The game items are freezed 
		Game::instance()->setFreezed(true);
		setFreezed(false);

		// dying_counter is increased
		dying_counter++;

		// Mario make a slow jump
		if (dying_counter > (death_duration / 3))
		{
			// slow jump
			jumping_speed = 1;
			falling_speed = 6;
			startJumping();
		}
	}

    // Mario became transparent
	if (transparent)
	{
		transparent_counter++;
		setOpacity(0.5);
		Game::instance()->setFreezed(true);

		if(transparent_counter > transparent_duration/2)
			Game::instance()->setFreezed(false);

		if (transparent_counter > transparent_duration)
		{
			transparent = false;
			transparent_counter = -1;
			setOpacity(1);
		}
	}

    // Mario kick KoopaTroopa shell
	if (kick)
	{
		kick_counter++;
		moving = false;

		if (kick_counter > kick_duration)
		{
			kick = false;
			kick_counter = -1;
		}
	}

    // Mario Racoon use tail
	if (round)
	{
		round_counter++;

		if (round_counter > round_duration)
		{
			round = false;
			round_counter = -1;
		}
	}

    // Mario Racoon fly
	if (fly)
	{
		jumping_duration = 20 * 16;
		startJumping();
	}

	if (falling)
	{
		if (fly)
		{
			fly = false;
			jumping_duration = 4 * 16;
		}
	}

    // Mario go down in Underground World
	if (y() == 34
		&& (x() >= 141 * 16 + 4 && x() <= 143 * 16 - 4))
		setPreComeDown(true);
	else
		setPreComeDown(false);

	if (come_down)
	{
		comedown_counter++;
		moving = false;
		setZValue(1);

		if(comedown_counter > comedown_duration/2)
			setY(y() + 1);

		if (comedown_counter > comedown_duration)
		{
			comedown_counter = -1;
			come_down = false;
			Game::instance()->setChangeScene(true);
		}
	}

    // Mario go up in starting World
	if (go_up)
	{
		goup_counter++;
		moving = false;
		falling = false;
		setZValue(1);
	
		if (goup_counter >  8)
		{
			setY(y() - goup_counter/4);
		}
		if (goup_counter > 14)
		{
			falling = true;
			goup_counter = -1;
			go_up = false;
			if (return2scene)
			{
				Game::instance()->setReturnScene(true);
				return2scene = false;
			}
		}
	}

	Entity::advance();
}

// @override
void Mario::endJumping()
{
	jumping_duration = 4*16;
	Entity::endJumping();
}

// start Falling
void Mario::startFalling()
{
	jumping_duration = 3 * 16;
	if (jump_counter > jumping_duration)
	{
		Entity::endJumping();
		jumping_duration = 4 * 16;
	}
}

// @override setMoving() to add horizontal acceleration
void Mario::setMoving(bool _moving)
{
	// transition move -> stop, then activate moving stop counter
	if(_moving == false && moving)
		moving_stop_counter = 0;
	// transition stop -> move, then activate moving start counter
	else if(_moving == true && !moving)
		moving_start_counter = 0;

	Entity::setMoving(_moving);
}

// @override setDirection() to avoid instant direction change
void Mario::setDirection(Direction _dir)
{
	if(_dir != dir && moving)
	{
		// reset acceleration/deceleration counters
		// @TODO: avoid instant direction change
		moving_start_counter = 0;
		moving_stop_counter = -1;

		pre_fly = false;

		dir_change_counter = 0;
	}

	// @TODO: avoid instant direction change
	Entity::setDirection(_dir);
}

void Mario::animate()
{
	Entity::animate();

	// save current texture height (for later correction)
	int prev_h = boundingRect().height();

	// set the proper texture
	if (transformation_counter >= 0)
	{
		moving = false;
		setPixmap(texture_small2big[(transformation_counter / 5) % 12]);
		transformation_counter++;
		if (transformation_counter >= 12 * 5)
		{
			transformation_counter = -1;
			Game::instance()->setFreezed(false);
		}
	}
	else if (big && crouch && big2racoon_counter < 0)
	{
		if (!racoon)
			setPixmap(texture_crouch);
		else
			setPixmap(texture_crouch_racoon);
	}
	else if (jumping && !dying && !grab && big2racoon_counter < 0 && !fly)
	{
		if (!racoon)
			setPixmap(texture_jumping[big]);
		else
			setPixmap(texture_jumping_racoon);
	}
	else if (falling && !dying && !grab && big2racoon_counter < 0)
	{
		if (!racoon)
			setPixmap(texture_falling[big]);
		else
			setPixmap(texture_falling_racoon);
	}
	else if (moving && !dying && !grab && big2racoon_counter < 0 && !pre_fly && !fly)
	{
		if (dir_change_counter > 0)
		{
			if (!racoon)
				setPixmap(texture_brake[big]);
			else
				setPixmap(texture_brake_racoon);
		}
		else
		{
			if (!racoon)
				setPixmap(texture_walking[big][(animation_counter / animation_div) % 4]);
			else
			{
				if (!round)
				{
					setPixmap(texture_walking_racoon[(animation_counter / animation_div) % 4]);
				}
			}
		}
	}
	else if (pre_fly && !dying && !fly)
		setPixmap(texture_pre_fly_racoon[(animation_counter / animation_div) % 3]);
	else if (fly && !dying)
		setPixmap(texture_fly_racoon[(animation_counter / animation_div) % 3]);
	else if (dying)
		setPixmap(texture_dead);
	else if (kick && big2racoon_counter < 0)
	{
		if (!racoon)
			setPixmap(texture_kick[big][0]);
		else
			setPixmap(texture_kick_racoon);
	}
	else if (grab && !dying && !kick && big2racoon_counter<0)
	{
		if (!racoon)
		{
			if (moving)
				setPixmap(texture_grab[big][(animation_counter / animation_div) % 2]);
			else
				setPixmap(texture_grab[big][0]);
		}
		else
		{
			if (moving)
				setPixmap(texture_grab_racoon[(animation_counter / animation_div) % 2]);
			else
				setPixmap(texture_grab_racoon[0]);
		}
	}
	else if (transparent_counter >= 0)
	{
		setPixmap(texture_big2small[(transparent_counter / 15) % 12]);
	}
	else if (big2racoon_counter >= 0)
	{
		setPixmap(texture_big2racoon[(animation_counter / animation_div) % 3]);
		big2racoon_counter++;
		if (big2racoon_counter > big2racoon_duration)
		{
			big2racoon_counter = -1;
			racoon = true;
			Game::instance()->setFreezed(false);
		}
	}
	else
	{
		if(!racoon)
			setPixmap(texture_stand[big]);
		else
			setPixmap(texture_stand_racoon);
	}

	if (racoon2big_counter >= 0)
	{
		racoon2big_counter++;
		collidable = false;
		if (racoon2big_counter >= 0 && racoon2big_counter < racoon2big_duration / 4)
		{
			setPixmap(texture_big2racoon[(animation_counter / animation_div) % 3]);
			Game::instance()->setFreezed(false);
			setFreezed(true);
		}
		else if (racoon2big_counter >= racoon2big_duration / 4 && racoon2big_counter < racoon2big_duration)
		{
			setPixmap(texture_stand[big]);
			if (racoon2big_counter % 2 == 0)
				setOpacity(0.2);
			else
				setOpacity(0.8);
		}
		else
		{
			racoon2big_counter = -1;
			racoon = false;
			setOpacity(1);
			collidable = true;
			setFreezed(false);
		}
	}

	if (round)
	{
		setPixmap(texture_round_racoon[(animation_counter / animation_div / 2) % 4]);
	}

	if (come_down || go_up)
	{
		if(!big && !racoon)
			setPixmap(texture_come_down[0]);
		else if(big && !racoon)
			setPixmap(texture_come_down[1]);
		else
			setPixmap(texture_come_down[2]);
	}
	// correct y position if texture height changed
	int cur_h= boundingRect().height();
	if(prev_h != cur_h)
		setY(y()-(cur_h-prev_h));

	// mirror the texture along the horizontal axis if needed
	if(dir == RIGHT)
		setPixmap(pixmap().transformed(QTransform().scale(-1,1)));
}

// Mario has been hit
void Mario::hit(Object *what, Direction fromDir)
{
	Object::hit(what, fromDir);

	// disable deceleration if mario hits impenetrable object
	if(dynamic_cast<Inert*>(what) && (fromDir == LEFT || fromDir == RIGHT))
		moving_start_counter = 0;

	// stop jumping if mario hits impenetrable object
	if(dynamic_cast<Inert*>(what) && fromDir == UP)
		endJumping();

    // Mario hit an enemy
	if(dynamic_cast<Enemy*>(what))
	{
		if(fromDir == DOWN && !((dynamic_cast<KoopaTroopa*>(what) &&
			(dynamic_cast<KoopaTroopa*>(what)->isReanimed() ||
				dynamic_cast<KoopaTroopa*>(what)->isReanimed_Fast()))
			|| (dynamic_cast<PiranhaPlant*>(what)
			|| (dynamic_cast<VenusFireTrap*>(what)))))
		{
			dynamic_cast<Enemy*>(what)->hurt();
			bounce();

			// score increases
			Game::instance()->scorechanged(100);
			new Scoring(QPoint(dynamic_cast<Enemy*>(what)->x(), dynamic_cast<Enemy*>(what)->y() - 16));
		}
		else if ((fromDir == LEFT || fromDir == RIGHT) && round)
		{
			dynamic_cast<Enemy*>(what)->smash();

			// score increases
			Game::instance()->scorechanged(100);
			new Scoring(QPoint(dynamic_cast<Enemy*>(what)->x(), dynamic_cast<Enemy*>(what)->y() - 16));
		}
		else
		{
			if(!(dynamic_cast<KoopaTroopa*>(what) &&
				(dynamic_cast<KoopaTroopa*>(what)->isReanimed() ||
					dynamic_cast<KoopaTroopa*>(what)->isReanimed_Fast()
					|| dynamic_cast<KoopaTroopa*>(what)->isGrabbed())))
			{
				if (big)
				{
					if (racoon)
					{
						racoon2big_counter = 0;
						Game::instance()->setFreezed(true);
						if (fly)
						{
							fly = false;
							pre_fly = false;
							racoon = false;
							if(jumping)
								endJumping();
						}
					}
					else
					{
						big = false;
						transparent = true;
					}
					moving = false;
				}
				else
				{
					if (!transparent)
					{
						dying = true;

						// stop level music
						Game::instance()->stopMusic();

						// play death music
						Sounds::instance()->play("death");
					}
				}
			}
		}
	}

	// Mario grab KoopaTroopa's shell
	if ((dynamic_cast<KoopaTroopa*>(what) &&
		(dynamic_cast<KoopaTroopa*>(what)->isReanimed() ||
			dynamic_cast<KoopaTroopa*>(what)->isReanimed_Fast())) && (fromDir==LEFT || fromDir==RIGHT) 
		&& pre_grab)
	{
		if (!grab)
		{
			grab = true;
			dynamic_cast<KoopaTroopa*>(what)->setGrabbed(true);
		}
	}
}

// running = double moving speed
void Mario::setRunning(bool _running)
{
	// do nothing if running state does not change
	if(running == _running)
		return;

	// set new running state
	running = _running;
}

// override die method (Mario is a special case)
void Mario::die()
{
	dying_counter = -1;

	// death music
	Sounds::instance()->play("death");

	// call superclass method
	Entity::die();

	// stop level music
	Game::instance()->stopMusic();
}

// crouch
void Mario::setCrouch(bool active)
{
	if(!jumping && !falling)
		crouch = active;
}

void Mario::powerUp()
{
	Sounds::instance()->play("eat");
	transformation_counter = 0;
	big = true;

	Game::instance()->setFreezed(true);
}

void Mario::marioRacoon()
{
	//Sounds::instance()->play("eat");

	if (big)
	{
		big2racoon_counter = 0;
	}

	Game::instance()->setFreezed(true);
}
