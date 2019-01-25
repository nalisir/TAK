#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class PathBoard
{

private:

  vector<bool> Map;

  int BoardLength;
  // int dir[4];

public:

  PathBoard(int Blength) : Map(Blength*Blength, false)
  {
    BoardLength = Blength;
    // dir[0] = Blength; // right
    // dir[1] = 1; // down
    // dir[2] = -Blength; // left
    // dir[3] = -1; // up
  }


  ~PathBoard()
  {}


  bool HasWon()
  {
    bool result[1];
    *result = false;

    vector<bool> NoVisitedH(BoardLength*BoardLength, true);
    vector<bool> NoVisitedV(BoardLength*BoardLength, true);

    for(int i=0; i<BoardLength; i++)
    {
      SeeNodeH(i, NoVisitedH, result);
      SeeNodeV(i*BoardLength, NoVisitedV, result);
    }

    return *result;
  }


  void SeeNodeH(int Node, vector<bool> NoVisit,  bool *res)
  {
    if(!(*res) && Node>0 && Node<BoardLength*BoardLength)
      if(this->Map[Node] && NoVisit[Node])
      {
        NoVisit[Node] = false;
        if(Node/BoardLength + 1 == BoardLength || *res)
          *res = true;
        else
        {
          SeeNodeH(Node+BoardLength, NoVisit, res);
          SeeNodeH(Node+1, NoVisit, res);
          SeeNodeH(Node-1, NoVisit, res);
          SeeNodeH(Node-BoardLength, NoVisit, res);
        }
      }
  }


  void SeeNodeV(int Node, vector<bool> NoVisit,  bool *res)
  {
    if(!(*res) && Node>0 && Node<BoardLength*BoardLength)
      if(this->Map[Node] && NoVisit[Node])
      {
        NoVisit[Node] = false;
        if(Node - Node/BoardLength + 1 == BoardLength)
          *res = true;
        else
        {
          SeeNodeV(Node+1, NoVisit, res);
          SeeNodeV(Node+BoardLength, NoVisit, res);
          SeeNodeV(Node-BoardLength, NoVisit, res);
          SeeNodeV(Node-1, NoVisit, res);
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
