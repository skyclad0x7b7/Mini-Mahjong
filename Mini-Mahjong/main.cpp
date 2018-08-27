#include "Game.h"
#include "Test.h"

int main()
{
	//mahjong::Test::testYaku();
	mahjong::Game game(new mahjong::Player("PlayerOneName"));
	game.startGame();
	system("pause");
	return 0;
}