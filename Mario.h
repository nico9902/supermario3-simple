#pragma once

#include "Entity.h"

class Mario : public Entity
{
	protected:

		// textures
		QPixmap texture_stand[2];			// small/big stand texture
		QPixmap texture_walking[2][4];		// small/big walking animations
		QPixmap texture_jumping[2];			// small/big jumping texture
		QPixmap texture_falling[2];			// small/big falling texture
		QPixmap texture_brake[2];			// small/big brake texture
		QPixmap texture_crouch;				// big crouch texture
		QPixmap texture_small2big[12];		// transformation small-to-big
		QPixmap texture_big2small[12];		// transformation big-to-small
		QPixmap texture_dead;               // dead texture
		QPixmap texture_kick[2][1];         // small/big kick texture
		QPixmap texture_grab[2][2];         // small/big grab texture
		QPixmap texture_stand_racoon;       // stand racoon texture
		QPixmap texture_walking_racoon[4];  // racoon walk animations
		QPixmap texture_jumping_racoon;     // racoon jump animation
		QPixmap texture_falling_racoon;     // racoon fall animation
		QPixmap texture_brake_racoon;       // racoon brake animation
		QPixmap texture_crouch_racoon;      // racoon crouch animation
		QPixmap texture_kick_racoon;        // racoon kick animation
		QPixmap texture_grab_racoon[2];     // racoon grab animations
		QPixmap texture_big2racoon[3];      // big2racoon animations
		QPixmap texture_round_racoon[4];    // racoon round animations
		QPixmap texture_pre_fly_racoon[3];  // racoon pre_fly animations
		QPixmap texture_fly_racoon[3];      // racoon fly animations
		QPixmap texture_come_down[3];       // come down animations 

		// animation divisors
		int animation_div;

		// flags
		bool running;						// is Mario running?
		bool big;							// is Mario big?
		bool racoon;					    // is Mario Racoon?
		bool crouch;						// is Mario crouched?
		bool kick;                          // is Mario kicking?
		bool grab;                          // is Mario grabbing?
		bool pre_grab;                      // is bottom 'V' push?
		bool transparent;                   // is transparent?
		bool round;                         // if Mario Racoon use tail
		bool pre_fly;                       // is Mario pre_fly?
		bool fly;                           // is Mario flying?
		bool pre_come_down;                 // is Mario coming down?
		bool come_down;                     // wheter Mario go in Underground World
		bool go_up;                         // wheter Mario return to starting World
		bool return2scene;

		// counters
		int moving_start_counter;			// counts the number of frames since moving started
		int moving_stop_counter;			// counts the number of frames since moving stopped
		int dir_change_counter;				// counts the number of frames since direction changed
		int transformation_counter;			// counts the number of frames since transformation started
		int dying_counter;                  // counts the number of frames since Mario is dying and before Mario jump
		int kick_counter;                   // counts the number of frames since Mario kick an object
		int transparent_counter;            // counts the number of frames since Mario is transparent
		int big2racoon_counter;             // counts the number of frames since Mario goes from Big to Racoon
		int racoon2big_counter;             // counts the number of frames since Mario goes from Racoon to Big
		int round_counter;                  // counts the number of frames since Mario Racoon begin to round
		int comedown_counter;               // counts the number of frames since Mario begin to come down in Underground World
		int goup_counter;                   // counts the number of frames since Mario begin to go up in starting Wolrd

		// durations
		int kick_duration;                  // kick duration
		int transparent_duration;           // transparent duration
		int big2racoon_duration;            // big2racoon duration
		int racoon2big_duration;            // racoon2big duration
		int round_duration;                 // round duration of Mario Racoon
		int comedown_duration;              // duration that takes Mario to go down in Underground World

	public:

		Mario(QPoint position, bool _goup=false);

		// getters and setters
		bool isBig(){return big;}
		bool iskick() { return kick; }
		bool isGrab() { return grab; }
		bool isRacoon() { return racoon; }
		bool isPregrab() { return pre_grab; }
		bool isTransparent() { return transparent; }
		bool isJumping() { return jumping; }
		bool isPreFly() { return pre_fly; }
		bool isFly() { return fly; }
		bool isRound() { return round; }
		bool isPreComeDown() { return pre_come_down; }
		bool isComeDown() { return come_down; }
		bool isGoUp() { return go_up; }
		Direction getDir() { return dir; }
		void setRunning(bool _running);
		void setKick(bool _kick) { kick = _kick; }
		void setGrab(bool _grab) { grab = _grab; }
		void setPregrab(bool _Pregrab) { pre_grab = _Pregrab; }
		void setRacoon(bool _racoon) { racoon = _racoon; }
		void setTransparent(bool _transparent) { transparent = _transparent; }
		void setRacoon2Big(int _counter) { racoon2big_counter = _counter; }
		void setRound(bool _round) { round = _round; }
		void setFly(bool _fly) { fly = _fly; }
		void setPreFly(bool _prefly) { pre_fly = _prefly; }
		void setJump(bool _jump) { jumping = _jump; }
		void setPreComeDown(bool _pre_come_down) { pre_come_down = _pre_come_down; }
		void setComeDown(bool _come_down) { come_down = _come_down; }
		void setGoUp(bool _go_up) { go_up = _go_up; }
		void setReturn2Scene(bool _scene) { return2scene = _scene; }

        // pure virtual methods that must be implemented
        virtual std::string name(){ return "Mario";}
        virtual void animate();
        virtual void hit(Object *what, Direction fromDir);

		// @override advance() for to add vertical/horizontal acceleration
		virtual void advance();

		// @override setMoving() to add horizontal acceleration
		virtual void setMoving(bool _moving);

		// @override setDirection() to avoid instant direction change
		virtual void setDirection(Direction _dir);

		// @override die method (Mario is a special case)
		virtual void die();

		// jump
		void jump();

		// bounce
		void bounce();

		// crouch
		void setCrouch(bool active);

		// dying
		void setDying(bool _dying) { dying = _dying; }

		// big
		void setBig(bool _big) { big = _big; }

		// Mario became big
		void powerUp();

		// Mario became MarioRacoon
		void marioRacoon();

		// Mario collider
		QPainterPath shape() const;

		// @override
		virtual void endJumping();
		
		void startFalling();
};
