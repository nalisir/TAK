#include <GameBoard.cpp>
#include <observable.cpp>
#include <cstdlib>
#include <ctime>
#include <chrono>

int main()
{
  GameBoard board(6);
  srand(time(nullptr)); // use current time as seed for random generator
  Observable out("DFS_delay", 2, "#Nr\tSeconds");
  chrono::high_resolution_clock::time_point currentT;
  bool value;
  int counter;

  while(true)
  {
    counter = 0;
    for(int i=0; i<36; i++) 
    {
      value = rand()%2;
      board.Modify (i, value);
      if(value) counter++;
    }

    board.print(cout);
    out(counter);
    currentT = chrono::high_resolution_clock::now();
    if(board.HasWon())
      cout << "\n" << "YES" << endl;
    else
      cout << "\n" << "NO" << endl;
    out(chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - currentT).count());
  }
  return 0;
}
    
