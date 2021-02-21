#include "Sprites.h"
#include "utils.h"
#include <QBitmap>

// utility function
QRect moveBy(QRect rect, int x, int y, int dx = 16, int dy = 16, int border_x = 1, int border_y = 1)
{
	rect.moveTo(QPoint(rect.x() + x*dx + x*border_x, rect.y() + y*dy + y*border_y));
	return rect;
}

QRect moveMarioBy(QRect rect, int x, int y, int dx = 16, int dy = 16)
{
	return moveBy(rect, x, y, dx, dy, 2, 2);
}

QRect moveRight(QRect rect, int pixels)
{
	rect.translate(QPoint(pixels, 0));
	return rect;
}

// main object positions within sprites
static QRect base(919, 137, 16, 16);
static QRect mario_small(1, 16, 16, 16);
static QRect mario_big(1, 93, 16, 27);
static QRect mario_racoon(1, 348, 22, 30);
static QRect terrain(443, 154, 16, 16);
static QRect hud_panel(3, 3, 232, 28);
static QRect pipe(69, 35, 16, 16);
static QRect goomba_brown(0, 0, 16, 15);
static QRect goomba_red(88, 0, 16, 15);
static QRect secret_box(1140, 1, 16, 16);
static QRect coin_spawnable(290, 101, 16, 14);
static QRect coin(953, 69, 16, 16);
static QRect mushroom(156, 121, 16, 16);
static QRect koopatroopa(96, 48, 16, 28);
static QRect wing(136, 2, 8, 12);
static QRect brick(1038, 35, 16, 16);

Sprites* Sprites::instance()
{
	static Sprites uniqueInstance;
	return &uniqueInstance;
}

Sprites::Sprites()
{
	hud          = loadTexture(":/graphics/sprites/hud.png", Qt::magenta);
	mario        = loadTexture(":/graphics/sprites/mario.png", QColor(68, 145, 190));
	enemies      = loadTexture(":/graphics/sprites/enemies.png", QColor(68, 145, 190));
	stage_tiles  = loadTexture(":/graphics/sprites/stage_tiles.png");
	title_screen = loadTexture(":/graphics/sprites/title_screen.png");
	miscs        = loadTexture(":/graphics/sprites/miscs.png", QColor(166, 185, 255));
	font = loadTexture(":/graphics/sprites/font.png", QColor(255, 150, 255));
	goal_roulette = loadTexture(":/graphics/sprites/goal_roulette.png", QColor(255, 150, 255));
	gameover_menu = loadTexture(":/graphics/sprites/gameover-menu.png", QColor(68, 34, 0));
}

