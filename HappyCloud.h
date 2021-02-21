#pragma once

#include "Inert.h"

class HappyCloud : public Inert
{
public:

	HappyCloud(QPoint point);

	QPixmap texture_cloud;

	// pure virtual methods that must be implemented
	virtual std::string name() { return "HappyCloud"; }
	virtual void hit(Object *what, Direction fromDir) { /* do nothing */ }
};
