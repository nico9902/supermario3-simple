#include <QApplication>
#include <QKeyEvent>
#include <QScrollBar>
#include <QWheelEvent>
#include <QSound>
#include <QThread>
#include "Game.h"
#include "Coin.h"
#include "Object.h"
#include "Entity.h"
#include "Brick.h"
#include "Mario.h"
#include "Sounds.h"
#include "Sprites.h"
#include "PiranhaPlant.h"
#include "Hud.h"
#include "ParaGoomba.h"
#include "KoopaTroopa.h"
#include "Enemy.h"

// Singleton design pattern
Game* Game::uniqueInstance = 0;
Game* Game::instance()
{
	if(uniqueInstance == 0)
		uniqueInstance = new Game();
	return uniqueInstance;
}


Game::Game(QGraphicsView *parent) : QGraphicsView(parent)
{
    // setup scene/view
	scene = new QGraphicsScene();
	setScene(scene);
	scale(3.0,3.0);
	centerOn(0,0);
	setInteractive(false);		// disables events
	setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
	setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
	scene->setSceneRect(0, 0, 176*16, 27*16);

    // setup game engine
    QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));
	engine.setInterval(15);
	engine.setTimerType(Qt::PreciseTimer);

	// setup game music
	music = new QSound(":/sounds/overworld.wav");
	music->setLoops(QSound::Infinite);

	// initialize mario
	mario = 0;

	// initialize score and other..
	score = 0;
	coinpoints = 0;
	time = 0;
	life = 1;
	mario_frame = -1;
	changescene = false;
	returnscene = false;

	// initialize hud
	hud = 0;
	layout = new QHBoxLayout();

	// reset game
	reset();

	// setup window size
	this->setFixedHeight(3*15*16);
	this->setFixedWidth(3*16*16);
}

// reset game
void Game::reset()
{
	cur_state = READY;

	// initialize items
	mario = 0;
	score = 0;
	time = 0;
	life = 1;
	coinpoints = 0;
	layout->removeWidget(hud);
	hud = 0;

	// stop music and game engine
	engine.stop();
	music->stop();

	// clear scene
	scene->clear();
	grid.clear();

	// display welcome message
	scene->setBackgroundBrush(QBrush(Qt::black));
	scene->addPixmap(Sprites::instance()->get("main-screen"));
	centerOn(0,0);
}

// game over
void Game::gameover()
{
	// stop death music
	Sounds::instance()->stop("death");

	// stop game
	cur_state = GAME_OVER;
	engine.stop();

	// set black background
	scene->setBackgroundBrush(QBrush(Qt::black));
	QGraphicsPixmapItem* item = scene->addPixmap(Sprites::instance()->get1("gameover-menu"));
	item->setPos(mario->x() - 50, mario->y() - 150);
	item->setZValue(10);
	centerOn(item);

	// play game over sound
	Sounds::instance()->play("gameover");
}

// start new game
void Game::start()
{
	if(cur_state == READY)
	{
		// clear and set scene
		scene->clear();
		scene->setSceneRect(0, 0, 176 * 16, 27 * 16);
		setScene(scene);
		engine.start();

		// load level
		mario = LevelManager::load("World-1-1", QPoint(1.5 * 16, 22 * 16), scene);

		//istance hud and QBoxLayout
		setLayout(layout);
		hud = new Hud();
		layout->addWidget(hud);
		layout->setContentsMargins(0, 10, 0, 0);

		// add debug grid
		for(int i=0; i<=15; i++)
			grid.push_back(new QGraphicsLineItem(0, i*16, 176*16, i*16));
		for(int j=0; j<=176; j++)
			grid.push_back(new QGraphicsLineItem(j*16, 0, j*16, 15*16));
		for(auto & l : grid)
		{
			l->setPen(QPen(QBrush(Qt::gray), 0.5));
			l->setZValue(100);			
			scene->addItem(l);
			l->setVisible(false);
		}

		if(!mario)
		{
			scene->setBackgroundBrush(QBrush(QColor(242,204,204)));
			QGraphicsTextItem* text = scene->addText("Error when loading level");
			text->setPos(300,90);
			centerOn(text);
		}
		else
			music->play();

		cur_state = RUNNING;
	}
	else if (cur_state = RUNNING) 
	{
		// if Mario dead, but his life is >0
		if (!changescene && !returnscene)
		{
			Sounds::instance()->stop("gameover");
			Sounds::instance()->stop("death");
			scene->clear();
			scene->setSceneRect(0, 0, 176 * 16, 27 * 16);
			setScene(scene);
			life--;
			mario = LevelManager::load("World-1-1", QPoint(1.5 * 16, 22 * 16), scene);
			music->play();
		}
		else
		{
			// if Mario go to Underground World
			if (changescene && !returnscene)
			{
				changescene = false;
				scene->clear();
				scene->setSceneRect(0, 0, 32 * 16, 13 * 16);
				setScene(scene);
				setInteractive(false);        // disables events
				setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
				setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

				// load level
				if (mario_frame == 0)
					mario = LevelManager::load("World-1-1-Underground", QPoint(8 * 16, 0 * 16), scene, 0);
				if (mario_frame == 1)
					mario = LevelManager::load("World-1-1-Underground", QPoint(8 * 16, 0 * 16), scene, 1);
				if (mario_frame == 2)
					mario = LevelManager::load("World-1-1-Underground", QPoint(8 * 16, 0 * 16), scene, 2);

				music->play();
			}
			// if Mario return to starting World
			else if(returnscene && !changescene)
			{
				returnscene = false;
				scene->clear();
				scene->setSceneRect(0, 0, 176 * 16, 27 * 16);
				setScene(scene);
				setInteractive(false);        // disables events

				// load level
				if (mario_frame == 0)
					mario = LevelManager::load("World-1-1-return", QPoint(147 * 16, 22 * 16), scene, 0);
				if (mario_frame == 1)
					mario = LevelManager::load("World-1-1-return", QPoint(147 * 16, 22 * 16), scene, 1);
				if (mario_frame == 2)
					mario = LevelManager::load("World-1-1-return", QPoint(147 * 16, 22 * 16), scene, 2);
				music->play();
			}
		}
	}
}

