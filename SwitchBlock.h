#pragma once

#include "Collectable.h"

class SwitchBlock : public Collectable
{
	protected:

	    // textures
	    QPixmap texture[4];
	    bool smitten;

    public:

	    SwitchBlock(QPoint position);
	    
		// getters
		bool isSmitten() { return smitten; }
		
        // setters
	    void setSmitten(bool _smitten) { smitten = _smitten; }

	    // inherited methods
	    virtual std::string name() { return "SwitchBlock"; }

	    virtual void animate();

	    virtual void advance();

	    virtual void hit(Object *what, Direction fromDir);

};