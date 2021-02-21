#pragma once
#include "Enemy.h"

class KoopaTroopa : public Enemy
{
protected:

	// attributes
	bool green;                             // brown/green KoopaTroopa
	bool reanimate;                         // is reanimed (= KoopaTroopa is only hurt by Mario, but it is still alive)
	bool reanimate_fast;                    // is in the final stage of reanimation
	bool kicked;                            // is kicked by Mario
	bool grabbed;                           // is grabbed by Mario
	bool walk_on_brick;

	// counters
	int reanimate_counter;                  // counts the number of frames since reanimate started
	int count_moving;

	// durations
	int reanimate_duration;                 // duration of reanimate

	// textures
	QPixmap texture_walk_right[2][2];		// brown/green walk animation
	QPixmap texture_walk_left[2][2];		// brown/green walk animation
	QPixmap texture_smashed[2][2];		    // brown/green smashed texture
	QPixmap texture_kicked[2][4];           // texture kicked

public:

	KoopaTroopa(QPoint position, Direction direction = LEFT, bool isGreen = false,
		bool _walk_on_brick = false);

	// pure virtual methods that must be implemented
	virtual std::string name() { return "KoopaTroopa"; }
	virtual void animate();
	virtual void hit(Object *what, Direction fromDir);
	virtual void hurt();
	virtual void smash();
	virtual void advance();
	
	// KoopaTroopa methods
	void startReanimed();                

	// getters
	bool isReanimed() { return reanimate; }
	bool isReanimed_Fast() { return reanimate_fast; }
	bool isKicked() { return kicked; }
	bool isGrabbed() { return grabbed; }
	bool isWalkOnBrick() { return walk_on_brick; }

	// setters
	void setKicked(bool _kicked) { kicked = _kicked; }
	void setGrabbed(bool _grabbed) { grabbed = _grabbed; }

	QPainterPath shape() const;
};