// pause / resume game
void Game::tooglePause()
{
	if(cur_state == RUNNING)
	{
		engine.stop();
		music->stop();
		cur_state = PAUSE;
		Sounds::instance()->play("pause");
	}
	else if(cur_state == PAUSE)
	{
		engine.start();
		music->play();
		cur_state = RUNNING;
	}
}

// show/ hide level grid
void Game::toogleGrid()
{
	for(auto & l : grid)
		l->setVisible(!l->isVisible());
}

// show/ hide object colliders
void Game::toogleColliders()
{
	for(auto & item : scene->items())
		if(dynamic_cast<Object*>(item))
			dynamic_cast<Object*>(item)->toogleColliderVisible();
}

// stop music
void Game::stopMusic()
{
	if(music)
		music->stop();
}

void Game::keyPressEvent(QKeyEvent *e)
{
	// ignore auto repeat key pressed/released
	// (same key has been pressed before and we already processed it)
	if(e->isAutoRepeat())
		return;

	// start new game
	if(e->key() == Qt::Key_Return && cur_state == READY)
		start();

	// reset game
	if(e->key() == Qt::Key_R || cur_state == GAME_OVER)
		reset();

	// pause game
	if(e->key() == Qt::Key_P)
		tooglePause();

	// show/hide grid game
	if(e->key() == Qt::Key_G)
		toogleGrid();

	// show/hide colliders
	if(e->key() == Qt::Key_C)
		toogleColliders();

	// from now on, all commands require the game to be running
	if(cur_state != RUNNING)
		return;

	// speed up / slow down
	if(e->key() == Qt::Key_Plus)
		engine.setInterval(engine.interval()/5);
	if(e->key() == Qt::Key_Minus)
		engine.setInterval(engine.interval()*5);

    // horizontal Mario's movements
    if(e->key() == Qt::Key_Right || e->key() == Qt::Key_Left)
	{
		mario->setDirection(e->key() == Qt::Key_Right ? Direction::RIGHT : Direction::LEFT);
        mario->setMoving(true);
    }
	if (e->key() == Qt::Key_Down)
		if(!mario->isPreComeDown())
			mario->setCrouch(true);
		else
			mario->setComeDown(true);

    // Mario's jump
    if(e->key() == Qt::Key_F && !mario->isDying())
        mario->jump();

	// Mario's running
	if(e->key() == Qt::Key_Z && !mario->isDying())
		mario->setRunning(true);

	// Mario's transformation
	if(e->key() == Qt::Key_T && !mario->isDying())
		mario->powerUp();

	// hurt every enemy
	//if(e->key() == Qt::Key_H)
	//	for(auto & item : scene->items())
	//	{
	//		Enemy* obj = dynamic_cast<Enemy*>(item);
	//		if(obj)
	//			obj->hurt();
	//	}

	// Mario round (only for Mario Racoon)
	if (e->key() == Qt::Key_X && mario->isRacoon() && !mario->isDying())
	{
		mario->setRound(true);
	}

	// Mario grab KoopaTroopa (or brick)
	if (e->key() == Qt::Key_V && !mario->isDying())
	{
		mario->setPregrab(true);
	}

	// Mario Racoon 
	if (e->key() == Qt::Key_B && !mario->isDying())
	{
		mario->setBig(true);
		mario->marioRacoon();
	}

	// Mario Racoon fly
	if (e->key() == Qt::Key_A && !mario->isDying() && mario->isPreFly())
	{
		if (!mario->isFly() && mario->isPreFly())
		{
			mario->setFly(true);
			mario->setPreFly(false);
		}
	}
}

