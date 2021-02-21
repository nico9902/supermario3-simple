#include "Wing.h"
#include "Sprites.h"
#include "Mario.h"
#include "Sounds.h"
#include "Game.h"

Wing::Wing(QPoint position, bool _left, Direction _dirKoopa, bool _kopa) : Enemy() 
{
	// set attributes
	fly = true;
	left = _left;
	koopa = _kopa;
	dirKoopa = _dirKoopa;

	// animation divisor
	animation_div = 10;

	// durations
	death_duration = 400;

	// textures
	texture_right[0] = Sprites::instance()->get1("wing-0");
	texture_right[1] = Sprites::instance()->get1("wing-1");
	texture_left[0] = texture_right[0].transformed(QTransform().scale(-1, 1));
	texture_left[1] = texture_right[1].transformed(QTransform().scale(-1, 1));


	setPixmap(texture_right[0]);

	// set texture and correct y-coordinate w.r.t. texture height
	setPos(position - QPoint(0, pixmap().height()));

	setZValue(2);
}


void Wing::animate() {
	// increase animation counter
	animation_counter++;
	// save current texture height (for later correction)
	int prev_h = boundingRect().height();
	
	if(fly && !left && !koopa)
		setPixmap(texture_right[(animation_counter / animation_div) % 2]);
	else if(fly && left && !koopa)
		setPixmap(texture_left[(animation_counter / animation_div) % 2]);
	else if (fly && koopa && dirKoopa == LEFT)
		setPixmap(texture_right[(animation_counter / animation_div) % 2]);
	else if(fly && koopa && dirKoopa == RIGHT)
		setPixmap(texture_left[(animation_counter / animation_div) % 2]);

}

void Wing::hit(Object *what, Direction fromDir) 
{
	Object::hit(what, fromDir);
}

void Wing::advance() 
{
	/* do nothing */
}

void Wing::hurt() 
{
	/* do nothing */
}

void Wing::smash()
{
	/* do nothing */
}