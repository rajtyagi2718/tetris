#include "../include/game.h"
#include "../include/agent.h"
#include "../include/board.h"
#include "../include/piece.h"
#include <memory>              // make_unique

namespace game
{
using board::Board;
using piece::Piece;

template<typename Agent_>
Game<Agent_>::Game(Agent_ agent_, Board board_)
  : agent_{agent_}, board_{board_}
//, curpiece{piece::spawn()}
{
}
}  // namespace game