QPixmap Sprites::get(const std::string & id)
{
	if (id == "mario-small-stand")
		return mario.copy(mario_small);
	else if (id == "mario-small-walk-0")
		return mario.copy(mario_small);
	else if (id == "mario-small-walk-1")
		return mario.copy(moveMarioBy(mario_small, 1, 0));
	else if (id == "mario-small-walk-2")
		return mario.copy(mario_small);
	else if (id == "mario-small-walk-3")
		return mario.copy(moveMarioBy(mario_small, 1, 0));
	else if (id == "mario-small-fall")
		return mario.copy(moveMarioBy(mario_small, 2, 0));
	else if (id == "mario-small-jump")
		return mario.copy(moveMarioBy(mario_small, 2, 0));
	else if (id == "mario-small-run-0")
		return mario.copy(moveMarioBy(mario_small, 3, 0));
	else if (id == "mario-small-run-1")
		return mario.copy(moveMarioBy(mario_small, 4, 0));
	else if (id == "mario-small-run-2")
		return mario.copy(moveMarioBy(mario_small, 3, 0));
	else if (id == "mario-small-run-3")
		return mario.copy(moveMarioBy(mario_small, 4, 0));
	else if (id == "mario-small-brake")
		return mario.copy(moveMarioBy(mario_small, 6, 0));
	else if (id == "mario-small-kick")
		return mario.copy(moveMarioBy(mario_small, 10, 0));
	else if (id == "mario-small-grab-0")
		return mario.copy(moveMarioBy(mario_small, 8, 0));
	else if (id == "mario-small-grab-1")
		return mario.copy(moveMarioBy(mario_small, 9, 0));

	else if (id == "mario-big-stand")
		return mario.copy(mario_big);
	else if (id == "mario-big-walk-0")
		return mario.copy(mario_big);
	else if (id == "mario-big-walk-1")
		return mario.copy(moveMarioBy(mario_big, 1, 0));
	else if (id == "mario-big-walk-2")
		return mario.copy(moveMarioBy(mario_big, 2, 0));
	else if (id == "mario-big-walk-3")
		return mario.copy(moveMarioBy(mario_big, 1, 0));
	else if (id == "mario-big-fall")
		return mario.copy(moveMarioBy(mario_big, 2, 0));
	else if (id == "mario-big-jump")
		return mario.copy(moveMarioBy(mario_big, 4, 0));
	else if (id == "mario-big-run-0")
		return mario.copy(QRect(117, 93, 19, 27));
	else if (id == "mario-big-run-1")
		return mario.copy(QRect(91, 93, 19, 27));
	else if (id == "mario-big-run-2")
		return mario.copy(QRect(143, 93, 19, 27));
	else if (id == "mario-big-run-3")
		return mario.copy(QRect(91, 93, 19, 27));
	else if (id == "mario-big-brake")
		return mario.copy(QRect(195, 92, 16, 28));
	else if (id == "mario-big-crouch")
		return mario.copy(QRect(55, 102, 16, 18));
	else if (id == "mario-big-kick")
		return mario.copy(QRect(306, 93, 21, 27));
	else if (id == "mario-big-grab-0")
		return mario.copy(QRect(249, 93, 15, 27));
	else if (id == "mario-big-grab-1")
		return mario.copy(QRect(267, 93, 15, 27));

	else if (id == "mario-half")
		return mario.copy(QRect(209, 132, 16, 22));

	else if (id == "mario-dead")
		return mario.copy(moveMarioBy(mario_small, 17, 0));

	else if (id == "goomba-brown-walk-0")
		return enemies.copy(goomba_brown);
	else if (id == "goomba-brown-walk-1")
		return enemies.copy(moveBy(goomba_brown, 1, 0, 16, 16, 0));
	else if (id == "goomba-brown-smashed")
		return enemies.copy(QRect(32, 7, 16, 9));
	else if (id == "goomba-red-walk-0")
		return enemies.copy(goomba_red);
	else if (id == "goomba-red-walk-1")
		return enemies.copy(moveBy(goomba_red, 1, 0, 16, 16, 0));
	else if (id == "goomba-red-smashed")
		return enemies.copy(QRect(120, 7, 16, 9));

	else if (id == "KoopaTroopa-walk-0")
		return enemies.copy(koopatroopa);
	else if (id == "KoopaTroopa-walk-1")
		return enemies.copy(moveBy(koopatroopa, 1, 0, 15.5, 16));
	else if (id == "KoopaTroopa-walk-green-0")
		return enemies.copy(QRect(0, 48, 16, 28));
	else if (id == "KoopaTroopa-walk-green-1")
		return enemies.copy(moveBy(QRect(0, 48, 16, 28), 1, 0, 15.5, 16));
	else if (id == "KoopaTroopa-smashed-0")
		return enemies.copy(QRect(128, 48, 16, 16));
	else if (id == "KoopaTroopa-smashed-1")
		return enemies.copy(moveBy(QRect(128, 47, 16, 16), 0, 1, 16, 16));
	else if (id == "KoopaTroopa-kicked-0")
		return enemies.copy(QRect(128, 48, 16, 16));
	else if (id == "KoopaTroopa-kicked-1")
		return enemies.copy(moveBy(QRect(128, 48, 16, 16), 1, 0, 16, 16, 0, 0));
	else if (id == "KoopaTroopa-kicked-2")
		return enemies.copy(moveBy(QRect(128, 48, 16, 16), 2, 0, 16, 16, 0, 0));
	else if (id == "KoopaTroopa-kicked-3")
		return enemies.copy(moveBy(QRect(128, 48, 16, 16), 3, 0, 16, 16, 0, 0));

	else if (id == "PiranhaPlant-0")
		return enemies.copy(QRect(96, 144, 16, 31));
	else if (id == "PiranhaPlant-1")
	    return enemies.copy(QRect(112, 144, 16, 31));
	else if (id == "PiranhaPlant-2")
	    return enemies.copy(QRect(128, 144, 16, 31));
	else if (id == "PiranhaPlant-3")
	    return enemies.copy(QRect(144, 144, 16, 31));
	else if (id == "PiranhaPlant-4")
	    return enemies.copy(QRect(160, 144, 16, 31));
	else if (id == "PiranhaPlant-5")
	    return enemies.copy(QRect(176, 144, 16, 31));

	else if (id == "terrain-NW")
		return stage_tiles.copy(terrain);
	else if (id == "terrain-N")
		return stage_tiles.copy(moveBy(terrain, 1, 0));
	else if (id == "terrain-NE")
		return stage_tiles.copy(moveBy(terrain, 2, 0));
	else if (id == "terrain-W")
		return stage_tiles.copy(moveBy(terrain, 0, 1));
	else if (id == "terrain-C")
		return stage_tiles.copy(moveBy(terrain, 1, 1));
	else if (id == "terrain-E")
		return stage_tiles.copy(moveBy(terrain, 2, 1));

	else if(id == "base-pink-C")
		return stage_tiles.copy(moveBy(base, 1, 1));
	else if(id == "base-pink-NW")
		return stage_tiles.copy(base);
	else if(id == "base-pink-N")
		return stage_tiles.copy(moveBy(base, 1, 0));
	else if(id == "base-pink-NE")
		return stage_tiles.copy(moveBy(base, 2, 0));
	else if(id == "base-pink-E")
		return stage_tiles.copy(moveBy(base, 2, 1));
	else if(id == "base-pink-SE")
		return stage_tiles.copy(moveBy(base, 2, 2));
	else if(id == "base-pink-S")
		return stage_tiles.copy(moveBy(base, 1, 2));
	else if(id == "base-pink-SW")
		return stage_tiles.copy(moveBy(base, 0, 2));
	else if(id == "base-pink-W")
		return stage_tiles.copy(moveBy(base, 0, 1));
	else if(id == "base-lightblue-C")
		return stage_tiles.copy(moveBy(base, 4, 1));
	else if(id == "base-lightblue-NW")
		return stage_tiles.copy(moveBy(base, 3, 0));
	else if(id == "base-lightblue-N")
		return stage_tiles.copy(moveBy(base, 4, 0));
	else if(id == "base-lightblue-NE")
		return stage_tiles.copy(moveBy(base, 5, 0));
	else if(id == "base-lightblue-E")
		return stage_tiles.copy(moveBy(base, 5, 1));
	else if(id == "base-lightblue-SE")
		return stage_tiles.copy(moveBy(base, 5, 2));
	else if(id == "base-lightblue-S")
		return stage_tiles.copy(moveBy(base, 4, 2));
	else if(id == "base-lightblue-SW")
		return stage_tiles.copy(moveBy(base, 3, 2));
	else if(id == "base-lightblue-W")
		return stage_tiles.copy(moveBy(base, 3, 1));
	else if(id == "base-green-C")
		return stage_tiles.copy(moveBy(base, 1, 4));
	else if(id == "base-green-NW")
		return stage_tiles.copy(moveBy(base, 0, 3));
	else if(id == "base-green-N")
		return stage_tiles.copy(moveBy(base, 1, 3));
	else if(id == "base-green-NE")
		return stage_tiles.copy(moveBy(base, 2, 3));
	else if(id == "base-green-E")
		return stage_tiles.copy(moveBy(base, 2, 4));
	else if(id == "base-green-SE")
		return stage_tiles.copy(moveBy(base, 2, 5));
	else if(id == "base-green-S")
		return stage_tiles.copy(moveBy(base, 1, 5));
	else if(id == "base-green-SW")
		return stage_tiles.copy(moveBy(base, 0, 5));
	else if(id == "base-green-W")
		return stage_tiles.copy(moveBy(base, 0, 4));

	else if(id == "base-white-C")
		return stage_tiles.copy(moveBy(base, 4, 4));
	else if(id == "base-white-NW")
		return stage_tiles.copy(moveBy(base, 3, 3));
	else if(id == "base-white-N")
		return stage_tiles.copy(moveBy(base, 4, 3));
	else if(id == "base-white-NE")
		return stage_tiles.copy(moveBy(base, 5, 3));
	else if(id == "base-white-E")
		return stage_tiles.copy(moveBy(base, 5, 4));
	else if(id == "base-white-SE")
		return stage_tiles.copy(moveBy(base, 5, 5));
	else if(id == "base-white-S")
		return stage_tiles.copy(moveBy(base, 4, 5));
	else if(id == "base-white-SW")
		return stage_tiles.copy(moveBy(base, 3, 5));
	else if(id == "base-white-W")
		return stage_tiles.copy(moveBy(base, 3, 4));

	else if(id == "base-shadow-topright")
		return stage_tiles.copy(moveBy(base, 8, 6));
	else if(id == "base-shadow-right")
		return stage_tiles.copy(moveBy(base, 8, 7));

	else if (id == "main-screen")
		return title_screen.copy(QRect(516, 226, 16*16, 15*16));

	else if (id == "brush-small")
		return stage_tiles.copy(QRect(375, 324, 16, 16));

	else if(id == "hud")
		return hud.copy(hud_panel);

	else if(id == "pipe-NW")
		return stage_tiles.copy(moveBy(pipe, 0, 0));
	else if(id == "pipe-NE")
		return stage_tiles.copy(moveBy(pipe, 1, 0));
	else if(id == "pipe-W")
		return stage_tiles.copy(moveBy(pipe, 0, 1));
	else if(id == "pipe-E")
		return stage_tiles.copy(moveBy(pipe, 1, 1));

	else if(id == "coin-0")
		return stage_tiles.copy(coin);
	else if(id == "coin-1")
		return stage_tiles.copy(moveBy(coin, 1, 0));
	else if(id == "coin-2")
		return stage_tiles.copy(moveBy(coin, 2, 0));
	else if(id == "coin-spawnable-0")
		return miscs.copy(coin_spawnable);
	else if(id == "coin-spawnable-1")
		return miscs.copy(moveRight(coin_spawnable, 24));
	else if(id == "coin-spawnable-2")
		return miscs.copy(moveRight(coin_spawnable, 13));

	else if(id == "mushroom-red")
		return miscs.copy(mushroom);
	else if(id == "mushroom-green")
		return miscs.copy(moveRight(mushroom, 130));

	else if(id == "leaf")
	    return miscs.copy(QRect(180, 121, 16, 16));

	else if(id == "secret-box-0")
		return stage_tiles.copy(secret_box);
	else if(id == "secret-box-1")
		return stage_tiles.copy(moveBy(secret_box, 1, 0));
	else if(id == "secret-box-2")
		return stage_tiles.copy(moveBy(secret_box, 2, 0));
	else if(id == "secret-box-3")
		return stage_tiles.copy(moveBy(secret_box, 3, 0));

	else if(id == "secret-box-inactive")
		return stage_tiles.copy(moveBy(secret_box, 4, 0));

	else 
		return QPixmap();
}

