#include "LevelManager.h"
#include <iostream>

#include "Background.h"
#include "Base.h"
#include "Mario.h"
#include "Sprites.h"
#include "Terrain.h"
#include "Pipe.h"
#include "Block.h"
#include "Coin.h"
#include "Goomba.h"
#include "ParaGoomba.h"
#include "KoopaParaTroopa.h"
#include "SecretBox.h"
#include "KoopaTroopa.h"
#include "PiranhaPlant.h"
#include "HappyCloud.h"
#include "VenusFireTrap.h"
#include "Brick.h"

#include <QSoundEffect>

// load all items from the given level in the given scene
Mario* LevelManager::load(std::string level_name, QPoint position, QGraphicsScene * scene, int mario_frame)
{
    Mario* mario = 0;

    if(level_name == "World-1-1")
    {
        // set background color
        scene->setBackgroundBrush(QBrush(QColor(180,241,241)));

		// terrain level
		int terrain_level = 23*16;

        // terrain
		new Terrain(QRect(0, terrain_level, 39*16, 1*16));
		new Terrain(QRect(39*16, terrain_level-16, 29*16, 32));
		new Terrain(QRect(72*16, terrain_level, 352, 1*16));
		new Terrain(QRect(96*16, terrain_level, 5*16, 1*16));
		new Terrain(QRect(104*16, terrain_level, 36*16, 1*16));
		new Terrain(QRect(141*16, terrain_level, 35*16, 1*16));

		// brushes
		new Background(QPoint( 1*16,terrain_level),   ":/graphics/background/brush-big.png");
		new Background(QPoint(10*16,terrain_level), Sprites::instance()->get("brush-small"));
		new Background(QPoint(11*16,terrain_level), Sprites::instance()->get("brush-small"));
		new Background(QPoint(12*16,terrain_level), Sprites::instance()->get("brush-small"));
		new Background(QPoint(74 * 16, terrain_level), Sprites::instance()->get("brush-small"));
		new Background(QPoint(75 * 16, terrain_level), Sprites::instance()->get("brush-small"));
		new Background(QPoint(76 * 16, terrain_level), Sprites::instance()->get("brush-small"));
		new Background(QPoint(51 * 16, terrain_level), ":/graphics/background/brush-big.png");
		new Background(QPoint(65 * 16, terrain_level - 1*16), Sprites::instance()->get("brush-small"));
		new Background(QPoint(66 * 16, terrain_level - 1*16), Sprites::instance()->get("brush-small"));
		new Background(QPoint(108 * 16, terrain_level), Sprites::instance()->get("brush-small"));
		new Background(QPoint(109 * 16, terrain_level), Sprites::instance()->get("brush-small"));
		new Background(QPoint(110 * 16, terrain_level), Sprites::instance()->get("brush-small"));

		// clouds
		new HappyCloud(QPoint(88 * 16, terrain_level - 13 * 16));
		new HappyCloud(QPoint(89 * 16, terrain_level - 13 * 16));
		new HappyCloud(QPoint(90 * 16, terrain_level - 13 * 16));
		new HappyCloud(QPoint(91 * 16, terrain_level - 13 * 16));
		new HappyCloud(QPoint(94 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(95 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(96 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(97 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(98 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(99 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(100 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(101 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(102 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(103 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(104 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(105 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(106 * 16, terrain_level - 14 * 16));

		// blocks
		new Block(QPoint(94 * 16, terrain_level - 16 * 4));
		new Block(QPoint(95 * 16, terrain_level - 16 * 4));
		new Block(QPoint(98 * 16, terrain_level - 16 * 1));
		new Block(QPoint(99 * 16, terrain_level - 16 * 1));
		new Block(QPoint(100 * 16, terrain_level - 16 * 1));
		new Block(QPoint(99 * 16, terrain_level - 16 * 2));
		new Block(QPoint(100 * 16, terrain_level - 16 * 2));
		new Block(QPoint(100 * 16, terrain_level - 16 * 3));
		new Block(QPoint(104 * 16, terrain_level - 16 * 3));
		new Block(QPoint(104 * 16, terrain_level - 16 * 2));
		new Block(QPoint(105 * 16, terrain_level - 16 * 2));
		new Block(QPoint(104 * 16, terrain_level - 16 * 1));
		new Block(QPoint(105 * 16, terrain_level - 16 * 1));
		new Block(QPoint(106 * 16, terrain_level - 16 * 1));
		new Block(QPoint(141 * 16, terrain_level - 16 * 7));
		new Block(QPoint(142 * 16, terrain_level - 16 * 7));
		new Block(QPoint(141 * 16, terrain_level - 16 * 3));
		new Block(QPoint(142 * 16, terrain_level - 16 * 3));

		// secret boxes
		new SecretBox(QPoint(9*16, terrain_level - 2*16));
		new SecretBox(QPoint(11*16, terrain_level-3*16));
		new SecretBox(QPoint(12*16, terrain_level-3*16));
		new SecretBox(QPoint(14*16, terrain_level-6*16));
		new SecretBox(QPoint(15*16, terrain_level-6*16), LEAF);
		new SecretBox(QPoint(41*16, terrain_level-1*16), LEAF);
		new SecretBox(QPoint(44*16, terrain_level-3*16));
		new SecretBox(QPoint(92*16, terrain_level-2*16), LEAF);
		new SecretBox(QPoint(90*16, terrain_level-18*16), LIFE);

		// bases
		new Base("lightblue", QRect(17*16, terrain_level, 3*16, 5*16));
		new BaseShadow(       QRect(20*16, terrain_level, 1*16, 5*16));
		new Base("pink",      QRect(15*16, terrain_level, 3*16, 3*16));
		new BaseShadow(       QRect(18*16, terrain_level, 1*16, 3*16));
		new Base("white",     QRect(32*16, terrain_level, 4*16, 7*16));
		new BaseShadow(       QRect(36*16, terrain_level, 1*16, 7*16));
		new Base("pink",      QRect(29*16, terrain_level, 4*16, 5*16));
		new BaseShadow(       QRect(33*16, terrain_level, 1*16, 5*16));
		new Base("green",     QRect(25*16, terrain_level, 5*16, 3*16));
		new BaseShadow(       QRect(30*16, terrain_level, 1*16, 3*16));
		new Base("green",     QRect(32*16, terrain_level, 6*16, 2*16));
		new BaseShadow(       QRect(38*16, terrain_level, 1*16, 2*16));
		new Base("lightblue", QRect(83 * 16, terrain_level, 7 * 16, 6 * 16));
		new Base("pink", QRect(81 * 16, terrain_level, 7 * 16, 4 * 16));
		new Base("green", QRect(79 * 16, terrain_level, 7 * 16, 2 * 16));
		new Base("pink", QRect(82 * 16, terrain_level - 15*16, 4 * 16, 2 * 16));
		new BaseShadow(QRect(86 * 16, terrain_level, 1 * 16, 2 * 16));
		new BaseShadow(QRect(88 * 16, terrain_level, 1 * 16, 4 * 16));
		new BaseShadow(QRect(90 * 16, terrain_level, 1 * 16, 6 * 16));
		new Base("green", QRect(136 * 16, terrain_level, 3 * 16, 8 * 16));
		new Base("pink", QRect(134 * 16, terrain_level, 3 * 16, 3 * 16));
		new BaseShadow(QRect(137 * 16, terrain_level, 1 * 16, 3 * 16));
		new BaseShadow(QRect(139 * 16, terrain_level, 1 * 16, 8 * 16));

		// bricks
		new Brick(QPoint(122 * 16, terrain_level - 1*16));
		new Brick(QPoint(123 * 16, terrain_level - 1*16));
		new Brick(QPoint(123 * 16, terrain_level - 2*16));
		new Brick(QPoint(124 * 16, terrain_level - 1*16));
		new Brick(QPoint(124 * 16, terrain_level - 2*16));
		new Brick(QPoint(124 * 16, terrain_level - 3*16));
		new Brick(QPoint(125 * 16, terrain_level - 1*16));
		new Brick(QPoint(125 * 16, terrain_level - 2*16));
		new Brick(QPoint(125 * 16, terrain_level - 3*16));
		new Brick(QPoint(126 * 16, terrain_level - 1*16));
		new Brick(QPoint(126 * 16, terrain_level - 2*16));
		new Brick(QPoint(126 * 16, terrain_level - 3*16));
		new Brick(QPoint(127 * 16, terrain_level - 1 * 16));
		new Brick(QPoint(127 * 16, terrain_level - 2 * 16));
		new Brick(QPoint(127 * 16, terrain_level - 3 * 16), true);
		new Brick(QPoint(128 * 16, terrain_level - 1 * 16));
		new Brick(QPoint(131 * 16, terrain_level - 1 * 16));
		new Brick(QPoint(131 * 16, terrain_level - 2 * 16));
		new Brick(QPoint(132 * 16, terrain_level - 1 * 16));

		// pipes
		new Pipe(QPoint(22*16, terrain_level), 2);
		new Pipe(QPoint(116*16, terrain_level), 2);
		new Pipe(QPoint(112*16, terrain_level), 1);
		new Pipe(QPoint(141*16, terrain_level - 16 * 7), 11);
		new Pipe(QPoint(141*16, terrain_level), 1);
		new Pipe(QPoint(147*16, terrain_level), 1);

		// clouds
		new Background(QPoint(8*16,4*16),   ":/graphics/background/cloud-2.png");
		new Background(QPoint(21*16,5*16),   ":/graphics/background/cloud-1.png");
		new Background(QPoint(103*16,terrain_level - 8*16),   ":/graphics/background/cloud-2.png");

		// enemies
		new Goomba(QPoint(14*16, terrain_level), LEFT);
		new Goomba(QPoint(820, terrain_level - 2 * 16), LEFT, false, false, 0);
		new Goomba(QPoint(870, terrain_level - 2*16), LEFT, false, false, 0);
		new ParaGoomba(QPoint(945, terrain_level - 2*16),
			new Wing(QPoint(945, terrain_level - 2*16 - 10)),
			new Wing(QPoint(945, terrain_level - 2*16 - 10), false), LEFT);
		new PiranhaPlant(QPoint(360, terrain_level));
		new PiranhaPlant(QPoint(116*16 + 8, terrain_level), LEFT, true);
		new Goomba(QPoint(33*16, terrain_level), LEFT);
		new KoopaTroopa(QPoint(579, terrain_level - 3 * 16), LEFT);
		new KoopaTroopa(QPoint(92*16, terrain_level), LEFT, true);
		new KoopaParaTroopa(QPoint(83 * 16, terrain_level - 6 * 16),
			new Wing(QPoint(83*16, terrain_level - 6 * 16 - 10), false, RIGHT, true), LEFT);
		new KoopaParaTroopa(QPoint(86 * 16, terrain_level - 6 * 16),
			new Wing(QPoint(86 * 16, terrain_level - 6 * 16 - 10), false, RIGHT, true), LEFT);
		new KoopaParaTroopa(QPoint(89 * 16, terrain_level - 6 * 16),
			new Wing(QPoint(89 * 16, terrain_level - 6 * 16 - 10), false, RIGHT, true), LEFT);
		new VenusFireTrap(QPoint(1800, terrain_level));
		new KoopaTroopa(QPoint(131*16, terrain_level - 2 * 16), LEFT, false, true);
	
        // Mario
		mario = new Mario(position);
		if (mario_frame == 1)
		{
			mario->setRacoon(true);
			mario->setBig(true);
		}
		if (mario_frame == 2)
			mario->setBig(true);
		
    }
	else if (level_name == "World-1-1-Underground") 
    {
		// terrain level
		int terrain_level = 12 * 16;
		scene->setBackgroundBrush(QBrush(Qt::black));

		// blocks
		for (int i = -1; i <10; i++)
		{
			new Block(QPoint(0 * 16, i * 16), true);
			new Block(QPoint(1 * 16, i * 16), true);
			new Block(QPoint(2 * 16, i * 16), true);
			new Block(QPoint(3 * 16, i * 16), true);
			new Block(QPoint(4 * 16, i * 16), true);
			new Block(QPoint(5 * 16, i * 16), true);
			new Block(QPoint(6 * 16, i * 16), true);
			new Block(QPoint(7 * 16, i * 16), true);
		}
		for (int i = 0; i < 32; i++)
		{
			new Block(QPoint(i * 16, 9 * 16), true);
			new Block(QPoint(i * 16, 10 * 16), true);
		}

		for (int i = 16; i < 32; i++)
		{
			new Block(QPoint(i * 16, 8 * 16), true);
		}

		for (int i = 17; i < 32; i++)
		{
			new Block(QPoint(i * 16, 7 * 16), true);
		}

		for (int i = 18; i < 32; i++)
		{
			new Block(QPoint(i * 16, 6 * 16), true);
		}

		for (int i = 19; i < 32; i++)
		{
			new Block(QPoint(i * 16, 5 * 16), true);
		}

		for (int i = 20; i < 32; i++)
		{
			new Block(QPoint(i * 16, 4 * 16), true);
		}

		for (int i = 21; i < 32; i++)
		{
			new Block(QPoint(i * 16, 3 * 16), true);
		}

		for (int i = 24; i < 32; i++)
		{
			new Block(QPoint(i * 16, 2 * 16), true);
			new Block(QPoint(i * 16, 1 * 16), true);
			new Block(QPoint(i * 16, 0 * 16), true);
			new Block(QPoint(i * 16, -1 * 16), true);
		}

		for (int i = 10; i <= 21; i++)
		{
			new Block(QPoint(i * 16, -1 * 16), true);
		}

		// Pipes
		new Pipe(QPoint(8 * 16, 1*16), 1, true);
		new Pipe(QPoint(22 * 16, 1*16), 1, true, true);

		// Coins
		new Coin(QPoint(14 * 16, 16 + 8));
		new Coin(QPoint(15 * 16, 16 + 8));
		new Coin(QPoint(13 * 16, 2*16 + 8));
		new Coin(QPoint(16 * 16, 2*16 + 8));
		new Coin(QPoint(16 * 16, 3*16 + 8));
		new Coin(QPoint(14 * 16, 4*16 + 8));
		new Coin(QPoint(15 * 16, 4*16 + 8));
		new Coin(QPoint(16 * 16, 5*16 + 8));
		new Coin(QPoint(16 * 16, 6*16 + 8));
		new Coin(QPoint(13 * 16, 6*16 + 8));
		new Coin(QPoint(14 * 16, 7*16 + 8));
		new Coin(QPoint(15 * 16, 7*16 + 8));

		// mario
		mario = new Mario(position);
		if (mario_frame == 1) 
		{
			mario->setRacoon(true);
			mario->setBig(true);
		}
		if (mario_frame == 2)
			mario->setBig(true);
	}
	else if (level_name == "World-1-1-return")
	{
		// set background color
		scene->setBackgroundBrush(QBrush(QColor(180, 241, 241)));

		// terrain level
		int terrain_level = 23 * 16;

		// terrain
		new Terrain(QRect(0, terrain_level, 39 * 16, 1 * 16));
		new Terrain(QRect(39 * 16, terrain_level - 16, 29 * 16, 32));
		new Terrain(QRect(72 * 16, terrain_level, 352, 1 * 16));
		new Terrain(QRect(96 * 16, terrain_level, 5 * 16, 1 * 16));
		new Terrain(QRect(104 * 16, terrain_level, 36 * 16, 1 * 16));
		new Terrain(QRect(141 * 16, terrain_level, 35 * 16, 1 * 16));

		// brushes
		new Background(QPoint(1 * 16, terrain_level), ":/graphics/background/brush-big.png");
		new Background(QPoint(10 * 16, terrain_level), Sprites::instance()->get("brush-small"));
		new Background(QPoint(11 * 16, terrain_level), Sprites::instance()->get("brush-small"));
		new Background(QPoint(12 * 16, terrain_level), Sprites::instance()->get("brush-small"));
		new Background(QPoint(74 * 16, terrain_level), Sprites::instance()->get("brush-small"));
		new Background(QPoint(75 * 16, terrain_level), Sprites::instance()->get("brush-small"));
		new Background(QPoint(76 * 16, terrain_level), Sprites::instance()->get("brush-small"));
		new Background(QPoint(51 * 16, terrain_level), ":/graphics/background/brush-big.png");
		new Background(QPoint(65 * 16, terrain_level - 1 * 16), Sprites::instance()->get("brush-small"));
		new Background(QPoint(66 * 16, terrain_level - 1 * 16), Sprites::instance()->get("brush-small"));
		new Background(QPoint(108 * 16, terrain_level), Sprites::instance()->get("brush-small"));
		new Background(QPoint(109 * 16, terrain_level), Sprites::instance()->get("brush-small"));
		new Background(QPoint(110 * 16, terrain_level), Sprites::instance()->get("brush-small"));

		// clouds
		new HappyCloud(QPoint(88 * 16, terrain_level - 13 * 16));
		new HappyCloud(QPoint(89 * 16, terrain_level - 13 * 16));
		new HappyCloud(QPoint(90 * 16, terrain_level - 13 * 16));
		new HappyCloud(QPoint(91 * 16, terrain_level - 13 * 16));
		new HappyCloud(QPoint(94 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(95 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(96 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(97 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(98 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(99 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(100 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(101 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(102 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(103 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(104 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(105 * 16, terrain_level - 14 * 16));
		new HappyCloud(QPoint(106 * 16, terrain_level - 14 * 16));

		// blocks
		new Block(QPoint(94 * 16, terrain_level - 16 * 4));
		new Block(QPoint(95 * 16, terrain_level - 16 * 4));
		new Block(QPoint(98 * 16, terrain_level - 16 * 1));
		new Block(QPoint(99 * 16, terrain_level - 16 * 1));
		new Block(QPoint(100 * 16, terrain_level - 16 * 1));
		new Block(QPoint(99 * 16, terrain_level - 16 * 2));
		new Block(QPoint(100 * 16, terrain_level - 16 * 2));
		new Block(QPoint(100 * 16, terrain_level - 16 * 3));
		new Block(QPoint(104 * 16, terrain_level - 16 * 3));
		new Block(QPoint(104 * 16, terrain_level - 16 * 2));
		new Block(QPoint(105 * 16, terrain_level - 16 * 2));
		new Block(QPoint(104 * 16, terrain_level - 16 * 1));
		new Block(QPoint(105 * 16, terrain_level - 16 * 1));
		new Block(QPoint(106 * 16, terrain_level - 16 * 1));
		new Block(QPoint(141 * 16, terrain_level - 16 * 7));
		new Block(QPoint(142 * 16, terrain_level - 16 * 7));
		new Block(QPoint(141 * 16, terrain_level - 16 * 3));
		new Block(QPoint(142 * 16, terrain_level - 16 * 3));

		// secret boxes
		new SecretBox(QPoint(9 * 16, terrain_level - 2 * 16));
		new SecretBox(QPoint(11 * 16, terrain_level - 3 * 16));
		new SecretBox(QPoint(12 * 16, terrain_level - 3 * 16));
		new SecretBox(QPoint(14 * 16, terrain_level - 6 * 16));
		new SecretBox(QPoint(15 * 16, terrain_level - 6 * 16), LEAF);
		new SecretBox(QPoint(41 * 16, terrain_level - 1 * 16), LEAF);
		new SecretBox(QPoint(44 * 16, terrain_level - 3 * 16));
		new SecretBox(QPoint(92 * 16, terrain_level - 2 * 16), LEAF);
		new SecretBox(QPoint(90 * 16, terrain_level - 18 * 16), LIFE);

		// bases
		new Base("lightblue", QRect(17 * 16, terrain_level, 3 * 16, 5 * 16));
		new BaseShadow(QRect(20 * 16, terrain_level, 1 * 16, 5 * 16));
		new Base("pink", QRect(15 * 16, terrain_level, 3 * 16, 3 * 16));
		new BaseShadow(QRect(18 * 16, terrain_level, 1 * 16, 3 * 16));
		new Base("white", QRect(32 * 16, terrain_level, 4 * 16, 7 * 16));
		new BaseShadow(QRect(36 * 16, terrain_level, 1 * 16, 7 * 16));
		new Base("pink", QRect(29 * 16, terrain_level, 4 * 16, 5 * 16));
		new BaseShadow(QRect(33 * 16, terrain_level, 1 * 16, 5 * 16));
		new Base("green", QRect(25 * 16, terrain_level, 5 * 16, 3 * 16));
		new BaseShadow(QRect(30 * 16, terrain_level, 1 * 16, 3 * 16));
		new Base("green", QRect(32 * 16, terrain_level, 6 * 16, 2 * 16));
		new BaseShadow(QRect(38 * 16, terrain_level, 1 * 16, 2 * 16));
		new Base("lightblue", QRect(83 * 16, terrain_level, 7 * 16, 6 * 16));
		new Base("pink", QRect(81 * 16, terrain_level, 7 * 16, 4 * 16));
		new Base("green", QRect(79 * 16, terrain_level, 7 * 16, 2 * 16));
		new Base("pink", QRect(82 * 16, terrain_level - 15 * 16, 4 * 16, 2 * 16));
		new BaseShadow(QRect(86 * 16, terrain_level, 1 * 16, 2 * 16));
		new BaseShadow(QRect(88 * 16, terrain_level, 1 * 16, 4 * 16));
		new BaseShadow(QRect(90 * 16, terrain_level, 1 * 16, 6 * 16));
		new Base("green", QRect(136 * 16, terrain_level, 3 * 16, 8 * 16));
		new Base("pink", QRect(134 * 16, terrain_level, 3 * 16, 3 * 16));
		new BaseShadow(QRect(137 * 16, terrain_level, 1 * 16, 3 * 16));
		new BaseShadow(QRect(139 * 16, terrain_level, 1 * 16, 8 * 16));

		// bricks
		new Brick(QPoint(122 * 16, terrain_level - 1 * 16));
		new Brick(QPoint(123 * 16, terrain_level - 1 * 16));
		new Brick(QPoint(123 * 16, terrain_level - 2 * 16));
		new Brick(QPoint(124 * 16, terrain_level - 1 * 16));
		new Brick(QPoint(124 * 16, terrain_level - 2 * 16));
		new Brick(QPoint(124 * 16, terrain_level - 3 * 16));
		new Brick(QPoint(125 * 16, terrain_level - 1 * 16));
		new Brick(QPoint(125 * 16, terrain_level - 2 * 16));
		new Brick(QPoint(125 * 16, terrain_level - 3 * 16));
		new Brick(QPoint(126 * 16, terrain_level - 1 * 16));
		new Brick(QPoint(126 * 16, terrain_level - 2 * 16));
		new Brick(QPoint(126 * 16, terrain_level - 3 * 16));
		new Brick(QPoint(127 * 16, terrain_level - 1 * 16));
		new Brick(QPoint(127 * 16, terrain_level - 2 * 16));
		new Brick(QPoint(127 * 16, terrain_level - 3 * 16), true);
		new Brick(QPoint(128 * 16, terrain_level - 1 * 16));
		new Brick(QPoint(131 * 16, terrain_level - 1 * 16));
		new Brick(QPoint(131 * 16, terrain_level - 2 * 16));
		new Brick(QPoint(132 * 16, terrain_level - 1 * 16));

		// pipes
		new Pipe(QPoint(22 * 16, terrain_level), 2);
		new Pipe(QPoint(116 * 16, terrain_level), 2);
		new Pipe(QPoint(112 * 16, terrain_level), 1);
		new Pipe(QPoint(141 * 16, terrain_level - 16 * 7), 11);
		new Pipe(QPoint(141 * 16, terrain_level), 1);
		new Pipe(QPoint(147 * 16, terrain_level), 1);

		// clouds
		new Background(QPoint(8 * 16, 4 * 16), ":/graphics/background/cloud-2.png");
		new Background(QPoint(21 * 16, 5 * 16), ":/graphics/background/cloud-1.png");
		new Background(QPoint(103 * 16, terrain_level - 8 * 16), ":/graphics/background/cloud-2.png");

		// enemies
		new Goomba(QPoint(14 * 16, terrain_level), LEFT);
		new Goomba(QPoint(820, terrain_level - 2 * 16), LEFT, false, false, 0);
		new Goomba(QPoint(870, terrain_level - 2 * 16), LEFT, false, false, 0);
		new ParaGoomba(QPoint(945, terrain_level - 2 * 16),
			new Wing(QPoint(945, terrain_level - 2 * 16 - 10)),
			new Wing(QPoint(945, terrain_level - 2 * 16 - 10), false), LEFT);
		new PiranhaPlant(QPoint(360, terrain_level));
		new PiranhaPlant(QPoint(116 * 16 + 8, terrain_level), LEFT, true);
		new Goomba(QPoint(33 * 16, terrain_level), LEFT);
		new KoopaTroopa(QPoint(579, terrain_level - 3 * 16), LEFT);
		new KoopaTroopa(QPoint(92 * 16, terrain_level), LEFT, true);
		new KoopaParaTroopa(QPoint(83 * 16, terrain_level - 6 * 16),
			new Wing(QPoint(83 * 16, terrain_level - 6 * 16 - 10), false, RIGHT, true), LEFT);
		new KoopaParaTroopa(QPoint(86 * 16, terrain_level - 6 * 16),
			new Wing(QPoint(86 * 16, terrain_level - 6 * 16 - 10), false, RIGHT, true), LEFT);
		new KoopaParaTroopa(QPoint(89 * 16, terrain_level - 6 * 16),
			new Wing(QPoint(89 * 16, terrain_level - 6 * 16 - 10), false, RIGHT, true), LEFT);
		new VenusFireTrap(QPoint(1800, terrain_level));
		new KoopaTroopa(QPoint(131 * 16, terrain_level - 2 * 16), LEFT, false, true);

		// Mario
		mario = new Mario(position, true);
		if (mario_frame == 1)
		{
			mario->setRacoon(true);
			mario->setBig(true);
		}
		if (mario_frame == 2)
			mario->setBig(true);

	}
    else
        std::cerr << "Level not implemented";

    return mario;
}
