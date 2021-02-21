#include "Entity.h"
#include "Game.h"
#include "Mario.h"
#include "Base.h"
#include "Scoring.h"
#include "Collectable.h"
#include "Enemy.h"
#include "Brick.h"
#include "Coin.h"
#include "Pipe.h"
#include "BrickDebris.h"
#include "KoopaTroopa.h"
#include "SuperLeaf.h"
#include "SecretBox.h"
#include "Mushroom.h"
#include "FireBall.h"
#include "Terrain.h"
#include "ParaGoomba.h"
#include "KoopaParaTroopa.h"
#include "Wing.h"
#include "Goomba.h"
#include "SwitchBlock.h"
#include "PiranhaPlant.h"

Entity::Entity() : Object()
{
	// physics parameters
	moving_speed     = 1;
	jumping_speed    = 3;
	falling_speed    = 3;
	moving_speed_div = 2;

	// flags
	dir     = RIGHT;
	moving  = true;
	jumping = false;
	falling = true;		// we can create entities in mid air and they will fall
	dead    = false;
	dying   = false;
	freezed = false;
	slow	= false;

	// counters
	jump_counter      = 0;
	animation_counter = 0;
	death_counter     = 0;

	// durations
	jumping_duration = 30;
	death_duration = 50;

	// others
	walkable_object = 0;
	animation_div = 1;
}

void Entity::startJumping()
{
    // entity can jump only when it is not falling
	if(!falling && !jumping)
	{
		walkable_object = 0;
		jumping = true;
	}
}

void Entity::endJumping()
{
	if(jumping)
	{
		jumping = false;
		jump_counter = 0;
		falling = true;
	}
}

void Entity::advance()
{
	if(freezed)
		return;
	
    // NOTE: every movement is embedded in a prevPos = pos() ... solveCollisions() block
	// this is the only way to check if movement does break the impenetrability hypothesis
	// if it does, we need to revert to previous position

    // moving
    if(moving)
    {
        prevPos = pos();

		// slow mode: move 1 pixel every moving_speed_div frames
		if(slow)
			moving_speed = animation_counter % moving_speed_div == 0;

        if(dir == RIGHT)
            setX(x() + moving_speed);
        else if(dir == LEFT)
			setX(x() - moving_speed);
		else if(dir == UP)
			setY(y() - moving_speed);
		else if(dir == DOWN)
			setY(y() + moving_speed);
	
        solveCollisions();
    }

    // jumping
    if(jumping)
    {
		prevPos = pos();

		// move upwards
        setY(y() - jumping_speed);
	
        // increase jump frame count
        jump_counter += jumping_speed;
	
        // end jumping when frame count reaches the defined limit
        if(jump_counter > jumping_duration)
            endJumping();
	
        solveCollisions();
    }

    // if the entity is not touching its walkable object anymore
    // we have to start falling
	if(walkable_object && !touchingDirection(walkable_object))
	{
		walkable_object = 0;
		falling = true;
	}

    // falling
	if(falling)
	{
		prevPos = pos();

		setY(y() + falling_speed);

		falling_counter++;

		solveCollisions();
	}

	// if we fall beyond the scene bottom limit
	// we have to die (if not dead already)
	if(y() > Game::instance()->getScene()->sceneRect().height() && !dead)
		die();
}

void Entity::animate()
{
	// increase animation counter
	animation_counter++;

	// increase death counter if dying
	if(dying && !dead)
	{
		death_counter++;
		if(death_counter >= death_duration)
			die();
	}
}

