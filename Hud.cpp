#include "Hud.h"
#include "Game.h"
#include "Sprites.h"
#include "KoopaTroopa.h"
#include <QLabel>


Hud::Hud(QWidget *parent) : QWidget(parent) 
{
	// set attributes
	score = Game::instance()->getScore();
	coinpoints = Game::instance()->getCoinPoints();
	time = Game::instance()->getTime();
	life = Game::instance()->getLife();
	
	// set textures
	texture_coin[0] = Sprites::instance()->get1("0");
	texture_coin[1] = Sprites::instance()->get1("1");
	texture_coin[2] = Sprites::instance()->get1("2");
	texture_coin[3] = Sprites::instance()->get1("3");
	texture_coin[4] = Sprites::instance()->get1("4");
	texture_coin[5] = Sprites::instance()->get1("5");
	texture_coin[6] = Sprites::instance()->get1("6");
	texture_coin[7] = Sprites::instance()->get1("7");
	texture_coin[8] = Sprites::instance()->get1("8");
	texture_coin[9] = Sprites::instance()->get1("9");
	texture_time[0] = Sprites::instance()->get1("9");
	texture_time[1] = Sprites::instance()->get1("8");
	texture_time[2] = Sprites::instance()->get1("7");
	texture_time[3] = Sprites::instance()->get1("6");
	texture_time[4] = Sprites::instance()->get1("5");
	texture_time[5] = Sprites::instance()->get1("4");
	texture_time[6] = Sprites::instance()->get1("3");
	texture_time[7] = Sprites::instance()->get1("2");
	texture_time[8] = Sprites::instance()->get1("1");
	texture_time[9] = Sprites::instance()->get1("0");

	connect(&_timer, SIGNAL(timeout()), this, SLOT(advance()));
	_timer.setInterval(15);
	_timer.start();
}

