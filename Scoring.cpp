#include "Scoring.h"
#include "Mario.h"
#include "Sounds.h"
#include "SecretBox.h"
#include "Brick.h"
#include "Enemy.h"
#include "Pipe.h"
#include "Sprites.h"

Scoring::Scoring(QPoint position, int _type) : Collectable(position) 
{
	// set attributes
	active = true;
	combo = true;
	combo_counter = 0;
	active_counter = 0;
	type = _type;
	point_counter = 0;

	//animation texture
	texture[0] = Sprites::instance()->get1("point-0"); //100
	texture[1] = Sprites::instance()->get1("point-1"); //200
	texture[2] = Sprites::instance()->get1("point-2"); //400
	texture[3] = Sprites::instance()->get1("point-3"); //800
	texture[4] = Sprites::instance()->get1("point-4"); //1000
	texture[5] = Sprites::instance()->get1("point-5"); //2000
	texture[6] = Sprites::instance()->get1("point-6"); //4000
	texture[7] = Sprites::instance()->get1("point-7"); //8000

	// set texture and position
	setPos(position);

	setZValue(4);
}

void Scoring::animate() 
{
	Entity::animate();

	if (type == 1) 
		setPixmap(texture[0]);
	else if (type == 2) 
		setPixmap(texture[1]);
	else if (type == 3) 
		setPixmap(texture[2]);
	else if (type == 4) 
		setPixmap(texture[3]);
	else if (type == 5) 
		setPixmap(texture[4]);
	else if (type == 6) 
		setPixmap(texture[5]);
	else if (type == 7) 
		setPixmap(texture[6]);
	else if (type == 8) 
		setPixmap(texture[7]);
}

void Scoring::advance() 
{
	// score appear on the scene
	if (active) 
	{
		point_counter++;
		if (point_counter < 40)
			setVisible(false);
		else if (point_counter >= 40 && point_counter < 60) 
		{
			setVisible(true);
			setY(y() - 1);
		}
		else 
		{
			setVisible(false);
			die();
		}
	}

}