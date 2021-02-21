#include "HappyCloud.h"
#include "Sprites.h"
#include <QBrush>
#include <QPainter>

HappyCloud::HappyCloud(QPoint point) : Inert()
{
	// set position
	setPos(QPoint(point.x(), point.y()));

	// set texfture
	texture_cloud = Sprites::instance()->get1("cloud");

	// set pixmap
	setPixmap(texture_cloud);

	// set a high z-value so it is displayed on top of other objects
	setZValue(2);
}