void Hud::paintEvent(QPaintEvent *e) 
{
	if(Game::instance()->getState() != 0)
	{
		QPainter painter(this);
		painter.fillRect(0 * 16, 35 * 16 + 4, 60 * 16 + 4, 10 * 16, Qt::black);
		painter.setBrush(Qt::red);
		painter.drawPixmap(1 * 16, 36 * 16, 45 * 16 + 4, 6 * 16, Sprites::instance()->get1("hud"));
		painter.fillRect(8 * 16, 37 * 16 + 8, 2 * 16, 2 * 16 - 8, QColor(175, 232, 226));
		painter.fillRect(27 * 16 - 4, 37 * 16 + 8, 3 * 16 + 2, 2 * 16 - 8, QColor(175, 232, 226));
		painter.fillRect(25 * 16 + 2, 39 * 16 + 3, 4 * 16 + 12, 2 * 16 - 8, QColor(175, 232, 226));
	    painter.fillRect(11 * 16 + 2, 39 * 16 + 3, 11 * 16, 2 * 16 - 8, QColor(175, 232, 226));
	    painter.fillRect(7 * 16 - 6, 39 * 16 + 3, 3 * 16 + 2, 2 * 16 - 8, QColor(175, 232, 226));
	    painter.drawPixmap(8 * 16, 37 * 16 + 11, 2 * 16, 1 * 16 + 4, Sprites::instance()->get1("world"));
	    painter.drawPixmap(2 * 16, 39 * 16 + 4, 3 * 16 + 4, 1 * 16 + 6, Sprites::instance()->get1("M"));
	if (coinpoints >= 0 && coinpoints < 10)
		painter.drawPixmap(440, 600, 2 * 16, 1 * 16 + 4, texture_coin[coinpoints]);
	else if (coinpoints >= 10 && coinpoints < 20) 
	{
		painter.drawPixmap(430, 600, 2 * 16, 1 * 16 + 4, texture_coin[1]);
		painter.drawPixmap(453, 600, 2 * 16, 1 * 16 + 4, texture_coin[coinpoints - 10]);
	}
	else if (coinpoints >= 20 && coinpoints < 30) 
	{
		painter.drawPixmap(430, 600, 2 * 16, 1 * 16 + 4, texture_coin[2]);
		painter.drawPixmap(453, 600, 2 * 16, 1 * 16 + 4, texture_coin[coinpoints - 20]);
	}
	else if (coinpoints >= 30 && coinpoints < 40) 
	{
		painter.drawPixmap(430, 600, 2 * 16, 1 * 16 + 4, texture_coin[3]);
		painter.drawPixmap(453, 600, 2 * 16, 1 * 16 + 4, texture_coin[coinpoints - 30]);
	}
	else if (coinpoints >= 40 && coinpoints < 50) 
	{
		painter.drawPixmap(430, 600, 2 * 16, 1 * 16 + 4, texture_coin[4]);
		painter.drawPixmap(453, 600, 2 * 16, 1 * 16 + 4, texture_coin[coinpoints - 40]);
	}
	else if (coinpoints >= 50 && coinpoints < 60) 
	{
		painter.drawPixmap(430, 600, 2 * 16, 1 * 16 + 4, texture_coin[5]);
		painter.drawPixmap(453, 600, 2 * 16, 1 * 16 + 4, texture_coin[coinpoints - 50]);
	}
	else if (coinpoints >= 60 && coinpoints < 70) 
	{
		painter.drawPixmap(430, 600, 2 * 16, 1 * 16 + 4, texture_coin[6]);
		painter.drawPixmap(453, 600, 2 * 16, 1 * 16 + 4, texture_coin[coinpoints - 60]);
	}
	else if (coinpoints >= 70 && coinpoints < 80) 
	{
		painter.drawPixmap(430, 600, 2 * 16, 1 * 16 + 4, texture_coin[7]);
		painter.drawPixmap(453, 600, 2 * 16, 1 * 16 + 4, texture_coin[coinpoints - 70]);
	}
	else if (coinpoints >= 80 && coinpoints < 90) 
	{
		painter.drawPixmap(430, 600, 2 * 16, 1 * 16 + 4, texture_coin[8]);
		painter.drawPixmap(453, 600, 2 * 16, 1 * 16 + 4, texture_coin[coinpoints - 80]);
	}
	else if (coinpoints >= 90 && coinpoints < 100) 
	{
		painter.drawPixmap(430, 600, 2 * 16, 1 * 16 + 4, texture_coin[9]);
		painter.drawPixmap(453, 600, 2 * 16, 1 * 16 + 4, texture_coin[coinpoints - 90]);
	}

	if (score >= 0 && score < 1000) 
	{
		painter.drawPixmap(10 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
		painter.drawPixmap(12 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
		painter.drawPixmap(14 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
		painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);

		if (score >= 0 && score < 100) 
		{
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
			if (score < 10) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
			}
			if (score >= 10 && score < 20) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 10]);
			}
			else if (score >= 20 && score < 30) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 20]);
			}
			else if (score >= 30 && score < 40) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 30]);
			}
			else if (score >= 40 && score < 50) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 40]);
			}
			else if (score >= 50 && score < 60) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 50]);
			}
			else if (score >= 60 && score < 70) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 60]);
			}
			else if (score >= 70 && score < 80) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 70]);
			}
			else if (score >= 80 && score < 90) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 80]);
			}
			else if (score >= 90 && score < 100) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 90]);
			}
		}

		if (score >= 100 && score < 200) 
		{
			//painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
			if (score < 110) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 100]);
			}
			if (score >= 110 && score < 120) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 110]);
			}
			else if (score >= 120 && score < 130) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 120]);
			}
			else if (score >= 130 && score < 140) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 130]);
			}
			else if (score >= 140 && score < 150) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 140]);
			}
			else if (score >= 150 && score < 160) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 150]);
			}
			else if (score >= 160 && score < 170) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 160]);
			}
			else if (score >= 170 && score < 180) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 170]);
			}
			else if (score >= 180 && score < 190) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 180]);
			}
			else if (score >= 190 && score < 200) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 190]);
			}
		}

		if (score >= 200 && score < 300) 
		{
			//painter.drawPixmap(10 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
			if (score < 210) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 200]);
			}
			if (score >= 210 && score < 220) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 210]);
			}
			else if (score >= 220 && score < 230) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 220]);
			}
			else if (score >= 230 && score < 240) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 230]);
			}
			else if (score >= 240 && score < 250) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 240]);
			}
			else if (score >= 250 && score < 260) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 250]);
			}
			else if (score >= 260 && score < 270) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 260]);
			}
			else if (score >= 270 && score < 280) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 270]);
			}
			else if (score >= 280 && score < 290) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 280]);
			}
			else if (score >= 290 && score < 300) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 290]);
			}
		}

		if (score >= 300 && score < 400) 
		{
			//painter.drawPixmap(10 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
			if (score < 310) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 300]);
			}
			if (score >= 310 && score < 320) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 310]);
			}
			else if (score >= 320 && score < 330) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 320]);
			}
			else if (score >= 330 && score < 340) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 330]);
			}
			else if (score >= 340 && score < 350) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 340]);
			}
			else if (score >= 350 && score < 360) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 350]);
			}
			else if (score >= 360 && score < 370) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 360]);
			}
			else if (score >= 370 && score < 380) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 370]);
			}
			else if (score >= 380 && score < 390) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 380]);
			}
			else if (score >= 390 && score < 400) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 390]);
			}
		}

		if (score >= 400 && score < 500) 
		{
			//painter.drawPixmap(10 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
			if (score < 410) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 400]);
			}
			if (score >= 410 && score < 420) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 410]);
			}
			else if (score >= 420 && score < 430) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 420]);
			}
			else if (score >= 430 && score < 440) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 430]);
			}
			else if (score >= 440 && score < 450) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 440]);
			}
			else if (score >= 450 && score < 460) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 450]);
			}
			else if (score >= 460 && score < 470) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 460]);
			}
			else if (score >= 470 && score < 480) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 470]);
			}
			else if (score >= 480 && score < 490) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 480]);
			}
			else if (score >= 490 && score < 500) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 490]);
			}
		}

		if (score >= 500 && score < 600) 
		{
			//painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
			if (score < 510) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 500]);
			}
			if (score >= 510 && score < 520) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 510]);
			}
			else if (score >= 520 && score < 530) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 520]);
			}
			else if (score >= 530 && score < 540) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 530]);
			}
			else if (score >= 540 && score < 550) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 540]);
			}
			else if (score >= 550 && score < 560) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 550]);
			}
			else if (score >= 560 && score < 570) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 560]);
			}
			else if (score >= 570 && score < 580) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 570]);
			}
			else if (score >= 580 && score < 590) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 580]);
			}
			else if (score >= 590 && score < 600) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 590]);
			}
		}

		if (score >= 600 && score < 700) 
		{
			//painter.drawPixmap(10 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
			if (score < 610) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 600]);
			}
			if (score >= 610 && score < 620) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 610]);
			}
			else if (score >= 620 && score < 630) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 620]);
			}
			else if (score >= 630 && score < 640) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 630]);
			}
			else if (score >= 640 && score < 650) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 640]);
			}
			else if (score >= 650 && score < 660) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 650]);
			}
			else if (score >= 660 && score < 670) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 660]);
			}
			else if (score >= 670 && score < 680) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 670]);
			}
			else if (score >= 680 && score < 690) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 680]);
			}
			else if (score >= 690 && score < 700) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 690]);
			}
		}

		if (score >= 700 && score < 800) 
		{
			//painter.drawPixmap(10 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
			if (score < 710) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 700]);
			}
			if (score >= 710 && score < 720) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 710]);
			}
			else if (score >= 720 && score < 730) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 720]);
			}
			else if (score >= 730 && score < 740) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 730]);
			}
			else if (score >= 740 && score < 750) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 740]);
			}
			else if (score >= 750 && score < 760) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 750]);
			}
			else if (score >= 760 && score < 770) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 760]);
			}
			else if (score >= 770 && score < 780) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 770]);
			}
			else if (score >= 780 && score < 790) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 780]);
			}
			else if (score >= 790 && score < 800) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 790]);
			}
		}

		if (score >= 800 && score < 900) 
		{
			//painter.drawPixmap(10 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
			if (score < 810) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 800]);
			}
			if (score >= 810 && score < 820) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 810]);
			}
			else if (score >= 820 && score < 830) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 820]);
			}
			else if (score >= 830 && score < 840) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 830]);
			}
			else if (score >= 840 && score < 850) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 840]);
			}
			else if (score >= 850 && score < 860) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 850]);
			}
			else if (score >= 860 && score < 870) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 860]);
			}
			else if (score >= 870 && score < 880) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 870]);
			}
			else if (score >= 880 && score < 890) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 880]);
			}
			else if (score >= 890 && score < 900) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 890]);
			}
		}

		if (score >= 900 && score < 1000) 
		{
			//painter.drawPixmap(10 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
			if (score < 910) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 900]);
			}
			if (score >= 910 && score < 920) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 910]);
			}
			else if (score >= 920 && score < 930) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 920]);
			}
			else if (score >= 930 && score < 940) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 930]);
			}
			else if (score >= 940 && score < 950) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 940]);
			}
			else if (score >= 950 && score < 960) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 950]);
			}
			else if (score >= 960 && score < 970) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 960]);
			}
			else if (score >= 970 && score < 980) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 970]);
			}
			else if (score >= 980 && score < 990) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 980]);
			}
			else if (score >= 990 && score < 1000) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 990]);
			}
		}
	}
	else if (score >= 1000 && score < 2000) 
	{
		painter.drawPixmap(10 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
		painter.drawPixmap(12 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
		painter.drawPixmap(14 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
		if (score >= 1000 && score < 1100) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
			if (score < 1010) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1000]);
			}
			else if (score >= 1010 && score < 1020) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1010]);
			}
			else if (score >= 1020 && score < 1030) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1020]);
			}
			else if (score >= 1030 && score < 1040) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1030]);
			}
			else if (score >= 1040 && score < 1050) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1040]);
			}
			else if (score >= 1050 && score < 1060) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1050]);
			}
			else if (score >= 1060 && score < 1070) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1060]);
			}
			else if (score >= 1070 && score < 1080) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1070]);
			}
			else if (score >= 1080 && score < 1090) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1080]);
			}
			else if (score >= 1090 && score < 1100) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1090]);
			}
		}

		if (score >= 1100 && score < 1200) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
			if (score < 1110) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1100]);
			}
			if (score >= 1110 && score < 1120) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1110]);
			}
			else if (score >= 1120 && score < 1130) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1120]);
			}
			else if (score >= 1130 && score < 1140) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1130]);
			}
			else if (score >= 1140 && score < 1150) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1140]);
			}
			else if (score >= 1150 && score < 1160) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1150]);
			}
			else if (score >= 1160 && score < 1170) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1160]);
			}
			else if (score >= 1170 && score < 1180) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1170]);
			}
			else if (score >= 1180 && score < 1190) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1180]);
			}
			else if (score >= 1190 && score < 1200) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1190]);
			}
		}

		if (score >= 1200 && score < 1300) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
			if (score < 1210) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1200]);
			}
			if (score >= 1210 && score < 1220) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1210]);
			}
			else if (score >= 1220 && score < 1230) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1220]);
			}
			else if (score >= 1230 && score < 1240) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1230]);
			}
			else if (score >= 1240 && score < 1250) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1240]);
			}
			else if (score >= 1250 && score < 1260) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1250]);
			}
			else if (score >= 1260 && score < 1270) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1260]);
			}
			else if (score >= 1270 && score < 1280) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1270]);
			}
			else if (score >= 1280 && score < 1290) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1280]);
			}
			else if (score >= 1290 && score < 1300) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1290]);
			}
		}

		if (score >= 1300 && score < 1400) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
			if (score < 1310) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1300]);
			}
			if (score >= 1310 && score < 1320) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1310]);
			}
			else if (score >= 1320 && score < 1330) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1320]);
			}
			else if (score >= 1330 && score < 1340) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1330]);
			}
			else if (score >= 1340 && score < 1350) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1340]);
			}
			else if (score >= 1350 && score < 1360) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1350]);
			}
			else if (score >= 1360 && score < 1370) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1360]);
			}
			else if (score >= 1370 && score < 1380) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1370]);
			}
			else if (score >= 1380 && score < 1390) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1380]);
			}
			else if (score >= 1390 && score < 1400) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1390]);
			}
		}

		if (score >= 1400 && score < 1500) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
			if (score < 1410) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1400]);
			}
			if (score >= 1410 && score < 1420) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1410]);
			}
			else if (score >= 1420 && score < 1430) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1420]);
			}
			else if (score >= 1430 && score < 1440) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1430]);
			}
			else if (score >= 1440 && score < 1450) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1440]);
			}
			else if (score >= 1450 && score < 1460) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1450]);
			}
			else if (score >= 1460 && score < 1470) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1460]);
			}
			else if (score >= 1470 && score < 1480) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1470]);
			}
			else if (score >= 1480 && score < 1490) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1480]);
			}
			else if (score >= 1490 && score < 1500) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1490]);
			}
		}

		if (score >= 1500 && score < 1600) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
			if (score < 1510) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1500]);
			}
			if (score >= 1510 && score < 1520) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1510]);
			}
			else if (score >= 1520 && score < 1530) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1520]);
			}
			else if (score >= 1530 && score < 1540) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1530]);
			}
			else if (score >= 1540 && score < 1550) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1540]);
			}
			else if (score >= 1550 && score < 1560) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1550]);
			}
			else if (score >= 1560 && score < 1570) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1560]);
			}
			else if (score >= 1570 && score < 1580) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1570]);
			}
			else if (score >= 1580 && score < 1590) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1580]);
			}
			else if (score >= 1590 && score < 1600) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1590]);
			}
		}

		if (score >= 1600 && score < 1700) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
			if (score < 1610) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1600]);
			}
			if (score >= 1610 && score < 1620) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1610]);
			}
			else if (score >= 1620 && score < 1630) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1620]);
			}
			else if (score >= 1630 && score < 1640) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1630]);
			}
			else if (score >= 1640 && score < 1650) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1640]);
			}
			else if (score >= 1650 && score < 1660) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1650]);
			}
			else if (score >= 1660 && score < 1670) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1660]);
			}
			else if (score >= 1670 && score < 1680) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1670]);
			}
			else if (score >= 1680 && score < 1690) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1680]);
			}
			else if (score >= 1690 && score < 1700) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1690]);
			}
		}

		if (score >= 1700 && score < 1800) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
			if (score < 1710) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1700]);
			}
			if (score >= 1710 && score < 1720) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1710]);
			}
			else if (score >= 1720 && score < 1730) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1720]);
			}
			else if (score >= 1730 && score < 1740) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1730]);
			}
			else if (score >= 1740 && score < 1750) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1740]);
			}
			else if (score >= 1750 && score < 1760) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1750]);
			}
			else if (score >= 1760 && score < 1770) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1760]);
			}
			else if (score >= 1770 && score < 1780) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1770]);
			}
			else if (score >= 1780 && score < 1790) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1780]);
			}
			else if (score >= 1790 && score < 1800) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1790]);
			}
		}

		if (score >= 1800 && score < 1900) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
			if (score < 1810) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1800]);
			}
			if (score >= 1810 && score < 1820) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1810]);
			}
			else if (score >= 1820 && score < 1830) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1820]);
			}
			else if (score >= 1830 && score < 1840) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1830]);
			}
			else if (score >= 1840 && score < 1850) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1840]);
			}
			else if (score >= 1850 && score < 1860) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1850]);
			}
			else if (score >= 1860 && score < 1870) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1860]);
			}
			else if (score >= 1870 && score < 1880) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1870]);
			}
			else if (score >= 1880 && score < 1890) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1880]);
			}
			else if (score >= 1890 && score < 1900) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1890]);
			}
		}

		if (score >= 1900 && score < 2000) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
			if (score < 1910) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1900]);
			}
			if (score >= 1910 && score < 1920) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1910]);
			}
			else if (score >= 1920 && score < 1930) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1920]);
			}
			else if (score >= 1930 && score < 1940) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1930]);
			}
			else if (score >= 1940 && score < 1950) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1940]);
			}
			else if (score >= 1950 && score < 1960) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1950]);
			}
			else if (score >= 1960 && score < 1970) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1960]);
			}
			else if (score >= 1970 && score < 1980) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1970]);
			}
			else if (score >= 1980 && score < 1990) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1980]);
			}
			else if (score >= 1990 && score < 2000) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1990]);
			}
		}
	}
	else if (score >= 2000 && score < 3000) 
	{
		painter.drawPixmap(10 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
		painter.drawPixmap(12 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
		painter.drawPixmap(14 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
		if (score >= 2000 && score < 2100) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
			if (score < 2010) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2000]);
			}
			else if (score >= 2010 && score < 2020) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2010]);
			}
			else if (score >= 2020 && score < 2030) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2020]);
			}
			else if (score >= 2030 && score < 2040) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2030]);
			}
			else if (score >= 2040 && score < 2050) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2040]);
			}
			else if (score >= 2050 && score < 2060) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2050]);
			}
			else if (score >= 2060 && score < 2070) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2060]);
			}
			else if (score >= 2070 && score < 2080) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2070]);
			}
			else if (score >= 2080 && score < 2090) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2080]);
			}
			else if (score >= 2090 && score < 2100) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2090]);
			}
		}

		if (score >= 2100 && score < 2200) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
			if (score < 2110) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2100]);
			}
			if (score >= 2110 && score < 2120) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2110]);
			}
			else if (score >= 2120 && score < 2130) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2120]);
			}
			else if (score >= 2130 && score < 2140) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2130]);
			}
			else if (score >= 2140 && score < 2150) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2140]);
			}
			else if (score >= 2150 && score < 2160) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2150]);
			}
			else if (score >= 2160 && score < 2170) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2160]);
			}
			else if (score >= 2170 && score < 2180) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2170]);
			}
			else if (score >= 2180 && score < 2190) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2180]);
			}
			else if (score >= 2190 && score < 2200) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2190]);
			}
		}

		if (score >= 2200 && score < 2300) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
			if (score < 2210) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2200]);
			}
			if (score >= 2210 && score < 2220) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2210]);
			}
			else if (score >= 2220 && score < 2230) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2220]);
			}
			else if (score >= 2230 && score < 2240) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2230]);
			}
			else if (score >= 2240 && score < 2250) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2240]);
			}
			else if (score >= 2250 && score < 2260) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2250]);
			}
			else if (score >= 2260 && score < 2270) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2260]);
			}
			else if (score >= 2270 && score < 2280) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2270]);
			}
			else if (score >= 2280 && score < 2290) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2280]);
			}
			else if (score >= 2290 && score < 2300) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2290]);
			}
		}

		if (score >= 2300 && score < 2400) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
			if (score < 2310) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2300]);
			}
			if (score >= 2310 && score < 2320) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2310]);
			}
			else if (score >= 2320 && score < 2330) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2320]);
			}
			else if (score >= 2330 && score < 2340) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2330]);
			}
			else if (score >= 2340 && score < 2350) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2340]);
			}
			else if (score >= 2350 && score < 2360) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2350]);
			}
			else if (score >= 2360 && score < 2370) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2360]);
			}
			else if (score >= 2370 && score < 2380) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2370]);
			}
			else if (score >= 2380 && score < 2390) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2380]);
			}
			else if (score >= 2390 && score < 2400) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2390]);
			}
		}

		if (score >= 2400 && score < 2500) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
			if (score < 2410) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2400]);
			}
			if (score >= 2410 && score < 2420) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2410]);
			}
			else if (score >= 2420 && score < 2430) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2420]);
			}
			else if (score >= 2430 && score < 2440) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2430]);
			}
			else if (score >= 2440 && score < 2450) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2440]);
			}
			else if (score >= 2450 && score < 2460) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2450]);
			}
			else if (score >= 2460 && score < 2470) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2460]);
			}
			else if (score >= 2470 && score < 2480) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2470]);
			}
			else if (score >= 2480 && score < 2490) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2480]);
			}
			else if (score >= 2490 && score < 2500) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2490]);
			}
		}

		if (score >= 2500 && score < 2600) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
			if (score < 1510) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2500]);
			}
			if (score >= 2510 && score < 2520) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2510]);
			}
			else if (score >= 2520 && score < 2530) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2520]);
			}
			else if (score >= 2530 && score < 2540) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2530]);
			}
			else if (score >= 2540 && score < 2550) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2540]);
			}
			else if (score >= 2550 && score < 2560) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2550]);
			}
			else if (score >= 2560 && score < 2570) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2560]);
			}
			else if (score >= 2570 && score < 2580) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2570]);
			}
			else if (score >= 2580 && score < 2590) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2580]);
			}
			else if (score >= 2590 && score < 2600) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2590]);
			}
		}

		if (score >= 2600 && score < 2700) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
			if (score < 2610) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2600]);
			}
			if (score >= 2610 && score < 2620) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2610]);
			}
			else if (score >= 2620 && score < 2630) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2620]);
			}
			else if (score >= 2630 && score < 2640) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2630]);
			}
			else if (score >= 2640 && score < 2650) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2640]);
			}
			else if (score >= 2650 && score < 2660) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2650]);
			}
			else if (score >= 2660 && score < 2670) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2660]);
			}
			else if (score >= 2670 && score < 2680) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2670]);
			}
			else if (score >= 2680 && score < 2690) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2680]);
			}
			else if (score >= 2690 && score < 2700) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2690]);
			}
		}

		if (score >= 2700 && score < 2800) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
			if (score < 2710) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2700]);
			}
			if (score >= 2710 && score < 2720) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2710]);
			}
			else if (score >= 2720 && score < 2730) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2720]);
			}
			else if (score >= 2730 && score < 2740) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2730]);
			}
			else if (score >= 2740 && score < 2750) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2740]);
			}
			else if (score >= 2750 && score < 2760) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2750]);
			}
			else if (score >= 2760 && score < 2770) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2760]);
			}
			else if (score >= 2770 && score < 2780) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2770]);
			}
			else if (score >= 2780 && score < 2790) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2780]);
			}
			else if (score >= 2790 && score < 2800) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2790]);
			}
		}

		if (score >= 2800 && score < 2900) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
			if (score < 2810) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2800]);
			}
			if (score >= 2810 && score < 2820) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2810]);
			}
			else if (score >= 2820 && score < 2830) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2820]);
			}
			else if (score >= 2830 && score < 2840) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2830]);
			}
			else if (score >= 2840 && score < 2850) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2840]);
			}
			else if (score >= 2850 && score < 2860) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2850]);
			}
			else if (score >= 2860 && score < 2870) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2860]);
			}
			else if (score >= 2870 && score < 2880) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2870]);
			}
			else if (score >= 2880 && score < 2890) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2880]);
			}
			else if (score >= 2890 && score < 2900) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2890]);
			}
		}

		if (score >= 2900 && score < 3000) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
			if (score < 2910) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2900]);
			}
			if (score >= 2910 && score < 2920) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2910]);
			}
			else if (score >= 2920 && score < 2930) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2920]);
			}
			else if (score >= 2930 && score < 2940) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2930]);
			}
			else if (score >= 2940 && score < 2950) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2940]);
			}
			else if (score >= 2950 && score < 2960) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2950]);
			}
			else if (score >= 2960 && score < 2970) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2960]);
			}
			else if (score >= 2970 && score < 2980) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2970]);
			}
			else if (score >= 2980 && score < 2990) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2980]);
			}
			else if (score >= 2990 && score < 3000) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 2990]);
			}
		}
	}
	else if (score >= 3000 && score < 4000) 
	{
		painter.drawPixmap(10 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
		painter.drawPixmap(12 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
		painter.drawPixmap(14 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
		if (score >= 3000 && score < 3100) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
			if (score < 3010) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3000]);
			}
			else if (score >= 3010 && score < 3020) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3010]);
			}
			else if (score >= 3020 && score < 3030) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3020]);
			}
			else if (score >= 3030 && score < 3040) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 1030]);
			}
			else if (score >= 3040 && score < 3050) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3040]);
			}
			else if (score >= 3050 && score < 3060) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3050]);
			}
			else if (score >= 3060 && score < 3070) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3060]);
			}
			else if (score >= 3070 && score < 3080) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3070]);
			}
			else if (score >= 3080 && score < 3090) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3080]);
			}
			else if (score >= 3090 && score < 3100) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3090]);
			}
		}

		if (score >= 3100 && score < 3200) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
			if (score < 3110) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3100]);
			}
			if (score >= 3110 && score < 3120) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3110]);
			}
			else if (score >= 3120 && score < 3130) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3120]);
			}
			else if (score >= 3130 && score < 3140) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3130]);
			}
			else if (score >= 3140 && score < 3150) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3140]);
			}
			else if (score >= 3150 && score < 3160) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3150]);
			}
			else if (score >= 3160 && score < 3170) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3160]);
			}
			else if (score >= 3170 && score < 3180) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3170]);
			}
			else if (score >= 3180 && score < 3190) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3180]);
			}
			else if (score >= 3190 && score < 3200) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3190]);
			}
		}

		if (score >= 3200 && score < 3300) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
			if (score < 3210) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3200]);
			}
			if (score >= 3210 && score < 3220) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3210]);
			}
			else if (score >= 3220 && score < 3230) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3220]);
			}
			else if (score >= 3230 && score < 3240) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3230]);
			}
			else if (score >= 3240 && score < 3250) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3240]);
			}
			else if (score >= 3250 && score < 3260) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3250]);
			}
			else if (score >= 3260 && score < 3270) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3260]);
			}
			else if (score >= 3270 && score < 3280) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3270]);
			}
			else if (score >= 3280 && score < 3290) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3280]);
			}
			else if (score >= 3290 && score < 3300) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3290]);
			}
		}

		if (score >= 3300 && score < 3400) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
			if (score < 3310) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3300]);
			}
			if (score >= 3310 && score < 3320) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3310]);
			}
			else if (score >= 3320 && score < 3330) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3320]);
			}
			else if (score >= 3330 && score < 3340) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3330]);
			}
			else if (score >= 3340 && score < 3350) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3340]);
			}
			else if (score >= 3350 && score < 3360) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3350]);
			}
			else if (score >= 3360 && score < 3370) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3360]);
			}
			else if (score >= 3370 && score < 3380) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3370]);
			}
			else if (score >= 3380 && score < 3390) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3380]);
			}
			else if (score >= 3390 && score < 3400) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3390]);
			}
		}

		if (score >= 3400 && score < 3500) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
			if (score < 3410) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3400]);
			}
			if (score >= 3410 && score < 3420) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3410]);
			}
			else if (score >= 3420 && score < 3430) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3420]);
			}
			else if (score >= 3430 && score < 3440) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3430]);
			}
			else if (score >= 3440 && score < 3450) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3440]);
			}
			else if (score >= 3450 && score < 3460) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3450]);
			}
			else if (score >= 3460 && score < 3470) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3460]);
			}
			else if (score >= 3470 && score < 3480) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3470]);
			}
			else if (score >= 3480 && score < 3490) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3480]);
			}
			else if (score >= 3490 && score < 3500) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3490]);
			}
		}

		if (score >= 3500 && score < 3600) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
			if (score < 3510) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3500]);
			}
			if (score >= 3510 && score < 3520) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3510]);
			}
			else if (score >= 3520 && score < 3530) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3520]);
			}
			else if (score >= 3530 && score < 3540) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3530]);
			}
			else if (score >= 3540 && score < 3550) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3540]);
			}
			else if (score >= 3550 && score < 3560) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3550]);
			}
			else if (score >= 3560 && score < 3570) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3560]);
			}
			else if (score >= 3570 && score < 3580) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3570]);
			}
			else if (score >= 3580 && score < 3590) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3580]);
			}
			else if (score >= 3590 && score < 3600) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3590]);
			}
		}

		if (score >= 3600 && score < 3700) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
			if (score < 3610) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3600]);
			}
			if (score >= 3610 && score < 3620) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3610]);
			}
			else if (score >= 3620 && score < 3630) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3620]);
			}
			else if (score >= 3630 && score < 3640) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3630]);
			}
			else if (score >= 3640 && score < 3650) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3640]);
			}
			else if (score >= 3650 && score < 3660) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3650]);
			}
			else if (score >= 3660 && score < 3670) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3660]);
			}
			else if (score >= 3670 && score < 3680) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3670]);
			}
			else if (score >= 3680 && score < 3690) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3680]);
			}
			else if (score >= 3690 && score < 3700) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3690]);
			}
		}

		if (score >= 3700 && score < 3800) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
			if (score < 3710) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3700]);
			}
			if (score >= 3710 && score < 3720) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3710]);
			}
			else if (score >= 3720 && score < 3730) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3720]);
			}
			else if (score >= 3730 && score < 3740) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3730]);
			}
			else if (score >= 3740 && score < 3750) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3740]);
			}
			else if (score >= 3750 && score < 3760) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3750]);
			}
			else if (score >= 3760 && score < 3770) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3760]);
			}
			else if (score >= 3770 && score < 3780) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3770]);
			}
			else if (score >= 3780 && score < 3790) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3780]);
			}
			else if (score >= 3790 && score < 3800) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3790]);
			}
		}

		if (score >= 3800 && score < 3900) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
			if (score < 3810) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3800]);
			}
			if (score >= 3810 && score < 3820) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3810]);
			}
			else if (score >= 3820 && score < 3830) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3820]);
			}
			else if (score >= 3830 && score < 3840) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3830]);
			}
			else if (score >= 3840 && score < 3850) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3840]);
			}
			else if (score >= 3850 && score < 3860) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3850]);
			}
			else if (score >= 3860 && score < 3870) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3860]);
			}
			else if (score >= 3870 && score < 3880) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3870]);
			}
			else if (score >= 3880 && score < 3890) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3880]);
			}
			else if (score >= 3890 && score < 3900) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3890]);
			}
		}

		if (score >= 3900 && score < 4000) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
			if (score < 3910) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3900]);
			}
			if (score >= 3910 && score < 3920) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3910]);
			}
			else if (score >= 3920 && score < 3930) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3920]);
			}
			else if (score >= 3930 && score < 3940) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3930]);
			}
			else if (score >= 3940 && score < 3950) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3940]);
			}
			else if (score >= 3950 && score < 3960) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3950]);
			}
			else if (score >= 3960 && score < 3970) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3960]);
			}
			else if (score >= 3970 && score < 3980) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3970]);
			}
			else if (score >= 3980 && score < 3990) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3980]);
			}
			else if (score >= 3990 && score < 4000) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 3990]);
			}
		}
	}
	else if (score >= 4000 && score < 5000) 
	{
		painter.drawPixmap(10 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
		painter.drawPixmap(12 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
		painter.drawPixmap(14 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
		if (score >= 4000 && score < 4100) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
			if (score < 4010) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4000]);
			}
			else if (score >= 4010 && score < 4020) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4010]);
			}
			else if (score >= 4020 && score < 4030) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4020]);
			}
			else if (score >= 4030 && score < 4040) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4030]);
			}
			else if (score >= 4040 && score < 4050) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4040]);
			}
			else if (score >= 4050 && score < 4060) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4050]);
			}
			else if (score >= 4060 && score < 4070) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4060]);
			}
			else if (score >= 4070 && score < 4080) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4070]);
			}
			else if (score >= 4080 && score < 4090) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4080]);
			}
			else if (score >= 4090 && score < 4100) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4090]);
			}
		}

		if (score >= 4100 && score < 4200) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
			if (score < 4110) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4100]);
			}
			if (score >= 4110 && score < 4120) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4110]);
			}
			else if (score >= 4120 && score < 4130) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4120]);
			}
			else if (score >= 4130 && score < 4140) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4130]);
			}
			else if (score >= 4140 && score < 4150) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4140]);
			}
			else if (score >= 4150 && score < 4160) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4150]);
			}
			else if (score >= 4160 && score < 4170) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4160]);
			}
			else if (score >= 4170 && score < 4180) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4170]);
			}
			else if (score >= 4180 && score < 4190) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4180]);
			}
			else if (score >= 4190 && score < 4200) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4190]);
			}
		}

		if (score >= 4200 && score < 4300) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
			if (score < 4210) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4200]);
			}
			if (score >= 4210 && score < 4220) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4210]);
			}
			else if (score >= 4220 && score < 4230) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4220]);
			}
			else if (score >= 4230 && score < 4240) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4230]);
			}
			else if (score >= 4240 && score < 4250) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4240]);
			}
			else if (score >= 4250 && score < 4260) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4250]);
			}
			else if (score >= 4260 && score < 4270) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4260]);
			}
			else if (score >= 4270 && score < 4280) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4270]);
			}
			else if (score >= 4280 && score < 4290) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4280]);
			}
			else if (score >= 4290 && score < 4300) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4290]);
			}
		}

		if (score >= 4300 && score < 4400) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
			if (score < 4310) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4300]);
			}
			if (score >= 4310 && score < 4320) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4310]);
			}
			else if (score >= 4320 && score < 4330) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4320]);
			}
			else if (score >= 4330 && score < 4340) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4330]);
			}
			else if (score >= 4340 && score < 4350) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4340]);
			}
			else if (score >= 4350 && score < 4360) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4350]);
			}
			else if (score >= 4360 && score < 4370) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4360]);
			}
			else if (score >= 4370 && score < 4380) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4370]);
			}
			else if (score >= 4380 && score < 4390) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4380]);
			}
			else if (score >= 4390 && score < 4400) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4390]);
			}
		}

		if (score >= 4400 && score < 4500) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
			if (score < 4410) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4400]);
			}
			if (score >= 4410 && score < 4420) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4410]);
			}
			else if (score >= 4420 && score < 4430) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4420]);
			}
			else if (score >= 4430 && score < 4440) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4430]);
			}
			else if (score >= 4440 && score < 4450) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4440]);
			}
			else if (score >= 4450 && score < 4460) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4450]);
			}
			else if (score >= 4460 && score < 4470) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4460]);
			}
			else if (score >= 4470 && score < 4480) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4470]);
			}
			else if (score >= 4480 && score < 4490) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4480]);
			}
			else if (score >= 4490 && score < 4500) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4490]);
			}
		}

		if (score >= 4500 && score < 4600) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
			if (score < 4510) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4500]);
			}
			if (score >= 4510 && score < 4520) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4510]);
			}
			else if (score >= 4520 && score < 4530) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4520]);
			}
			else if (score >= 4530 && score < 4540) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4530]);
			}
			else if (score >= 4540 && score < 4550) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4540]);
			}
			else if (score >= 4550 && score < 4560) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4550]);
			}
			else if (score >= 4560 && score < 4570) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4560]);
			}
			else if (score >= 4570 && score < 4580) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4570]);
			}
			else if (score >= 4580 && score < 4590) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4580]);
			}
			else if (score >= 4590 && score < 4600) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4590]);
			}
		}

		if (score >= 4600 && score < 4700) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
			if (score < 4610) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4600]);
			}
			if (score >= 4610 && score < 4620) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4610]);
			}
			else if (score >= 4620 && score < 4630) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4620]);
			}
			else if (score >= 4630 && score < 4640) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4630]);
			}
			else if (score >= 4640 && score < 4650) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4640]);
			}
			else if (score >= 4650 && score < 4660) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4650]);
			}
			else if (score >= 4660 && score < 4670) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4660]);
			}
			else if (score >= 4670 && score < 4680) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4670]);
			}
			else if (score >= 4680 && score < 4690) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4680]);
			}
			else if (score >= 4690 && score < 4700) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4690]);
			}
		}

		if (score >= 4700 && score < 4800) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
			if (score < 4710) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4700]);
			}
			if (score >= 4710 && score < 4720) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4710]);
			}
			else if (score >= 4720 && score < 4730) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4720]);
			}
			else if (score >= 4730 && score < 4740) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4730]);
			}
			else if (score >= 4740 && score < 4750) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4740]);
			}
			else if (score >= 4750 && score < 4760) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4750]);
			}
			else if (score >= 4760 && score < 4770) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4760]);
			}
			else if (score >= 4770 && score < 4780) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4770]);
			}
			else if (score >= 4780 && score < 4790) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4780]);
			}
			else if (score >= 4790 && score < 4800) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4790]);
			}
		}

		if (score >= 4800 && score < 4900) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
			if (score < 4810) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4800]);
			}
			if (score >= 4810 && score < 4820) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4810]);
			}
			else if (score >= 4820 && score < 4830) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4820]);
			}
			else if (score >= 4830 && score < 4840) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4830]);
			}
			else if (score >= 4840 && score < 4850) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4840]);
			}
			else if (score >= 4850 && score < 4860) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4850]);
			}
			else if (score >= 4860 && score < 4870) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4860]);
			}
			else if (score >= 4870 && score < 4880) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4870]);
			}
			else if (score >= 4880 && score < 4890) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4880]);
			}
			else if (score >= 4890 && score < 4900) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4890]);
			}
		}

		if (score >= 4900 && score < 5000) 
		{
			painter.drawPixmap(16 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
			painter.drawPixmap(18 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
			if (score < 4910) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4900]);
			}
			if (score >= 4910 && score < 4920) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4910]);
			}
			else if (score >= 4920 && score < 4930) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4920]);
			}
			else if (score >= 4930 && score < 4940) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4930]);
			}
			else if (score >= 4940 && score < 4950) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[4]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4940]);
			}
			else if (score >= 4950 && score < 4960) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[5]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4950]);
			}
			else if (score >= 4960 && score < 4970) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[6]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4960]);
			}
			else if (score >= 4970 && score < 4980) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[7]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4970]);
			}
			else if (score >= 4980 && score < 4990) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[8]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4980]);
			}
			else if (score >= 4990 && score < 5000) 
			{
				painter.drawPixmap(20 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[9]);
				painter.drawPixmap(22 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[score - 4990]);
			}
		}
	}

	if (time >= 0 && time < 66) 
	{
		painter.drawPixmap(25 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[3]);
		painter.drawPixmap(27 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_time[9]);
		painter.drawPixmap(29 * 16, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_time[9]);
	}
	else if (time >= 66 && time < 6600) 
	{
		painter.drawPixmap(25 * 16 + 4, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[2]);
		painter.drawPixmap(27 * 16 - 2, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_time[(time / 660) % 10]);
		painter.drawPixmap(29 * 16 - 6, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_time[(time / 66) % 10]);
	}
	else if (time >= 6600 && time < 2 * 6600) 
	{
		painter.drawPixmap(25 * 16 + 4, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[1]);
		painter.drawPixmap(27 * 16 - 2, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_time[(time / 660) % 10]);
		painter.drawPixmap(29 * 16 - 6, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_time[(time / 66) % 10]);
	}
	else if (time >= 2 * 6600 && time < 3 * 6600) 
	{
		painter.drawPixmap(25 * 16 + 4, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
		painter.drawPixmap(27 * 16 - 2, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_time[(time / 660) % 10]);
		painter.drawPixmap(29 * 16 - 6, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_time[(time / 66) % 10]);
	}

	if (time >= 3 * 6600) 
	{
		painter.drawPixmap(25 * 16 + 4, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
		painter.drawPixmap(27 * 16 - 2, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);
		painter.drawPixmap(29 * 16 - 6, 39 * 16 + 6, 2 * 16, 1 * 16 + 4, texture_coin[0]);

	}

	if (life == 1)
		painter.drawPixmap(7 * 16 - 4, 39 * 16 + 8, 2 * 16 + 6, 1 * 16, texture_coin[1]);
	else if (life == 0)
		painter.drawPixmap(7 * 16 - 4, 39 * 16 + 8, 2 * 16 + 6, 1 * 16, texture_coin[0]);
	else if (life == 2)
		painter.drawPixmap(7 * 16 - 4, 39 * 16 + 8, 2 * 16 + 6, 1 * 16, texture_coin[2]);

    }
}

void Hud::advance() 
{
	score = Game::instance()->getScore();
	coinpoints = Game::instance()->getCoinPoints();
	time = Game::instance()->getTime();
	life = Game::instance()->getLife();
	this->update();
}