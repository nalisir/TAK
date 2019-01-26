#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>

class PathBoard
{

private:

  std::vector<bool> Map;
  std::vector<short int> *Neighbours;

  short int BoardLength;

public:

  PathBoard(int Blength) : Map(Blength*Blength, false)
  {
    this->BoardLength = Blength; 
    this->Neighbours = new std::vector<short int> [Blength*Blength];

    int tempnode;
    for(int i=0; i<Blength; i++)
      for(int j=0; j<Blength; j++)
      {
        tempnode = i*Blength + j;
        if( i+1 != Blength) this->Neighbours[tempnode].push_back(tempnode + Blength); // Right
        if( j+1 != Blength) this->Neighbours[tempnode].push_back(tempnode + 1); // Down
        if( i != 0) this->Neighbours[tempnode].push_back(tempnode - Blength); // Left
        if( j != 0) this->Neighbours[tempnode].push_back(tempnode - 1); // Up
      }
  }


  ~PathBoard()
  {
  }


  bool HasWon()
  {
    bool result[1];
    *result = false;

    std::vector<bool> NoVisitedH(BoardLength*BoardLength, true);
    std::vector<bool> NoVisitedV(BoardLength*BoardLength, true);

    for(short int i=0; i<BoardLength; i++)
    {
      SeeNodeH(i, &NoVisitedH, result);
      SeeNodeV(i*BoardLength, &NoVisitedV, result);
    }

    return *result;
  }


  void SeeNodeH(int Node, std::vector<bool> *NoVisit,  bool *res)
  {
    if(!(*res))
      if(this->Map[Node] && (*NoVisit)[Node])
      {
        (*NoVisit)[Node] = false;
        if(Node/BoardLength + 1 == BoardLength)
          *res = true;
        else
        {
          for(short int i=0; i<this->Neighbours[Node].size(); i++)
            SeeNodeH(Neighbours[Node][i], NoVisit, res);
        }
      }
  }


  void SeeNodeV(int Node, std::vector<bool> *NoVisit,  bool *res)
  {
    if(!(*res))
      if(this->Map[Node] && (*NoVisit)[Node])
      {
        (*NoVisit)[Node] = false;
        if(Node - (Node/BoardLength)*BoardLength + 1 == BoardLength)
          *res = true;
        else
        {
          for(short int i=0; i<this->Neighbours[Node].size(); i++)
            SeeNodeV(Neighbours[Node][i], NoVisit, res);
        }
      } 
  }


  inline void Modify(int Node, bool value)
  {
    this->Map[Node] = value;
  }


  void print(std::ofstream& out)
  {
    for(int i=0; i<BoardLength; i++)
    {
      for(int j=0; j<BoardLength*BoardLength; j+=BoardLength)
        out << Map[j+i] << "\t";
      out << "\n";
    }
  }


  void print(std::ostream& out)
  {
    for(int i=0; i<BoardLength; i++)
    {
      for(int j=0; j<BoardLength*BoardLength; j+=BoardLength)
        out << Map[j+i] << "\t";
      out << "\n";
    }
  }


};
