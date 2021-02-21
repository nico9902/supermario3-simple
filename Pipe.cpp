#include "Pipe.h"
#include "Sprites.h"
#include "Game.h"
#include <QPainter>

Pipe::Pipe(QPoint position, int height, bool _black, bool _penetrable) : Inert()
{
	// set position
	setPos(QPoint(position.x(), position.y()-(1+height)*16));

	// set attributes
	black = _black;
	penetrable = _penetrable;

	// create collage texture
	QPixmap collage(32, (1+height)*16);
	QPainter painter(&collage);

	if (!black)
	{
		// entrance
		painter.drawPixmap(0, 0, Sprites::instance()->get("pipe-NW"));
		painter.drawPixmap(16, 0, Sprites::instance()->get("pipe-NE"));
		// pipe
		for (int i = 1; i <= height; i++)
		{
			painter.drawPixmap(0, i * 16, Sprites::instance()->get("pipe-W"));
			painter.drawPixmap(16, i * 16, Sprites::instance()->get("pipe-E"));
		}

		// end painting (necessary for setMask)
		painter.end();
	}
	else
	{
		// entrance
		painter.drawPixmap(0, height*16, Sprites::instance()->get1("pipe-black-NW"));
		painter.drawPixmap(16, height*16, Sprites::instance()->get1("pipe-black-NE"));
		// pipe
		for (int i = 0; i < height; i++)
		{
			painter.drawPixmap(0, i * 16, Sprites::instance()->get1("pipe-black-W"));
			painter.drawPixmap(16, i * 16, Sprites::instance()->get1("pipe-black-E"));
		}

		// end painting (necessary for setMask)
		painter.end();
	}

	// make background color (224, 163, 216) transparent
	collage.setMask(collage.createMaskFromColor(QColor(224, 163, 216)));

	setPixmap(collage);
	if (!black)
		setZValue(2);
	else
		setZValue(5);
}

void Pipe::hit(Object *what, Direction fromDir)
{
	Object::hit(what, fromDir);

	Mario* mario = Game::instance()->getMario();

	if (dynamic_cast<Mario*>(what) && fromDir == DOWN && black && penetrable)
	{
		mario->setGoUp(true);
		mario->setReturn2Scene(true);
	}
}