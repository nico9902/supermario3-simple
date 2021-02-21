#pragma once

#include "Collectable.h"

class Scoring : public Collectable 
{
	private:

	    QPixmap texture[8];
	    bool combo = false;
	    int combo_counter = 0;
	    bool active = false;
	    int active_counter = 0;
	    int type;
	    int point_counter;

    public:

	    Scoring(QPoint position, int _type = 1);

	    // inherited methods
	    virtual std::string name() { return "Scoring"; }

	    virtual void animate();

	    virtual void hit(Object *what, Direction fromDir) {};

	    // @override
	    virtual void advance();
};