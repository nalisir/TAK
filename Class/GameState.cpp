#include <vector>
#include <PathBoard.cpp>

class GameState
{

private:

  SquareStack *Squares;

  PathBoard WhitePath;

  PathBoard BlackPath;

  int BoardLength;

public:

  GameState(int Blength) : WhitePath(Blength*Blength), BlackPath(Blength*Blength)
  {
    Squares = new SquareStack [Blength*Blength];
    BoardLength = Blength;
  }


};
