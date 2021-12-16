#pragma once
using namespace std;
using namespace sf;

enum GameBallType{DEFAULT = 0, DAMAGING, HEALING, NROFTYPES};

class GameBalls
{
private:
	CircleShape shape;
	void initShape(const RenderWindow& window);
	int type;

public:
	//accesor
	const CircleShape getShape() const;
	const int& getType() const;

	//functions
	GameBalls(const RenderWindow& window, int type);
	
	virtual ~GameBalls();
	void update();
	void render(RenderTarget& target);

};

