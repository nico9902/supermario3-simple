#pragma once

#include "Background.h"
#include "Coin.h"
#include <QWidget>
#include <QString>
#include <QTimer>

class Hud : public QWidget 
{
	Q_OBJECT;
	
	private:
	
	    QTimer _timer;              // timer of the game 
	    int score;                  // score of player
		int coinpoints;             // number of coins caught by Mario
		int time;                   // time
		int life;                   // number of Mario's lifes
		QPixmap texture_coin[10];
		QPixmap texture_time[10];
	
	public:
	
	    Hud(QWidget *parent = 0);
		
		virtual void paintEvent(QPaintEvent *e);
		
		public slots:
		
		     void advance();
};
