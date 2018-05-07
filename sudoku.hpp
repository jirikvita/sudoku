////////////////////////////////////////////////
// File     : sudoku.hpp
// Author   : Jiri Kvita kvita@fnal.gov
// Purpose  : hold the sudoku class
// Created  : Jan 2006
// Modified : Feb 2008
////////////////////////////////////////////////

// it should be dim = subdim*subdim
// in genereal, e.g. subdim 3 or 4 should be possible
const int dim = 9;
const int subdim = 3;

// other typedef like e.g. char enables also character sudoku
// unfortunatelly, we use values also for indexing, so a map between TElement and int would be in fact needed...

typedef int TElement;

const TElement kEmpty = 0;


#include <fstream>

class TSudoku
{

private:
  bool _initialised;
  TElement _sudoku[dim][dim];
  //  int** _sudoku;
  int _debug;

public:

  TSudoku();
  TSudoku(int sudoku[dim][dim]);
  ~TSudoku();

  bool Assign(int sudoku[dim][dim]);
  bool ReadFromAscii(std::string filename);
  bool DumpToAscii(std::string filename);

  bool isConsistent();
  int EnforceOnlySolutions(bool possible[dim][dim][dim], bool print);
  int EnforceIndividualValues(bool possible[dim][dim][dim], bool print);
  void EvaluatePossibilities(bool possible[dim][dim][dim], bool print);
  void PrintPossibilities(bool possible[dim][dim][dim]);
  int solve();

  bool checkLines();
  bool checkColumns();
  bool checkSubsquares();

  void Transpose();

  bool hasNoHoles();
  int GetNHoles();
  bool isCorrectSolution();

  void Print();
  void PrintPlain();
  void PrintSubSquare(int isq);

  int debug();
  void SetDebug(int debug);

};
