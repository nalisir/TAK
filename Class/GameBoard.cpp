#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class GameBoard
{

private:

  vector<bool> Map;

  int BoardLength;
  // int dir[4];

public:

  GameBoard(int Blength) : Map(Blength*Blength, false)
  {
    BoardLength = Blength;
    // dir[0] = Blength; // right
    // dir[1] = 1; // down
    // dir[2] = -Blength; // left
    // dir[3] = -1; // up
  }


  ~GameBoard()
  {}


  bool HasWon()
  {
    bool result[1];
    *result = false;

    vector<bool> visitedH(BoardLength*BoardLength, false);
    vector<bool> visitedV(BoardLength*BoardLength, false);

    for(int i=0; i<BoardLength; i++)
    {
      SeeNodeH(i, visitedH, result);
      SeeNodeV(i*BoardLength, visitedV, result);
    }

    return *result;
  }


  void SeeNodeH(int Node, vector<bool> visit,  bool *res)
  {
    if(!(*res) && Node>0 && Node<BoardLength*BoardLength)
      if(this->Map[Node] && !(visit[Node]))
      {
        visit[Node] = true;
        if(Node/BoardLength + 1 == BoardLength || *res)
          *res = true;
        else
        {
          SeeNodeH(Node+BoardLength, visit, res);
          SeeNodeH(Node+1, visit, res);
          SeeNodeH(Node-1, visit, res);
          SeeNodeH(Node-BoardLength, visit, res);
        }
      }
  }


  void SeeNodeV(int Node, vector<bool> visit,  bool *res)
  {
    if(!(*res) && Node>0 && Node<BoardLength*BoardLength)
      if(this->Map[Node] && !(visit[Node]))
      {
        visit[Node] = true;
        if(Node - Node/BoardLength + 1 == BoardLength)
          *res = true;
        else
        {
          SeeNodeV(Node+1, visit, res);
          SeeNodeV(Node+BoardLength, visit, res);
          SeeNodeV(Node-BoardLength, visit, res);
          SeeNodeV(Node-1, visit, res);
        }
      }
  }


  inline void Modify(int Node, bool value)
  {
    this->Map[Node] = value;
  }


  void print(ofstream out)
  {
    for(int i=0; i<BoardLength; i++)
    {
      for(int j=0; j<BoardLength*BoardLength; j+=BoardLength)
        out << Map[j+i] << "\t";
      out << "\n";
    }
  }


  void print(ostream& out)
  {
    for(int i=0; i<BoardLength; i++)
    {
      for(int j=0; j<BoardLength*BoardLength; j+=BoardLength)
        out << Map[j+i] << "\t";
      out << "\n";
    }
  }


};