void Game::keyReleaseEvent(QKeyEvent *e)
{
	// ignore auto repeat key pressed/released
	// (same key has been pressed before and we already processed it)
	if(e->isAutoRepeat())
		return;

	// from now on, all commands require the game to be running
	if(cur_state != RUNNING)
		return;

    // horizontal Mario's movements
    if(e->key() == Qt::Key_Right || e->key() == Qt::Key_Left)
        mario->setMoving(false);
	if(e->key() == Qt::Key_Down)
		mario->setCrouch(false);

	// Mario's running
	if(e->key() == Qt::Key_Z)
		mario->setRunning(false);

	// end grab
	if (e->key() == Qt::Key_V)
	{
		mario->setPregrab(false);
		if (mario->isGrab())
		{
			mario->setGrab(false);
			mario->setKick(true);
		}
	}

	if (e->key() == Qt::Key_F)
	{
		mario->startFalling();
	}
}

// zoom-in/out
void Game::wheelEvent(QWheelEvent *e)
{
    if(e->delta() > 0)
        scale(1.1, 1.1);
    else
        scale(1/1.1, 1/1.1);
}

void Game::advance()
{
	// do nothing if game is not running
	if(cur_state != RUNNING)
		return;

	// if mario is dead, game over
	if (mario->isDead() && life == 0) 
		gameover();
	else if (mario->isDead() && life > 0) 
		start();
	else if(!mario->isDead())
		timeincrease(1);

	if (changescene)
	{
		if (!mario->isBig())
			mario_frame = 0;
		if (mario->isRacoon())
			mario_frame = 1;
		if (mario->isBig() && !(mario->isRacoon()))
			mario_frame = 2;
		start();
	}

	if (returnscene)
	{
		if (!mario->isBig())
			mario_frame = 0;
		if (mario->isRacoon())
			mario_frame = 1;
		if (mario->isBig() && !(mario->isRacoon()))
			mario_frame = 2;
		start();
	}

	// if timer is out, the game is in gameover
	if (time >= 3 * 6600)
		gameover();

	// tell all game objects to animate and advance in the scene
    for(auto & item : scene->items())
    {
		Object* obj = dynamic_cast<Object*>(item);
		if(obj)
		{
			obj->animate();
			obj->advance();

			// destroy died Entity objects, except Mario
			Entity* entity_obj = dynamic_cast<Entity*>(obj);
			Mario* mario_obj = dynamic_cast<Mario*>(obj);
			if(entity_obj && !mario_obj && entity_obj->isDead())
			{
				scene->removeItem(entity_obj);
				delete entity_obj;
			}
		}
    }

    // center view on Mario
    centerOn(mario);
}

// freeze/unfreeze all entities
void Game::setFreezed(bool freezed, bool mario)
{
	// tell all game objects to animate and advance in the scene
	for(auto & item : scene->items())
	{
		Entity* obj = dynamic_cast<Entity*>(item);
		if (obj)
		{
			if (mario == false)
			{
				if (obj != dynamic_cast<Mario*>(item))
				{
					obj->setFreezed(freezed);
					obj->setMoving(false);
				}
			}
			else
			{
				if ((obj != dynamic_cast<PiranhaPlant*>(item)))
				{
					obj->setFreezed(freezed);
					//obj->setMoving(freezed ? false : true);
				}
			}
		} 
	}
}

void Game::swap()
{
	// tell all game objects to swap bricks with coins
	for (auto & item : scene->items())
	{
		Brick* obj = dynamic_cast<Brick*>(item);
		KoopaTroopa* koopa = dynamic_cast<KoopaTroopa*>(item);
		if (obj && !obj->isContainer())
		{
			obj->setVisible(false);
			new Coin(QPoint(obj->x(), obj->y()));
			scene->removeItem(obj);
		}

		if (koopa && koopa->isWalkOnBrick())
		{
			koopa->setFalling(true);
		}
	}
}