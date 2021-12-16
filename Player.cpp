#include "stdafx.h"
#include "Player.h"
using namespace std;
using namespace sf;

void Player::initVariable()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	this->hpMax = 10;
	this->hp = hpMax;
	


}

void Player::initTexture()
{
	//fix error, dont load sprites
	//SOLVED

	if(!this->textureSheet.loadFromFile("GameTexture/cat_sprite.png"));
	{
		cout << "Error meow.. Could not load player sheet.. meow" << "\n";
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	//play with these numbers unil you get the right size
	this->currentFrame = IntRect(0, 0, 110, 100);

	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(2.f, 2.f);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	//play with these VALUES ATTENTION!! 
	//play with these values 
	this->velocityMax = 5.f;
	this->velocityMin = 1.f;
	this->acceleration = 3.3f;
	//REDUCE CAREFULLY TO NOT DISABLE A KEY MOV
	//45 IS PERFECT 
	this->drag = 0.45f;
	//gravity is what is making the cat dissapear from the screen! play with this!!
	this->gravity = 1.f;
	this->velocityMaxY = 15.f;
}

Player::Player()
{
	//this->sprite.setPosition(x, y);
	this->initVariable();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();

}

Player::~Player()
{
}


void Player::updatePhysics()
{
	//gravity
	this->velocity.x += 1.0 * this->gravity;
	if (abs(this->velocity.x) > this->velocityMaxY)
	{
		this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}

	//this->velocity.y += dir_y * this->acceleration; GRAVITY
	//deceleration
	this->velocity*= this->drag;

	//limit deceleration
	if (abs(this->velocity.x) < this->velocityMin)
	{
		this->velocity.x = 0.f;
	}
	if (abs(this->velocity.y) < this->velocityMin)
	{
		this->velocity.y = 0.f;
	}

	this->sprite.move(this->velocity);
}

void Player::move(const float dir_x, const float dir_y)
{

	//acceleration 
	this->velocity.x += dir_x * this->acceleration;
	
	//limit velocity
	if (abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
		//((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
}

void Player::updateMovement()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	if (Keyboard::isKeyPressed(Keyboard::Key::A)) //LEFT
	{
		this->move(-1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::D)) //RIGHT
	{
		this->move(1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
		
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::W)) //top
	{
		this->sprite.move(0.f, -1.f);
		this->animState = PLAYER_ANIMATION_STATES::JUMPING;
	}

	else if (Keyboard::isKeyPressed(Keyboard::Key::S)) //down
	{
		this->sprite.move(0.f, 1.f);
		this->animState = PLAYER_ANIMATION_STATES::FALLING;
	}
}

void Player::updateAnimations()
{
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.4f || this->getAnimSwitch())
		{
			
				//play with the numbers until idle animation looks good
			this->currentFrame.top = 320.f;
			this->currentFrame.left += 340.f;
			if (this->currentFrame.left >= 400.f)
			{
				this->currentFrame.left = 0;
			}
			
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.3f || this->getAnimSwitch())
		{

			//play with the numbers until idle animation looks good
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 110.f;
			if (this->currentFrame.left >= 400.f)
			{
				this->currentFrame.left = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
			
		}
		this->sprite.setScale(-2.f, 2.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.f, 0.f);
		
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.3f || this->getAnimSwitch())
		{

			//play with the numbers until idle animation looks good
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 110.f;
			if (this->currentFrame.left >= 400.f)
			{
				this->currentFrame.left = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
			
		}
		this->sprite.setScale(2.f, 2.f);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::JUMPING)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{

			//play with the numbers until idle animation looks good
			this->currentFrame.top = 320.f;
			this->currentFrame.left += 230.f;
			if (this->currentFrame.left >= 500.f)
			{
				this->currentFrame.left = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::FALLING)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.3f || this->getAnimSwitch())
		{

			//play with the numbers until idle animation looks good
			this->currentFrame.top = 451.f;
			this->currentFrame.left += 324.f;
			if (this->currentFrame.left >= 550.f)
			{
				this->currentFrame.left = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);

		}
		this->sprite.setScale(2.f, 2.f); //-2.f,2.f
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.f, 0.f);

	}

	else
	{
		this->animationTimer.restart();
	}
	
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimations();
	this->updatePhysics();
	//this->updateCollision(target);
}

void Player::takeDamage(const int damage)
{
	if (this->hp > 0)
	{
		this->hp -= damage;
	}
	if (this->hp < 0)
	{
		this->hp = 0;
	}
}

void Player::gainHealth(const int health)
{
	if (this->hp < this->hpMax)
	{
		this->hp += health;
	}
	if (this->hp > this->hpMax)
	{
		this->hp = this->hpMax;
	}
}

const Sprite& Player::getShape() const
{
	return this->sprite;
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::gethpMax() const
{
	return this->hpMax;
}
/*void Player::updateCollision(RenderTarget& target)
{
	//const RenderTarget* target;
	FloatRect playerBounds = this->sprite.getGlobalBounds();
	//Vector2f playerSize = this->sprite.getSize();
	//left
	if (playerBounds.left <= 0.f)
	{
		this->sprite.setPosition(0.f, playerBounds.top);
		
	}
	//right
	else if (playerBounds.left + playerBounds.width >= target.getSize().x)
	{
		this->sprite.setPosition(target.getSize().x - playerBounds.width, playerBounds.top);
	}
	//top
	if (playerBounds.top <= 0.f)
	{
		this->sprite.setPosition(playerBounds.left , 0.f);

	}
	//bottom
	else if (playerBounds.top + playerBounds.height >= target.getSize().y)
	{
		this->sprite.setPosition(playerBounds.left,target.getSize().y - playerBounds.width);
	}
}*/


const FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

const Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}


void Player::render(RenderTarget& target)
{
	target.draw(this->sprite);
	/*CircleShape circ;
	circ.setFillColor(Color::Magenta);
	circ.setRadius(2.f);
	circ.setPosition(this->sprite.getPosition());

	target->draw(circ);*/
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}


void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}
const bool& Player::getAnimSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;
	
	return anim_switch;
}