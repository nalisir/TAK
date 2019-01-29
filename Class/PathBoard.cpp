#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>

class PathBoard
{

private:

  std::vector<bool> Map;
  
  short int BoardLength;

public:

  PathBoard(int Blength) : Map(Blength*Blength, false)
  {
    this->BoardLength = Blength; 
    int tempnode;
  }


  ~PathBoard()
  {
  }


  bool HasWon(std::vector<int> *neighbours)
  {
    bool result = false;

    std::vector<bool> NoVisitedH(BoardLength*BoardLength, true);
    std::vector<bool> NoVisitedV(BoardLength*BoardLength, true);

    for(short int i=0; i<BoardLength; i++)
    {
      SeeNodeH(i, &NoVisitedH, neighbours, &result);
      SeeNodeV(i*BoardLength, &NoVisitedV, neighbours, &result);
    }

    return *result;
  }


  void SeeNodeH(int Node, std::vector<bool> *NoVisit, std::vector<int> *neighb, bool *res)
  {
    if(!(*res))
      if(this->Map[Node] && (*NoVisit)[Node])
      {
        (*NoVisit)[Node] = false;
        if(Node/BoardLength + 1 == BoardLength)
          *res = true;
        else
        {
          for(short int i=0; i<this->(*neighb)[Node].size(); i++)
            if((*neighb)[Node][i] >= 0)
              SeeNodeH((*neighb)[Node][i], NoVisit, res);
        }
      }
  }


  void SeeNodeV(int Node, std::vector<bool> *NoVisit, std::vector<int> *neighb,  bool *res)
  {
    if(!(*res))
      if(this->Map[Node] && (*NoVisit)[Node])
      {
        (*NoVisit)[Node] = false;
        if(Node - (Node/BoardLength)*BoardLength + 1 == BoardLength)
          *res = true;
        else
        {
          for(short int i=0; i<this->(*neighb)[Node].size(); i++)
            if((*neighb)[Node][i] >= 0)
              SeeNodeV((*neighb)[Node][i], NoVisit, res);
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
