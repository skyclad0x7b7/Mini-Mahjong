#include "Game.h"

int main()
{
	mahjong::Game game(new mahjong::Player("PlayerOneName"));
	game.startGame();
	system("pause");
	return 0;
}