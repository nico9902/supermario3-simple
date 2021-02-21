#pragma once

#include "Inert.h"
#include "Background.h"

class Base : public Inert
{
	public:

		Base(const std::string & color, QRect rect);

        // pure virtual methods that must be implemented
        virtual std::string name() { return "Base"; }
		virtual void hit(Object *what, Direction fromDir){}

		// this object has custom collider
		// --> we need to re-implement the shape() method
		QPainterPath shape() const;
};

class BaseShadow : public Background
{
	public:

		BaseShadow(QRect rect);
		virtual std::string name() { return "BaseShadow"; }
};