void Entity::solveCollisions()
{
	// if the entity cannot collide or is 100% dead, we avoid
	// solving possible collisions
	if(!collidable || dead)
		return;

    // get collisions
    QList<QGraphicsItem*> colliding_items = collidingItems();

	// will be set to true if we collide an impenetrable object
	bool revert = false;	

    // manage collisions
    for(auto & ci : colliding_items)
    {
		// convert to game object, and skip if conversion
		// does not work (should never happen)
		Object *obj = dynamic_cast<Object*>(ci);
		if(!obj)
			continue;

		// IGNORE section (no need to compute collision direction)
		{
			// ignore collision if obj is not collidable
			if( ! obj->isCollidable())
				continue;
		
			// ignore collisions between Collectables and Enemies
			if( (dynamic_cast<Collectable*>(this) && dynamic_cast<Enemy*>(obj)) ||
				(dynamic_cast<Enemy*>(this) && dynamic_cast<Collectable*>(obj)))
				continue;

			// ignore collision with a base while jumping
			if(dynamic_cast<Base*>(obj) && jumping)
				continue;

			// ignore collision of a dying entity with another entity
			Entity* entity_obj = dynamic_cast<Entity*>(obj);
			if(entity_obj && (dying || entity_obj->isDying()))
				continue;
		}

        // get collision direction
        Direction coll_dir = collisionDirection(obj);
   
		// if it is not possible to calculate it, we skip current collision
        // (e.g. this may happen if we have solved the collision earlier)
        if(!coll_dir)
		{
			//printf("%s collided with %s from an UNKNOWN direction\n", name().c_str(), obj->name().c_str());
            continue;
		}

		// special case 1: collision with a base from left or right
		// ---> ignore
		if(dynamic_cast<Base*>(obj) && (coll_dir == RIGHT || coll_dir == LEFT))
			continue;

        // special case 2: collision with a walkable inert object while falling
        // ---> end falling and set walkable object
		Inert* inert_obj = dynamic_cast<Inert*>(obj);
        if(coll_dir == DOWN && falling && inert_obj && inert_obj->isWalkable())
        {
				falling = false;
				falling_counter = 0;
				walkable_object = inert_obj;
				if (dynamic_cast<Base*>(obj)
					&& ((dynamic_cast<Base*>(obj)->y() - Game::instance()->getMario()->y()) >= 1
						&& (dynamic_cast<Base*>(obj)->y() - Game::instance()->getMario()->y()) <= 9)
					&& Game::instance()->getMario()->isBig() && 
					!Game::instance()->getMario()->isRacoon())
					continue;

				if (dynamic_cast<Base*>(obj)
					&& ((dynamic_cast<Base*>(obj)->y() - Game::instance()->getMario()->y()) >= 1
						&& (dynamic_cast<Base*>(obj)->y() - Game::instance()->getMario()->y()) <= 12)
					&& Game::instance()->getMario()->isBig() &&
					Game::instance()->getMario()->isRacoon())
					continue;
				//printf("%s is now walking on %s\n", name().c_str(), inert_obj->name().c_str());
        }

        // special case 3: collision with an object while jumping
        // --> end jumping
        if(coll_dir == UP && jumping && !dynamic_cast<Coin*>(obj))
            endJumping();

		// special case 4: collision with a base from up
		// ---> ignore
		if (dynamic_cast<Base*>(obj) && (coll_dir == UP))
			continue;

		// special case 5: collision with a KoopaTroopa in reanimed form from down
		// ---> ignore
		if (dynamic_cast<KoopaTroopa*>(obj) && (dynamic_cast<KoopaTroopa*>(obj)->isReanimed() ||
			dynamic_cast<KoopaTroopa*>(obj)->isReanimed_Fast())
			&& (coll_dir == DOWN)
			&& dynamic_cast<Mario*>(this))
		{
			dynamic_cast<Mario*>(this)->setKick(true);
			dynamic_cast<KoopaTroopa*>(obj)->setKicked(true);

			// score increases
			Game::instance()->scorechanged(100);
			new Scoring(QPoint(dynamic_cast<KoopaTroopa*>(obj)->x(), dynamic_cast<KoopaTroopa*>(obj)->y() - 16));

			if (dynamic_cast<KoopaTroopa*>(obj)->x() >= dynamic_cast<Mario*>(this)->x())
			{
				dynamic_cast<KoopaTroopa*>(obj)->setDirection(RIGHT);
				dynamic_cast<KoopaTroopa*>(obj)->setX(x() + 16);
			}
			else
			{
				dynamic_cast<KoopaTroopa*>(obj)->setDirection(LEFT);
				dynamic_cast<KoopaTroopa*>(obj)->setX(x() - 16);
			}

			continue;
		}

		// special case 6: collision with a KoopaTroopa grabbed
		// ---> ignore
		if (dynamic_cast<KoopaTroopa*>(obj) && (Game::instance()->getMario()->isGrab())
			&& (coll_dir == LEFT || coll_dir == RIGHT))
		{
			if(dynamic_cast<Mario*>(this))
				continue;
			else if (dynamic_cast<Enemy*>(this))
			{
				dynamic_cast<Enemy*>(this)->setSmashed(true);
				dynamic_cast<KoopaTroopa*>(obj)->setGrabbed(false);
				dynamic_cast<KoopaTroopa*>(obj)->setSmashed(true);
				Game::instance()->getMario()->setGrab(false);
			}
		}
		// special case 7: collision between a Mushroom and a SecretBox from RIGHT or LEFT
		// ---> ignore
		if (dynamic_cast<SecretBox*>(obj) && (dynamic_cast<Mushroom*>(this))
			&& (coll_dir == LEFT || coll_dir == RIGHT))
			continue;

		// special case 8: collision between a FireBall and a Enemy
		// ---> ignore
		if (dynamic_cast<Enemy*>(obj) && (dynamic_cast<FireBall*>(this)))
			continue;

		// special case 9: collision between an Object and a Wing
		// ---> ignore
		if (dynamic_cast<Wing*>(obj))
			continue;

		// special case 10: collision between an Object and Mario transparent
		// ---> ignore
		if (dynamic_cast<Mario*>(obj) && dynamic_cast<Mario*>(obj)->isTransparent())
			continue;

		// special case 11: collision between an Object and PiranhaPlant
		// ---> ignore
		if (dynamic_cast<PiranhaPlant*>(this) && dynamic_cast<FireBall*>(obj))
			continue;

		// special case 12: collision between an Object and SuperLeaf except Mario
		// ---> ignore
		if (dynamic_cast<SuperLeaf*>(this) && !dynamic_cast<Mario*>(obj))
			continue;

		// special case 13: collision with Enemy smashed 
		// ---> ignore
		if (dynamic_cast<Enemy*>(this) && dynamic_cast<Enemy*>(this)->isSmashed())
			continue;
		
		// special case 14: collision between KoopaParaTroopa and Terrain from RIGHT or LEFT 
		// ---> ignore
		if (dynamic_cast<KoopaParaTroopa*>(this) && dynamic_cast<Terrain*>(obj)
			&& (coll_dir == LEFT || coll_dir == RIGHT))
			continue;

		// special case 15: collision with BrickDebris
		// ---> ignore
		if (dynamic_cast<BrickDebris *>(obj))
			continue;

		// special case 16: collision with SwitchBlock smitten
		// ---> ignore
		if (dynamic_cast<SwitchBlock *>(obj) && dynamic_cast<SwitchBlock *>(obj)->isSmitten())
			continue;

		// special case 17: collision with Coin
		// ---> ignore
		if (dynamic_cast<Coin *>(obj) && !dynamic_cast<Mario*>(this))
			continue;

		// special case 18: collision beetwen mushroom and Fireball
		// ---> ignore
		if (dynamic_cast<Mushroom*>(this) && dynamic_cast<FireBall*>(obj))
			continue;

		// special case 19: collision beetwen mario camedown and Pipe
		// ---> ignore
		if (Game::instance()->getMario()->isComeDown() && dynamic_cast<Pipe*>(obj))
			continue;

		// special case 19: collision beetwen mario and Pipe in UNDERGROUND level
		// ---> ignore
		if (dynamic_cast<Pipe*>(obj) && dynamic_cast<Pipe*>(obj)->isBlack()
			&& !dynamic_cast<Pipe*>(obj)->isPenetrable())
			continue;

		// special case 20: collision beetwen mario and Pipe penetrable in UNDERGROUND level
		// ---> ignore
		if (dynamic_cast<Pipe*>(obj) && dynamic_cast<Pipe*>(obj)->isBlack()
			&& dynamic_cast<Pipe*>(obj)->isPenetrable()
			&& Game::instance()->getMario()->isGoUp())
			continue;

        // the two objects hit each other
        obj->hit(this, inverse(coll_dir));
		this->hit(obj, coll_dir);

        // if we ended up here, it means we have to revert
		// to the previous position (impenetrability)
		revert = true;
    }

	// revert to previous position if needed
	if(revert)
		setPos(prevPos);

	// touchdown correction
	// entity is on a walkable object but is not touching it!
	// (this occurs when entity penetrates the walkable object,
	//  in which case the 'revert' operation will put it in mid-air)
	if(revert && walkable_object && !collisionDirection(walkable_object))
	{
		// just moving down until entity touches the walkable
		while(touchingDirection(walkable_object) != DOWN)
		{
			static int correct_counter=0;
			//printf("[%d] %s is correcting touchdown (y = %.3f, dir = %d)\n", correct_counter++, this->name().c_str(), y(), touchingDirection(walkable_object));
			setY(y()+1);
		}
	}
}

void Entity::die()
{
	// only a full living entity can die
	if(!dead)
	{
		// cannot move
		moving = false;

		// dead
		dead = true;
	}
}


