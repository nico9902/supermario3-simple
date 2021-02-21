#include <QSound>
#include "BrickDebris.h"
#include "Sprites.h"

BrickDebris::BrickDebris(QPoint position, Direction dir) : Entity()
{
	// set texture and position
	texture[0] = Sprites::instance()->get1("brick-debris-0");
	texture[1] = Sprites::instance()->get1("brick-debris-1");
	texture[2] = Sprites::instance()->get1("brick-debris-2");
	texture[3] = Sprites::instance()->get1("brick-debris-3");
	// set texture and position
	texture[0].setMask(texture[0].createMaskFromColor(QColor(224, 163, 216)));
	texture[1].setMask(texture[1].createMaskFromColor(QColor(224, 163, 216)));
	texture[2].setMask(texture[2].createMaskFromColor(QColor(224, 163, 216)));
	texture[3].setMask(texture[3].createMaskFromColor(QColor(224, 163, 216)));
	setPixmap(texture[0]);
	setPos(position);

	// debris are not collidable
	collidable = false;

	// debris are always moving horizontally (slowly)
	moving = true;
	setDirection(dir);
	slow = true;

	// debris are overlaid on top of all other objects
	setZValue(10);

	// initially, debris are not falling
	falling = false;

	// once they are spawned, we make a small jump with random
	// duration so as to create the feeling of a true break
	jumping_duration = rand() % 15;
	startJumping();
}