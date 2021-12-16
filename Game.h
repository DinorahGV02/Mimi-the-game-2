#pragma once
//#include"stdafx.h"
#include <iostream>
#include <ctime>
#include "Player.h"
#include "GameBalls.h"
#include <vector>
#include <sstream>

using namespace sf;
using namespace std;

class Game
{
private:
	//VideoMode videMode;
	RenderWindow window; //maybe add a * at the end of window
	Event ev;
	Player* player;
	vector<GameBalls> gameBalls;
	float spawnTimerMax;
	float spawnTimer;
	int maxGameBalls;
	bool endGame;
	int points;
	Font font;
	Text text;
	Text endGameText;


	void initWindow();
	void initPlayer();
	void initVariables();
	void initFont();
	void initText();


public:
	
	Game();
	virtual ~Game();

	//Functions
	const bool running() const;
	void pollEvents();
	void updatePlayer();
	void updateCollision();
	void spawnGameBalls();
	void updateBallCollision();
	void update();
	void renderPlayer();
	void render();
	void renderText(RenderTarget& target);
	void updateText();
	const int randBallType() const;
	const bool& getEndGame() const;
	
	

	const RenderWindow& getWindow() const;
};

