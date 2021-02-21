#include "Base.h"
#include "Sprites.h"
#include <QPainter>

Base::Base(const std::string & color, QRect rect) : Inert()
{
	// set position
	setPos(QPoint(rect.x(), rect.y()-rect.height()));

	// create collage texture
	QPixmap collage(rect.width(), rect.height());
	QPainter painter(&collage);

	// corners
	std::string base_name = std::string("base-") + color + "-";
	painter.drawPixmap(0, 0, Sprites::instance()->get(base_name + "NW"));
	painter.drawPixmap(rect.width()-16, 0, Sprites::instance()->get(base_name + "NE"));
	painter.drawPixmap(rect.width()-16, rect.height()-16, Sprites::instance()->get(base_name + "SE"));
	painter.drawPixmap(0, rect.height()-16, Sprites::instance()->get(base_name + "SW"));
	// top
	for(int x=16; x<=rect.width()-32; x += 16)
		painter.drawPixmap(x, 0, Sprites::instance()->get(base_name + "N"));
	// bottom
	for(int x=16; x<=rect.width()-32; x += 16)
		painter.drawPixmap(x, rect.height()-16, Sprites::instance()->get(base_name + "S"));
	// left
	for(int y=16; y<=rect.height()-32; y += 16)
		painter.drawPixmap(0, y, Sprites::instance()->get(base_name + "W"));
	// right
	for(int y=16; y<=rect.height()-32; y += 16)
		painter.drawPixmap(rect.width()-16, y, Sprites::instance()->get(base_name + "E"));
	// center
	for(int x=16; x<=rect.width()-32; x += 16)
		for(int y=16; y<=rect.height()-32; y += 16)
			painter.drawPixmap(x, y, Sprites::instance()->get(base_name + "C"));

	// end painting (necessary for setMask)
	painter.end();

	// make background color (224, 163, 216) transparent
	collage.setMask(collage.createMaskFromColor(QColor(224, 163, 216)));

	setPixmap(collage);
}

QPainterPath Base::shape() const
{
	QPainterPath path;
	path.addRect(5, boundingRect().top(), boundingRect().width()-10, 5);
	return path;
}

BaseShadow::BaseShadow(QRect rect) : Background()
{
	// set position
	setPos(QPoint(rect.x(), rect.y()-rect.height()));

	// create collage texture
	QPixmap collage(rect.width(), rect.height());
	QPainter painter(&collage);

	// shadow
	for(int y=0; y<=rect.height()-16; y += 16)
		painter.drawPixmap(0, y, Sprites::instance()->get(y == 0 ? "base-shadow-topright" : "base-shadow-right"));

	// end painting (necessary for setMask)
	painter.end();

	// make background color (224, 163, 216) transparent
	collage.setMask(collage.createMaskFromColor(QColor(224, 163, 216)));

	setPixmap(collage);
}
