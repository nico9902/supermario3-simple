#include "Block.h"
#include "Sprites.h"
#include <QBrush>
#include <QPainter>

Block::Block(QPoint point, bool _type_x) : Inert()
{
	// set position
	setPos(QPoint(point.x(), point.y()));

	// set type_x
	type_x = _type_x;

	// set texture
	texture_block[0] = Sprites::instance()->get1("block");
	texture_block[1] = Sprites::instance()->get1("block-x");

	// set a high z-value so it is displayed on top of other objects
	setZValue(2);
}

void Block::animate() 
{
	// type_x: block of Underground Level
	if (!type_x)
		setPixmap(texture_block[0]);
	else
		setPixmap(texture_block[1]);
}