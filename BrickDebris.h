#pragma once

#include "Entity.h"

class BrickDebris : public Entity
{
protected:

	int walk_counter;

	QPixmap texture[4];

public:

	BrickDebris(QPoint position, Direction dir);

	// inherited methods
	virtual std::string name() { return "BrickDebris"; }
	virtual void animate() { walk_counter++; }
	virtual void hit(Object *what, Direction fromDir) {}
};