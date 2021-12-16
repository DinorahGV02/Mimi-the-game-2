#pragma once
#include "Tile.h";
using namespace sf;
using namespace std;

class TileMap
{
private:
	vector<vector<Tile*> >tiles;

public:
	TileMap();
	~TileMap();

	//functions

	void addTile(unsigned x, unsigned y);
	void removeTile(unsigned x, unsigned y);

	void update();
	void render();
};

