#pragma once
using namespace sf;

enum PLAYER_ANIMATION_STATES { IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING };
class Player
{
private:
	Sprite sprite;
	Texture textureSheet;
	Clock animationTimer;
	int hp;
	int hpMax;
	


	//animation
	short animState;
	IntRect currentFrame;
	bool animationSwitch;

	// movement 

	//physics
	Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	float velocityMaxY;

	//core
	
	void initVariable();
	void initTexture(); // same as init shape
	void initSprite();
	void initAnimations();
	void initPhysics();


public:
	Player();
	virtual ~Player();

	//accesors

	const bool& getAnimSwitch();
	const Vector2f getPosition() const;
	const FloatRect getGlobalBounds() const;
	const Sprite& getShape() const;
	const int& getHp() const;
	const int& gethpMax() const;


	//modifiers
	void setPosition(const float x, const float y);
	void resetVelocityY();


	//functions 
	void takeDamage(const int damage);
	void gainHealth(const int health);
	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);
	void updatePhysics();
	void updateMovement();
	void updateAnimations();
	void update();
	//void updateCollision(RenderTarget& target);
	void render(RenderTarget& target);
	
};

