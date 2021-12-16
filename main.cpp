#include "stdafx.h"
#include "Game.h"
#include <SFML/Audio.hpp>
using namespace std;


int main()
{
	srand(static_cast<unsigned>(time(0)));

	Game game;
	Music music;
	music.openFromFile("resources/bubblegum_kk.ogg");
	music.play();
	music.setLoop(true);
	while (game.running())
	{
		game.update();
		game.render();	
	}
	
	cout << "Dinorah Garcia Vasquez" << endl
		<< "Prof.Azhar" << endl
		<< "FALL 2021 HONORS PROJECT" << endl;

	//END OF APPLICATION 

	return 0;
}
