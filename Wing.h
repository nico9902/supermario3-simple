#pragma once

#include "Enemy.h"

class Wing : public Enemy 
{
	
	protected:

	    // attributes
	    int move_duration;
	    bool fly;
	    bool left;
	    bool koopa;
	    int dirKoopa;

	    // textures
	    QPixmap texture_right[2];        //  wing right animation
	    QPixmap texture_left[2];        //  wing left animation



    public:

	    Wing(QPoint position, bool _left = true, Direction _dirKoopa = LEFT, bool _koopa = false);

	    // pure virtual methods that must be implemented
	    virtual std::string name() { return "Wing"; }
	    virtual void animate();
	    virtual void hit(Object *what, Direction fromDir);
	    virtual void hurt();
	    virtual void smash();
	    virtual void advance();

	    // setters
	    void setDying(bool _dying) { dying = _dying; }
	    void setDirKoopa(Direction _dir) { dirKoopa = _dir; }
};