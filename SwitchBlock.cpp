#include "Game.h"
#include "SwitchBlock.h"
#include "Sprites.h"
#include <QPainter>

SwitchBlock::SwitchBlock(QPoint position) : Collectable(position) 
{

	// set attributes
	smitten = false;
	moving = false;

	// set position
	setPos(position - QPoint(0, pixmap().height()));

	texture[0] = Sprites::instance()->get1("push-0");
	texture[1] = Sprites::instance()->get1("push-1");
	texture[2] = Sprites::instance()->get1("push-2");
	texture[3] = Sprites::instance()->get1("push-smitten");

	texture[0].setMask(texture[0].createMaskFromColor(QColor(224, 163, 216)));
	texture[1].setMask(texture[1].createMaskFromColor(QColor(224, 163, 216)));
	texture[2].setMask(texture[2].createMaskFromColor(QColor(224, 163, 216)));
	texture[3].setMask(texture[3].createMaskFromColor(QColor(224, 163, 216)));

	setPixmap(texture[0]);
}

void SwitchBlock::hit(Object *what, Direction fromDir) 
{
	Object::hit(what, fromDir);

	Mario *mario = dynamic_cast<Mario *>(what);
	if (mario && fromDir==UP) 
	{
		smitten = true;
	}
}

void SwitchBlock::animate() {
	animation_counter++;

	if (!moving)
		setPixmap(texture[(animation_counter / 5) % 3]);
	if (smitten)
		setPixmap(texture[3]);
}

void SwitchBlock::advance() {
	// never fall from walkable object
	/*if (walkable_object)
	{
		int delta = dir == RIGHT ? 16 : -16;
		setX(x() + delta);
		if (!touchingDirection(walkable_object))
			dir = inverse(dir);
		setX(x() - delta);
	}*/

	// if switch block fully emerges from spawn position, 
	// become collidable
	if (y() == spawned_position.y())
	{
		collidable = true;
	}

	if (smitten) 
	{
		Game::instance()->swap();
		//smitten = false;
	}

	Entity::advance();
}