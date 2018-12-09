#pragma once
#ifndef Megaman_H_
#define Megaman_H_
#include"ActionObject.h"
#include<d3dx9.h>
#include"Bullet.h"
#include<list>


#define MEGAMAN_HEIGHT 84
#define MEGAMAN_WIDTH 75
#define MEGAMAN_GRAVITY -0.0015f
#define MEGAMAN_WALK_SPEED 0.2f

#define MEGAMAN_STAND_JUMP_SPEED 0.45f
#define MEGAMAN_JUMP_BONUS_SPEED 0.4f
#define MEGAMAN_RUN_JUMP_SPEED 0.55f
#define MEGAMAN_JUMP_WALL_SPEED 0.4f

#define MEGAMAN_DASH_SPEED 0.4f
#define MEGAMAN_DISTANCE_DASH 250
#define MEGAMAN_DISTANCE_ALLOW_BOUNS 50
#define MEGAMAN_TIME_NEED_TO_CHARING 400

class Megaman:public ActionObject
{
private:
	int yPre;
	int yStartJump; //y -start jump -using for render and state jump
	int xStartDash;

	bool isAllowDash;
	bool isGround;
	bool isAllowClimbWall;
	bool isAllowJump; //if keydown -false- keyup -true. reset because jump more
	bool charging;
	bool hurting;
	bool bounsed;

	float time_start_press_A;
	static Megaman* instance;

	
	Animation * animation_charging;
	Animation * animation_lifebar;
public:
	Megaman();
	~Megaman();

	static Megaman* Instance();

	void Update(DWORD dt, vector<Object*> *List__virtual_object_can_col);
	void ProcessCollisionBullet(list<Bullet*> List__bullet_enemy);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);
	bool SetTimeStartPressA();
	void SetAllowDash(bool allow) { this->isAllowDash = allow; }
	void SetAllowJump(bool allow) { this->isAllowJump = allow;	}
	void SetStartJump() { this->yStartJump = this->y; this->bounsed = false; }
	void SetBonus(float vy) { this->vy = vy; this->bounsed = true; }

	void ResetTimeStartPressA();

	State GetState();
	//State GetShootOldState() { return shoot_state_old; }
	State GetNewState(State currentState, EControler controler);
	Direction GetDirection();
	float GetTimePressA();
	int GetDistanceDash() { return abs(this->x - xStartDash); }
	int GetDistanceJump() { return abs(this->y - yStartJump); }


	bool IsCanJump() { return ((isGround||isAllowClimbWall)&&this->isAllowJump); }
	bool IsGround() { return this->isGround; }
	bool IsFinishUpGun();
	bool IsFinshAction();
	bool IsCharging() { return this->charging; }
	bool IsCanDash() { return (this->isAllowDash&&this->isGround); }
	bool IsBounused() { return this->bounsed; }
	bool IsFreeFall() { return (this->y+5 < yPre); }

	void SetGround(bool ground) { this->isGround = ground; }
	void ResetAnimation() { this->animation->listSprite[state]->Reset(); }
};

#endif // !Megaman_H_
