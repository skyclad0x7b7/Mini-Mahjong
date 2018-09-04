#include "Game.h"
#include "Test.h"

int main()
{
	//mahjong::Test::testYaku();
	mahjong::Game game(new mahjong::Player("Alpha"), new mahjong::Player("Beta"), new mahjong::Player("Charlie"), new mahjong::Player("Delta"));
	game.startGame();
	system("pause");
	return 0;
}