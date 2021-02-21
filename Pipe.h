#pragma once

#include "Inert.h"

class Pipe : public Inert
{
    private:

		bool black;
		bool penetrable;

	public:

		Pipe(QPoint position, int height=1, bool _black=false, bool _penetrable=false);

        // pure virtual methods that must be implemented
        virtual std::string name() { return "Pipe"; }
		virtual void hit(Object *what, Direction fromDir);

		bool isBlack() { return black; }
		bool isPenetrable() { return penetrable; }
};
