////////////////////////////////////////////////
// File     : SuDoKu.cpp
// Author   : Jiri Kvita kvita@fnal.gov
// Purpose  : run the sudoku example
// Created  : Jan 2006
// Modified : Feb 2008
////////////////////////////////////////////////

#include <iostream>
#include "sudoku.hpp"
#include "example_sudoku.hpp"

using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char *argv[])

{

  TSudoku *tsudoku = 0;

  std::string filename = "";
  if (argc > 1) {
    cout << "OK, we got one command line argument, we understand it is a file name containing a sudoku to read and solve!" << endl;
    filename = argv[1];
    tsudoku = new TSudoku();
    tsudoku -> ReadFromAscii(filename);
    cout << "Sudoku read: " << endl;
    tsudoku -> Print();
  } else {
    cout << "Usage: " << argv[0] << " [filename]" << endl;
    cout << "As we did not get any file name with a sudoku to solve, we will use some default one as an example..." << endl;

    // choose here sudoku to try to solve:

    // medium:
    //    tsudoku = new TSudoku(sudoku2);
    //    tsudoku = new TSudoku(sudoku2);
    //    tsudoku -> DumpToAscii("sudoku2.txt");

    //    tsudoku = new TSudoku(sudoku3);
    //    tsudoku = new TSudoku(sudoku3);
    //    tsudoku -> DumpToAscii("sudoku3.txt");

    //    tsudoku = new TSudoku(sudoku4);
    //    tsudoku = new TSudoku(sudoku4);
    //    tsudoku -> DumpToAscii("sudoku4.txt");

    // hard:
    // tsudoku = new TSudoku(sudoku5);
    tsudoku = new TSudoku(sudoku5);
    //    tsudoku -> DumpToAscii("sudoku5.txt");
  }

  cout << " Sudoku to solve: " << endl;
  tsudoku -> Print();
  tsudoku -> SetDebug(0);
  //  tsudoku -> SetDebug(1);

  cout << "Checking consistency of the assignment: " << endl;
  if (!tsudoku -> isConsistent())
    cout << "Incorrectly assigned! No point solving!" << endl;
  else
    cout << "Correctly assigned!" << endl;

  cout << " isConsistent      : " << tsudoku -> isConsistent()      << endl;
  cout << " hasNoHoles        : " << tsudoku -> hasNoHoles()        << endl;
  cout << " nHoles            : " << tsudoku -> GetNHoles()         << endl;
  cout << " isCorrectSolution : " << tsudoku -> isCorrectSolution() << endl;

  
  if (tsudoku -> isCorrectSolution()) {
    cout << "Sudoku is already solved! No point solving! ;-)" << endl;
    return 0;
  }

  if (tsudoku -> isConsistent()) {
    // solve:
    int nsolutions = tsudoku -> solve();
    if (nsolutions > 0)
      cout << "Found " << nsolutions << " solutions." << endl;
    else
      cout << "No final solution found!" << endl;

    // print result:
    if (tsudoku -> isCorrectSolution())
      cout << "Is correct solution!" << endl;
    else {
      cout << "Is NOT final solution!" << endl;
      if (!tsudoku -> isConsistent())
	cout << "...and is also inconsistent!:(" << endl;
      else
	cout << "...but still consistent!:)" << endl;

    }
    tsudoku -> Print();

  } // was correctly assigned

  return 0;

}
