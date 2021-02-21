#include "Coin.h"
#include "Sprites.h"
#include "Mario.h"
#include "Game.h"
#include "Sounds.h"

Coin::Coin(QPoint position) : Entity()
{
	// set attributes
	collidable = true;

	// create textures
	texture_animation = Sprites::instance()->get("coin-0");

	// make background color (224, 163, 216) transparent
	texture_animation.setMask(texture_animation.createMaskFromColor(QColor(224, 163, 216)));

	// set texture and position
	setPixmap(texture_animation);
	setPos(position - QPoint(0, pixmap().height()));

	// play coin sound
	Sounds::instance()->play("coin");
}


void Coin::animate()
{
	Entity::animate();

	setPixmap(texture_animation);
}

void Coin::hit(Object * what, Direction fromDir)
{
	if (dynamic_cast<Mario*>(what))
	{
		// coin is removed by scene
		setVisible(false);
		Game::instance()->getScene()->removeItem(this);

		// coins increase
		Game::instance()->coinpointschanged(1);
	}
}

// @override
void Coin::advance()
{
	/* do nothing */
}