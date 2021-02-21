#pragma once

#include "Inert.h"

class Block : public Inert
{
	public:

	    Block(QPoint point, bool _type_x=false);
		
		QPixmap texture_block[2];
		
		bool type_x;              // block in Underground World
		
		// pure virtual methods that must be implemented
		virtual std::string name() { return "Block"; }
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir) { /* do nothing */ }
};