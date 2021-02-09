#include "../include/game.h"
#include "../include/agent.h"
#include "../include/board.h"
#include "../include/piece.h"
#include "../include/spawn.h"

Game::Game()
  : agent{Agent()}, board{Board()}, curpiece{spawn::piece()}
{
}

