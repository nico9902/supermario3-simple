#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QTimer>
#include <QSound>
#include <QLayout>

#include "Hud.h"
#include "Mario.h"
#include "LevelManager.h"

class Game : public QGraphicsView 
{ 
	Q_OBJECT 
	
	enum game_state{READY, RUNNING, PAUSE, GAME_OVER};

	private:

		static Game* uniqueInstance;	// Singleton design pattern
		Game(QGraphicsView *parent=0);	// Singleton design pattern

        QGraphicsScene *scene;          // the scene used to render the game (2D)
		Hud *hud;						// hud object
        Mario *mario;                   // mario object
        QTimer engine;                  // game engine / timer
		game_state cur_state;           // current game state
		QSound *music;					// game music
		std::vector <QGraphicsLineItem*> grid;		// scene grid (for debugging)
		QHBoxLayout *layout;            // layout
		int score;                      // score of level
		int time;                       // time
		int life;                       // Mario's life
		int coinpoints;                 // number of coins caught by Mario
		int mario_frame;                // Mario's state (Big, Racoon, Small)
		bool changescene;               // wheter Mario go in Underground World
		bool returnscene;               // wheter Mario return to starting World

	protected:

        // the game is controlled using the keyboard
        // hence we have to intercept all keyboard events
		virtual void keyPressEvent(QKeyEvent *e);
		virtual void keyReleaseEvent(QKeyEvent *e);

        // zoom-in/out (for debug)
        virtual void wheelEvent(QWheelEvent *e);

	public: 
		
		// singleton unique instance getter
		static Game* instance();

		// getters
		QGraphicsScene* getScene(){return scene;}
		Mario* getMario() { return mario; }
		game_state getState() { return cur_state; }
		int getScore() { return score; }
		int getCoinPoints() { return coinpoints; }
		int getTime() { return time; }
		int getLife() { return life; }

		//setters
		void setLife(int _life) { life = _life; }
		void setChangeScene(bool _changescene) { changescene = _changescene; }
		void setReturnScene(bool _returnscene) { returnscene = _returnscene; }

		// utility methods
		void scorechanged(int points) { score += points;}
		void coinpointschanged(int points) { coinpoints += points;}
		void timeincrease(int points) { time += points;}


	public slots:

        // advance game / next frame
        void advance();

		// pause / resume game
		void tooglePause();

		// show/ hide level grid
		void toogleGrid();

		// show/ hide object colliders
		void toogleColliders();

		// reset game
		void reset();

		// start new game
		void start();

		// game over
		void gameover();

		// freeze/unfreeze all entities
		void setFreezed(bool freezed, bool mario = true);

		// stop music
		void stopMusic();

		// switch (swap brick with coin)
		void swap();
};
