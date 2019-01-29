#include <vector>
#include <PathBoard.cpp>

class GameState
{

private:

  SquareStack *Squares;
  std::vector<short int> *Neighbours;

  PathBoard WhitePath;
  PathBoard BlackPath;

  int BoardLength;

public:

  GameState(int Blength) : WhitePath(Blength), BlackPath(Blength)
  {
    Squares = new SquareStack [Blength*Blength];
    BoardLength = Blength;
    this->Neighbours = new std::vector<short int> [Blength*Blength];
    
    for(int i=0; i<Blength; i++)
      for(int j=0; j<Blength; j++)
      {
        tempnode = i*Blength + j;
        this->Neighbours[tempnode].push_back( (i+1 != Blength) ? (tempnode + Blength) : -1); // Right
        this->Neighbours[tempnode].push_back( (j+1 != Blength) ? (tempnode + 1) : -1); // Down
        this->Neighbours[tempnode].push_back( (i != 0) ? (tempnode - Blength) : -1); // Left
        this->Neighbours[tempnode].push_back( (j != 0) ? (tempnode - 1) : -1); // Up
      }
  }
 

  ~GameState()
  {
  }


  bool NewPiece(short int Node, short int type, bool color)
  {
    if(Squares[Node].WhatTop() == 0)
    {
      Squares[Node].add(color);
      Squares[Node].ChangeTop(type);
      return true;
    }
    else
    {
      std::cerr << "Error: the selected square is not empty" << endl;
      return false;
    }
  }


  bool Move(short int Node, short int bunch, short int dir, std::vector<bool> *trail)
  {
    if(checkmove(Node, dir, trail.size()))
    {
      short int top = Squares[Node].WhatTop();
      std::stack<bool> tempstack;

      if(!(Squares[Node].take(bunch, &tempstack)))
        return false;
      
      for(int i=0, i<(*trail).size(); i++)
      {
        Node = Neighbours[Node][dir];
        for(int j=0; j<(*trail)[i]; j++)
        {
          Squares[Node].add(stack.top());
          stack.pop();
        }
        Squares[Node].ChangeTop(1);
        WhitePath.Modify(!(Squares[Node].top()) && Squares[Node].path());
        BlackPath.Modify(Squares[Node].top() && Squares[Node].path());
      }
      Squares[Node].ChangeTop(top);
      WhitePath.Modify(!(Squares[Node].top()) && Squares[Node].path());
      BlackPath.Modify(Squares[Node].top() && Squares[Node].path());
      return true;
    }
    else
    {
      std::cerr << "Error: move is not allowed" << endl;
      return false;
    }
  }


  bool CheckMove(short int pos, short int direct, int steps)
  {
    bool capstone = Squares[pos].path() && Squares[pos].step();
    for(short int i=0; i<steps-1; i++)
    {
      pos = Neighbours[pos][direct];
      if(pos < 0) return 0;
      if(!(Squares[pos].step())) return 0;
    }
    pos = Neighbours[pos][direct];
    if(pos < 0) return 0;
    if(!(Squares[pos].step()) && !(capstone)) return 0;

    return true;
  }
    

  bool IsOver()
  {
    bool result = false;
    if(WhitePath.HasWon(&Neigbours))
    {
      std::cout << "White has completed a road!";
      result = true;
    }

    if(BlackPath.HasWon())
    {
      std::cout << "Black has completed a road!";
      result = true;
    }

    bool noempty=true;
    short int blacksquares=0;
    for(int i=0; i<BoardLength*BoardLength; i++)
    {
      if(Squares[i].WhatTop() == 0) 
        noempty = false;
      else if(Squares[i].top() && Squares[i].path())
        blacksquares++;
    }

    if(noempty)
    {
      result = true;
      if(blacksquares<BoardLength*BoardLength/2)
        std::cout << "No empty squares remain. White controls a majority of squares" << endl;
      else
        std::cout << "No empty squares remain. Black controls a majority of squares" << endl;
    }
  }


};
