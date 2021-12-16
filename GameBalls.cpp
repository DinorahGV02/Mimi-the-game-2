#include "stdafx.h"
#include "GameBalls.h"
using namespace sf;
using namespace std;

void GameBalls::initShape(const RenderWindow& window)
{
	this->shape.setRadius(static_cast<float>(rand() % 10 + 10));
	Color color;
	switch (this->type)
	{
	case DEFAULT:
		color = Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
		break;
	case DAMAGING:
		color = Color::Red;
		this->shape.setOutlineColor(Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
	case HEALING:
		color = Color::Green;
		this->shape.setOutlineColor(Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
	}
	
	this->shape.setFillColor(color);
	this->shape.setPosition(Vector2f(static_cast<float>(rand()% window.getSize().x - shape.getGlobalBounds().width),
		static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height)));
		
}

GameBalls::GameBalls(const RenderWindow& window, int type)
	:type(type)
{
	this->initShape(window);
	
}

const CircleShape GameBalls::getShape() const
{
	return this->shape;
}

const int& GameBalls::getType() const
{
	return this->type;
}

GameBalls::~GameBalls()
{
}

void GameBalls::update()
{
}

void GameBalls::render(RenderTarget& target)
{
	target.draw(this->shape);
}
