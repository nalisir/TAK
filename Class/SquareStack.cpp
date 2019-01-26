#include <vector>
#include <stack>

class SquareStack
{

private:
  std::vector<bool> Stack;

  bool Pathable; // Can the square form a path
  bool Steppable; // Can a piece be put on top of this square

public:

  SquareStack() : Stack()
  {
    Pathable = false;
    Steppable = true;
  }


  bool path()
  {
    return this->Pathable;
  }


  bool step()
  {
    return this->Steppable;
  }


  bool color()
  {
    return this->Stack.back();
  }


  void add(bool value)
  {
    Stack.push_back(value);
  }

  short int WhatTop()
  {
    short int type = 0;
    if(this->Pathable) type++;
    if(!(this->Steppable)) type+=2;
    return type;
  }

  bool ChangeTop(short int type)
  {
    switch(type)
    {
      case 0: // Empty
        this->Pathable = false; this->Steppable = true;
        break;

      case 1: // Flat
        this->Pathable = true; this->Steppable = true;
        break;

      case 2: // Standing
        this->Pathable = false; this->Steppable = false;
        break;

      case 3: // Capstone
        this->Pathable = true; this->Steppable = false;
        break;

      default:
        std::cerr << "Error: Piece type does not exist" << endl;
        return false;
        break;
    }
    return true;
  }


  bool take(short int howmany, std::stack<bool> *transfer)
  {
    if(howmany > Stack.size())
    {
      std::cerr << "Error: Not enough pieces in the square" << endl;
      return false;
    }
    else if(howmany < Stack.size())
      ChangeTop(1); // Top is a Flat now
    else
      ChangeTop(0); // Square is empty

    for(short int i=0; i<howmany; i++)
    {
      (*transfer).push(this->Stack.back());
      this->Stack.pop_back();
    }
    return true;
  }

};
