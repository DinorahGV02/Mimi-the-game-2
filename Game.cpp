#include "stdafx.h"
#include "Game.h"
using namespace std;

void Game::initWindow()
{
	//this->videMode = VideoMode(800, 600);
	//this->window = new RenderWindow(this->videMode, "Mimi The Game!", Style::Close | Style::Titlebar);
	this->window.create(VideoMode(800, 600), "Mimi The Game!", Style::Close | Style:: Titlebar);
	this->window.setFramerateLimit(144);
}

void Game::initPlayer()
{
	//solve
	this->player = new Player(); //maybe deleting the new word
}

void Game::initVariables()
{
	this->endGame = false;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxGameBalls = 10;
	this->points = 0;
}

void Game::initFont()
{
	if(!this->font.loadFromFile("resources/victor_pixel.ttf"));
	{
		cout << "Sowwy could not load font, meowwww" << endl;
	}
}

void Game::initText()
{
	this->text.setFont(this->font);
	this->text.setFillColor(Color::Magenta);
	this->text.setCharacterSize(24);
	//this->text.setString("Welcome to Mimi The Game!! enjoy!! purr");

	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(Color::Red);
	this->endGameText.setCharacterSize(28);
	this->endGameText.setPosition(Vector2f(20, 300));
	this->endGameText.setString("NO!!! YOU KILLED THE CUTE LITTLE CAT, MONSTER!!");
}


Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initPlayer();
	this->initFont();
	this->initText();
	
	
}

Game::~Game()
{
	//delete this-player;
	delete this->player;
}

const bool Game::running() const
{
	return this->window.isOpen(); //&& this->endGame == false;
}

void Game::pollEvents()
{
	while (this->window.pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case Event::Closed:
			this->window.close();
			break;
		case Event::KeyPressed:
			if (this->ev.key.code == Keyboard::Escape)
				this->window.close();
			break;
		}
	}
}

void Game::updatePlayer()
{
	this->player->update();
	if (this->player->getHp() == 0)
	{
		this->endGame == true;
	}
}

void Game::updateCollision()
{
	//collision bottom of the screen
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window.getSize().y)
	{
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getPosition().x, this->window.getSize().y - this->player->getGlobalBounds().height);
	}

	//left collision
	
}

void Game::spawnGameBalls()
{
	//timer
	if (this->spawnTimer < this->spawnTimerMax)
	{
		this->spawnTimer += 1.f;
	}
	else 
	{
		if (this->gameBalls.size() < this->maxGameBalls)
		{
			this->gameBalls.push_back(GameBalls(this->window,this->randBallType()));
			this->spawnTimer = 0.f;
		}
		
	}
}

void Game::updateBallCollision()
{
	//check the collision
	for (size_t i = 0; i < this->gameBalls.size(); i++)
	{
		if (this->player->getShape().getGlobalBounds().intersects(this->gameBalls[i].getShape().getGlobalBounds()))
		{
			switch (this->gameBalls[i].getType())
			{
			case GameBallType::DEFAULT:
				this->points++;
				break;
			case GameBallType::DAMAGING:
				this->player->takeDamage(1);
				//REMEMBER TO SET BACK TO 1
				if (this->points >= 1)
				{
					this->points--;
				}
				break;
			case GameBallType::HEALING:
				this->player->gainHealth(1);
				break;
			}
			//add points
			
			//remove the balls
			this->gameBalls.erase(this->gameBalls.begin() + i);
			
		}
	}
	
}

void Game::update()//RenderTarget& target
{
	//polling window events 
	/*while (this->window.pollEvent(this->ev))
	{
		if (this->ev.type == Event::Closed)
		{
			this->window.close();
		}
		else if(this->ev.type == Event::KeyPressed && this->ev.key.code == Keyboard::Escape)
		{
			this->window.close();
		}
		if (this->ev.type == Event::KeyReleased &&
			(this->ev.key.code == Keyboard::A || 
				this->ev.key.code == Keyboard::D ||
				this->ev.key.code == Keyboard::W ||
				this->ev.key.code == Keyboard::S))
		{
			this->player->resetAnimationTimer();
		}
	} uncomment in case */
	this->pollEvents();

	if (this->endGame == false)
	{
		this->updatePlayer();
		this->spawnGameBalls();
		this->updateBallCollision();
		this->updateText();
	}
	

	//this->updateCollision();

}

void Game::renderPlayer()
{
	this->player->render(this->window); //change -> or . when having issues
}

void Game::render()
{
	this->window.clear(Color(255, 192, 203));//-> doing this solve the red this 
	//

	//render game
	this->renderPlayer();
	for (auto i : this->gameBalls)
	{
		i.render(this->window); //maybe add * before this
	}

	//draw or render game in between

	//render text
	this->renderText(this->window);

	//render end text
	//if (this->endGame == true)
	if(this->player->getHp() == 0)
	{
		this->window.draw(this->endGameText);
		this->endGame == true;
	}

	this->window.display();

}

void Game::renderText(RenderTarget& target)
{
	target.draw(this->text);
}

void Game::updateText()
{
	stringstream ss;
	ss << "Puurr Points: " << this->points << endl
		<< "Meow Health: " << this->player->getHp() << " / "<< this->player->gethpMax()<<endl;

	this->text.setString(ss.str());
}

const int Game::randBallType() const
{
	int type = GameBallType::DEFAULT;
	int randValue = rand() % 100 +1;

	if (randValue > 60 && randValue <= 80)
	{
		type = GameBallType::DAMAGING;
	}
	else if (randValue > 80 && randValue <= 100)
	{
		type = GameBallType::HEALING;
	}
	return type;
}

const bool& Game::getEndGame() const
{
	return this->endGame;
}


const RenderWindow& Game::getWindow() const
{
	// TODO: insert return statement here
	return this->window;
}
