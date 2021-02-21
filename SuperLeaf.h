#pragma once

#include "Collectable.h"

class SuperLeaf : public Collectable
{
	protected:

	    int number_jump;               // number of jumps since leaf is spawned

    public:

	    SuperLeaf(QPoint position);

	    // inherited methods
	    virtual std::string name() { return "SuperLeaf"; }
	    virtual void animate();
	    virtual void advance();
	    virtual void hit(Object *what, Direction fromDir);
};