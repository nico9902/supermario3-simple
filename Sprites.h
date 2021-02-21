#pragma once

#include <QPixmap>

// Singleton class
class Sprites
{
	private:

		// sprites
		QPixmap hud;
		QPixmap enemies;
		QPixmap mario;
		QPixmap stage_tiles;
		QPixmap title_screen;
		QPixmap miscs;
		QPixmap font;
		QPixmap goal_roulette;
		QPixmap gameover_menu;

		Sprites();

	public:

		// singleton
		static Sprites* instance();

		// extract texture from sprites using the given id
		QPixmap get(const std::string & id);

		// extrat texture from sprites using given id (compiler limit)
		QPixmap get1(const std::string & id);
};