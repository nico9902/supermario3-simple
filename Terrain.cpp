#include "Terrain.h"
#include "Sprites.h"
#include <QBrush>
#include <QPainter>

Terrain::Terrain(QRect rect) : Inert()
{
	// set position
    setPos(QPoint(rect.x(), rect.y()));

	// create collage texture
    QPixmap collage(rect.width(), rect.height());
    QPainter painter(&collage);
 
	// corners
	painter.drawPixmap(0, 0, Sprites::instance()->get("terrain-NW"));
	painter.drawPixmap(rect.width()-16, 0, Sprites::instance()->get("terrain-NE"));
	// top
	for(int x=16; x<=rect.width()-32; x += 16)
		painter.drawPixmap(x, 0, Sprites::instance()->get("terrain-N"));
	// left
	for(int y=16; y<=rect.height()-16; y += 16)
		painter.drawPixmap(0, y, Sprites::instance()->get("terrain-W"));
	// right
	for(int y=16; y<=rect.height()-16; y += 16)
		painter.drawPixmap(rect.width()-16, y, Sprites::instance()->get("terrain-E"));
	// center
	for(int x=16; x<=rect.width()-32; x += 16)
		for(int y=16; y<=rect.height()-16; y += 16)
			painter.drawPixmap(x, y, Sprites::instance()->get("terrain-C"));

	// end painting (necessary for setMask)
	painter.end();

	// make background color (224, 163, 216) transparent
	collage.setMask(collage.createMaskFromColor(QColor(224, 163, 216)));

	// set pixmap
    setPixmap(collage);

	// set a high z-value so it is displayed on top of other objects
	setZValue(2);
}
