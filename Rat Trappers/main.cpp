#include "game.h"

using namespace rat_trappers;

int main(int argc, char* args[])
{
	Game game(672, 768);
	return game.run();
}