QPixmap Sprites::get1(const std::string & id)
{
	if (id == "fireball-0")
		return enemies.copy(QRect(164, 275, 7, 9));
	else if (id == "fireball-1")
	    return enemies.copy(QRect(180, 275, 7, 9));
	else if (id == "fireball-2")
	    return enemies.copy(QRect(165, 292, 7, 9));
	else if (id == "fireball-3")
	    return enemies.copy(QRect(181, 292, 7, 9));
	else if (id == "fireball-crush-0")
	    return mario.copy(QRect(415, 1, 15, 15));
	else if (id == "fireball-crush-1")
	    return mario.copy(QRect(433, 1, 15, 15));
	else if (id == "fireball-crush-2")
	    return mario.copy(QRect(469, 1, 15, 15));

	else if (id == "wing-0")
		return enemies.copy(wing);
	else if (id == "wing-1")
		return enemies.copy(QRect(144, 4, 8, 12));

	else if (id == "mario-racoon-stand")
		return mario.copy(mario_racoon);
	else if (id == "mario-racoon-walk-0")
		return mario.copy(mario_racoon);
	else if (id == "mario-racoon-walk-1")
		return mario.copy(QRect(27, 348, 22, 30));
	else if (id == "mario-racoon-walk-2")
		return mario.copy(QRect(53, 348, 23, 30));
	else if (id == "mario-racoon-walk-3")
		return mario.copy(QRect(27, 348, 22, 30));
	else if (id == "mario-racoon-fall")
		return mario.copy(QRect(131, 348, 23, 30));
	else if (id == "mario-racoon-jump")
		return mario.copy(QRect(105, 348, 23, 30));
	else if (id == "mario-racoon-run-0")
		return mario.copy(QRect(183, 93, 22, 30));
	else if (id == "mario-racoon-run-1")
		return mario.copy(QRect(209, 348, 22, 30));
	else if (id == "mario-racoon-run-2")
		return mario.copy(QRect(235, 348, 22, 30));
	else if (id == "mario-racoon-run-3")
		return mario.copy(QRect(209, 348, 22, 30));
	else if (id == "mario-racoon-brake")
		return mario.copy(QRect(339, 348, 16, 30));
	else if (id == "mario-racoon-crouch")
		return mario.copy(QRect(79, 348, 22, 30));
	else if (id == "mario-racoon-kick")
		return mario.copy(QRect(81, 383, 22, 30));
	else if (id == "mario-racoon-grab-0")
		return mario.copy(QRect(1, 383, 22, 30));
	else if (id == "mario-racoon-grab-1")
		return mario.copy(QRect(27, 383, 22, 30));
	else if (id == "mario-racoon-round-0")
		return mario.copy(QRect(357, 348, 16, 30));
	else if (id == "mario-racoon-round-1")
		return mario.copy(QRect(375, 348, 23, 30));
	else if (id == "mario-racoon-round-2")
		return mario.copy(QRect(401, 348, 16, 30));
	else if (id == "mario-racoon-pre-fly-0")
		return mario.copy(QRect(183, 348, 25, 30));
	else if (id == "mario-racoon-pre-fly-1")
		return mario.copy(QRect(209, 348, 25, 30));
	else if (id == "mario-racoon-pre-fly-2")
		return mario.copy(QRect(235, 348, 25, 30));
	else if (id == "mario-racoon-fly-0")
		return mario.copy(QRect(261, 348, 25, 30));
	else if (id == "mario-racoon-fly-1")
		return mario.copy(QRect(287, 348, 25, 30));
	else if (id == "mario-racoon-fly-2")
		return mario.copy(QRect(313, 348, 25, 30));

	else if (id == "cloud")
		return miscs.copy(QRect(309, 144, 16, 16));
	else if (id == "block")
		return miscs.copy(QRect(254, 188, 16, 16));

	else if (id == "KoopaTroopa-smashed-green-0")
		return enemies.copy(QRect(2*16, 48, 16, 16));
	else if (id == "KoopaTroopa-smashed-green-1")
		return enemies.copy(moveBy(QRect(2*16, 47, 16, 16), 0, 1, 16, 16));
	else if (id == "KoopaTroopa-kicked-green-0")
		return enemies.copy(QRect(2*16, 48, 16, 16));
	else if (id == "KoopaTroopa-kicked-green-1")
		return enemies.copy(moveBy(QRect(2*16, 48, 16, 16), 1, 0, 16, 16, 0, 0));
	else if (id == "KoopaTroopa-kicked-green-2")
		return enemies.copy(moveBy(QRect(2*16, 48, 16, 16), 2, 0, 16, 16, 0, 0));
	else if (id == "KoopaTroopa-kicked-green-3")
		return enemies.copy(moveBy(QRect(2*16, 48, 16, 16), 3, 0, 16, 16, 0, 0));

	else if (id == "PiranhaPlant-green-0")
		return enemies.copy(QRect(16*2, 144, 16, 23));
	else if (id == "PiranhaPlant-green-1")
		return enemies.copy(QRect(16*3, 144, 16, 23));
	else if (id == "PiranhaPlant-green-2")
		return enemies.copy(QRect(16*4, 144, 16, 23));
	else if (id == "PiranhaPlant-green-3")
		return enemies.copy(QRect(16*5, 144, 16, 23));

	else if (id == "VenusFireTrap-0")
		return enemies.copy(QRect(0, 144, 16, 23));
	else if (id == "VenusFireTrap-1")
		return enemies.copy(QRect(16, 144, 16, 23));

	else if (id == "brick-0")
	    return stage_tiles.copy(QRect(1038, 1, 16, 16));
	else if (id == "brick-1")
	    return stage_tiles.copy(moveBy(QRect(1038, 1, 16, 16), 1, 0));
	else if (id == "brick-2")
	    return stage_tiles.copy(moveBy(QRect(1038, 1, 16, 16), 2, 0));
	else if (id == "brick-3")
	    return stage_tiles.copy(moveBy(QRect(1038, 1, 16, 16), 3, 0));
	else if (id == "brick-debris-0")
	    return stage_tiles.copy(QRect(1089, 103, 8, 9));
	else if (id == "brick-debris-1")
	    return stage_tiles.copy(QRect(1098, 113, 8, 9));
	else if (id == "brick-debris-2")
	    return stage_tiles.copy(QRect(1107, 113, 8, 9));
	else if (id == "brick-debris-3")
	    return stage_tiles.copy(QRect(1116, 113, 8, 9));
	else if (id == "brick-grab-0")
	    return stage_tiles.copy(QRect(1157, 69, 16, 16));
	else if (id == "brick-grab-1")
	    return stage_tiles.copy(QRect(1140, 69, 16, 16));
	else if (id == "brick-grab-2")
	    return stage_tiles.copy(QRect(1123, 69, 16, 16));
	else if (id == "brick-grab-3")
	    return stage_tiles.copy(QRect(1106, 69, 16, 16));

	else if (id == "push-0")
	    return stage_tiles.copy(QRect(1174, 86, 16, 16));
	else if (id == "push-1")
	    return stage_tiles.copy(QRect(1191, 86, 16, 16));
	else if (id == "push-2")
	    return stage_tiles.copy(QRect(1208, 86, 16, 16));
	else if (id == "push-smitten")
	    return stage_tiles.copy(QRect(1225, 86, 16, 16));

	else if (id == "point-0")
	    return font.copy(QRect(60, 88, 12, 9));
	else if (id == "point-1")
	    return font.copy(QRect(74, 88, 13, 9));
	else if (id == "point-2")
	    return font.copy(QRect(89, 88, 12, 9));
	else if (id == "point-3")
	    return font.copy(QRect(104, 88, 17, 9));
	else if (id == "point-4")
	    return font.copy(QRect(119, 88, 17, 9));
	else if (id == "point-5")
	    return font.copy(QRect(137, 88, 17, 9));
	else if (id == "point-6")
	    return font.copy(QRect(156, 88, 17, 9));
	else if (id == "point-7")
	    return font.copy(QRect(175, 88, 17, 9));

	else if (id == "world")
	    return hud.copy(QRect(42, 32, 9, 7));
	else if (id == "M")
	    return hud.copy(QRect(9, 43, 17, 7));
	else if (id == "0")
	    return hud.copy(QRect(33, 32, 9, 7));
	else if (id == "1")
	    return hud.copy(QRect(44, 32, 9, 7));
	else if (id == "2")
	    return hud.copy(QRect(53, 32, 9, 7));
	else if (id == "3")
	    return hud.copy(QRect(63, 32, 9, 7));
	else if (id == "4")
	    return hud.copy(QRect(73, 32, 9, 7));
	else if (id == "5")
	    return hud.copy(QRect(83, 32, 9, 7));
	else if (id == "6")
	    return hud.copy(QRect(93, 32, 9, 7));
	else if (id == "7")
	    return hud.copy(QRect(103, 32, 9, 7));
	else if (id == "8")
	    return hud.copy(QRect(113, 32, 9, 7));
	else if (id == "9")
	    return hud.copy(QRect(123, 32, 9, 7));

	else if (id == "iconmushroom")
	    return hud.copy(QRect(187, 33, 23, 27));
	else if (id == "iconflower")
	    return hud.copy(QRect(211, 32, 23, 27));
	else if (id == "iconstar")
	    return hud.copy(QRect(236, 32, 23, 27));

	else if (id == "block-x")
	    return miscs.copy(QRect(175, 167, 16, 16));

	else if (id == "hud")
	    return hud.copy(QRect(3, 3, 232, 28));

	else if (id == "gameover-menu")
	    return gameover_menu.copy(QRect(4, 6, 128, 63));

	else if (id == "mario-comedown-small")
	    return mario.copy(QRect(127, 16, 16, 16));
	else if (id == "mario-comedown-big")
	    return mario.copy(QRect(213, 93, 16, 27));
	else if (id == "mario-comedown-racoon")
	    return mario.copy(QRect(357, 348, 16, 27));

	else if (id == "pipe-black-NW")
	    return stage_tiles.copy(QRect(1, 69, 16, 16));
	else if (id == "pipe-black-NE")
	    return stage_tiles.copy(QRect(18, 69, 16, 16));
	else if (id == "pipe-black-W")
	    return stage_tiles.copy(QRect(1, 86, 16, 16));
	else if (id == "pipe-black-E")
	    return stage_tiles.copy(QRect(18, 86, 16, 16));

	else
		return QPixmap();
}