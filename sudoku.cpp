////////////////////////////////////////////////
// File     : sudoku.cpp
// Author   : Jiri Kvita kvita@fnal.gov
// Purpose  : hold the sudoku class
// Created  : Jan 2006
// Modified : Feb 2008
////////////////////////////////////////////////
// future ideas: 
//
//

#include <iostream>
#include "sudoku.hpp"


using std::cout;
using std::cerr;
using std::endl;

// constructors:
//_________________________________

TSudoku::TSudoku() 
{

  for (int i = 0; i < dim; ++i) 
    for (int j = 0; j < dim; ++j) 
      _sudoku[i][j] = kEmpty;

  _initialised = false;
  _debug = 0;

}

TSudoku::TSudoku(TElement sudoku[dim][dim]) 
{

  _debug = 0;
  cout << "--- Initialising -  TSudoku::TSudoku ---" << endl;
  Assign(sudoku);
  cout << "  ...Initialised!" << endl;

}

//_________________________________

TSudoku::~TSudoku()
{

}

//_________________________________

bool TSudoku::ReadFromAscii(std::string filename)
{
  TElement sudoku[dim][dim];
  
  std::ifstream file(filename.c_str());
  if (file.is_open()) {

    int nlines = 0;
    int ncolumns = 0;
    TElement el;
    while ( file >> el ) {
      sudoku[nlines][ncolumns] = el;
      ncolumns++;
      if (ncolumns == dim) {
	ncolumns = 0;
	nlines++;
      }
    }
    file.close();
    if (nlines != dim) {
      cout << "ERROR: number of input lines in the file " << filename.c_str() << " does not match the requested dimension of " << dim << "!" << endl;
    } else {
      cout << "Sudoku correctly read from file " << filename.c_str() << endl;
      Assign(sudoku);
      return true;
    }
    
  } else {
    cout << "Error: file " << filename.c_str() << " not open!" << endl;
  }

  return false;

}

//_________________________________

bool TSudoku::DumpToAscii(std::string filename)
{

  cout << "Dumping sudoku to ascii file " << filename.c_str() << endl;
  std::ofstream file(filename.c_str());
  for (int i = 0; i < dim; ++i) {
    for (int j = 0; j < dim; ++j) {
      file << _sudoku[i][j];
      if (j == dim - 1)
	file << endl;
      else
	file << " ";
    }
  }
  
  file.close();
  return true;
  
}


//_________________________________
  
bool TSudoku::Assign(TElement sudoku[dim][dim])
{

  //  _sudoku = (TElement**) new int[dim][dim];
  for (int i = 0; i < dim; ++i) 
    for (int j = 0; j < dim; ++j) {
      if (debug() > 2) {
	cout << "Assigning [i,j]=[" << i << "," << j << "] with: " << endl;
	cout << "  " <<  sudoku[i][j] << endl;
      }
      _sudoku[i][j] = sudoku[i][j];
    }

  _initialised = true;
  return true;
}  

//_________________________________

bool TSudoku::isConsistent()
{
    
  if (!_initialised) {
    if (debug() > 0)
      cout << "Not consistent as we're not initialised!" << endl;
    return false;
  }

  if (!checkLines()) {
    if (debug() > 0)
      cout << "Not consistent: checkLines failes!" << endl;
    return false;
  }
  if (!checkColumns()) {
    if (debug() > 0)
      cout << "Not consistent: checkColumns failes!" << endl;
    return false;
  }
  if (!checkSubsquares()) {
    if (debug() > 0)
      cout << "Not consistent: checkSubsquares failes!" << endl;
    return false;
  }
  return true;
}
  
//_________________________________

bool TSudoku::checkLines()
{
  
  if (!_initialised)
    return false;

  bool _used[dim];
  
  for (int i = 0; i < dim; ++i) {
    for (int j = 0; j < dim; ++j) 
      _used[j] = false; 
    if (debug() > 0)
      cout << "Checking line " << i << endl;
    for (int j = 0; j < dim; ++j) 
      // we don't care about zeros there
      if (_sudoku[i][j] != kEmpty) {
	if (_used[_sudoku[i][j]-1]) {
	  // number already used before
	  if (debug() > 0)
	    cout << "Found already used figure at [i,j]=[" << i << "," << j << "] with " << _sudoku[i][j] << endl;
	  return false;
	}
	else {
	  // first occurence found
	  _used[_sudoku[i][j]-1] = true;
	  if (debug() > 0)
	    cout << "First occurence at [i,j]=[" << i << "," << j << "] of " << _sudoku[i][j] << endl;
	}
      } // if
  } // i

  return true;

}


//_________________________________

bool TSudoku::checkColumns()
{
  
  if (!_initialised)
    return false;

  if (debug() > 0) {
    cout << "===========================" << endl;
    cout << "Before transpositions:" << endl;
    Print();
  }
  Transpose();
  if (debug() > 0) {
    cout << "===========================" << endl;
    cout << "After transpositions:" << endl;
    Print();
  }

  bool isOK = checkLines();
  Transpose();
  if (debug() > 0) {
    cout << "===========================" << endl;
    cout << "Back again:" << endl;
    Print();
  }

  return isOK;

}

//_________________________________

bool TSudoku::checkSubsquares()
{
  if (!_initialised)
    return false;

  bool _used[dim];
  
  // we have 9 squares to check

  for (int isq = 0; isq < dim; ++isq) {

    if (debug() > 0) {
      cout << "--- checking subsquare " << isq << " ---" << endl;
      PrintSubSquare(isq);
    }

    // line begin index:
    int i0 = subdim * (isq / subdim);
    // column begin index:
    int j0 = subdim * (isq % subdim);
    
    TElement value;
    for (int j = 0; j < dim; ++j) 
      _used[j] = false; 
    
    for (int j = 0; j < dim; ++j) {
      value =_sudoku[i0 + j / subdim][j0 + j % subdim];
      // we don't care about zeros there
      if ( value != kEmpty) {
	if (_used[value - 1]) {
	  // number already used before
	  if (debug() > 0)
	    cout << "Found already used figure at [i,j]=[" 
		 << i0 + j / subdim << "," 
		 << j0 + j % subdim << "] localy  [i,j]=[" 
		 << j / subdim << "," 
		 << j % subdim << "]  with " 
		 << value << endl;
	  return false;
	}
	else {
	  // first occurence found
	  _used[value-1] = true;
	  if (debug() > 0)
	    cout << "First occurence at [i,j]=[" << i0 + j / subdim << "," 
		 << j0 + j % subdim << "], localy  [i,j]=[" 
		 << j / subdim << "," 
		 << j % subdim << "] of " 
		 << value << endl;
	}
      } // if
    } //j

  } // isq


  return true;

}

//_________________________________
  
bool TSudoku::hasNoHoles()
{

  // check there are no zeros

  for (int i = 0; i < dim; ++i) 
    for (int j = 0; j < dim; ++j) 
      if (_sudoku[i][j] == kEmpty)
	return false;

  return true;
}  

//_________________________________
  
int TSudoku::GetNHoles()
{

  // count holes
  int sum = 0;
  for (int i = 0; i < dim; ++i) 
    for (int j = 0; j < dim; ++j) 
      if (_sudoku[i][j] == kEmpty)
	sum++;
  
  return sum;
}  
  
//_________________________________

void TSudoku::Transpose()
{
  
  TElement help;
  for (int i = 0; i < dim; ++i) 
    for (int j = 0; j < dim; ++j) 
      if (i < j) {
	help = _sudoku[i][j];
	_sudoku[i][j] = _sudoku[j][i];
	_sudoku[j][i] = help;
      }
}  

//_________________________________

bool TSudoku::isCorrectSolution()
{

  if (!isConsistent())
    return false;

  if (!hasNoHoles())
    return false;

  return true;
}  
  
//_________________________________
//_________________________________

//_________________________________

void TSudoku::EvaluatePossibilities(bool possible[dim][dim][dim], bool print)
{
  
  if (print)
    cout << "subsquare indices: " << endl;
  

  for (int i = 0; i < dim; ++i)
    for (int j = 0; j < dim; ++j)
      for (int k = 0; k < dim; ++k)
	possible[i][j][k] = true;

  // evaluate possible values for every field of sudoku:
  for (int ii = 0; ii < dim; ++ii) {
    for (int jj = 0; jj < dim; ++jj) {
      if (_sudoku[ii][jj] != kEmpty) {
	if (print) {
	  cout << "X" << " ";
	  if (! ((jj + 1) % dim))
	    cout << endl;
	}
	continue;
      }

      // lines check:
      for (int kk = 0; kk < dim; ++kk) {
	TElement value = _sudoku[ii][kk];
	if (value != kEmpty)
	  possible[ii][jj][value - 1] = false;
      }

      // rows check:
      for (int kk = 0; kk < dim; ++kk) {
	TElement value = _sudoku[kk][jj];
	if (value != kEmpty)
	  possible[ii][jj][value - 1] = false;
      }

  
      // subsquares:
      // need to find out which subsquare we belong to:
      int isq = ( ii / subdim) * subdim + jj / subdim;

      if (print) {
	cout << isq << " ";
	if (! ((jj + 1) % dim))
	  cout << endl;
      }
      // line begin index:
      int i0 = subdim * (isq / subdim);
      // column begin index:
      int j0 = subdim * (isq % subdim);
      for (int j = 0; j < dim; ++j) {
	TElement value =_sudoku[i0 + j / subdim][j0 + j % subdim];
	if (value != kEmpty)
	  possible[ii][jj][value - 1] = false;
      }
      
    } // ii
  } // jj
  
  if (print)
    cout << endl;

}


//_________________________________


int TSudoku::EnforceIndividualValues(bool possible[dim][dim][dim], bool print)
{
  int didSomething = 0;
  // check for each value: at how many places can it be?
  // if at only one, enforce it!
  
  // --- in each row:
  //  int nPossible[dim];
  if (print)
    Print();
  int index = -1;
  for (int value = 0; value < dim; ++value) {
    for (int ii = 0; ii < dim; ++ii) {
      //      for (int value = 0; value < dim; ++value) 
      int nPossible = 0;
      for (int jj = 0; jj < dim; ++jj) {
	if (_sudoku[ii][jj] != kEmpty)
	  continue;

	if (possible[ii][jj][value]) {
	  nPossible++;
	  index = jj;
	}
      } // jj (columns)
      if (nPossible == 1) {
	if (print)
	  cout << "Found only solution for " << value + 1 << " based on row " << ii << " at index " << index << endl;
	_sudoku[ii][index] = value + 1;
	didSomething++;
	EvaluatePossibilities(possible, print && _debug);
	Print();
	PrintPossibilities(possible);
	cout <<"isConsistent: " << isConsistent() << endl;
      } else {
	if (print && _debug)
	  cout << "Found " << nPossible << " solutions for " << value + 1 << " in row " << ii << "." << endl;
      }
    } // ii (rows)
  } // value
  
  // --- in each column:
  if (print)
    Print();
  for (int value = 0; value < dim; ++value) {
    for (int jj = 0; jj < dim; ++jj) {
      //      for (int value = 0; value < dim; ++value) 
      int nPossible = 0;
      for (int ii = 0; ii < dim; ++ii) {
	if (_sudoku[ii][jj] != kEmpty)
	  continue;

	if (possible[ii][jj][value]) {
	  nPossible++;
	  index = ii;
	}
      } // ii (rows)
      if (nPossible == 1) {
	if (print)
	  cout << "Found only solution for " << value + 1 << " based on column " << jj << " at index " << index << endl;
	_sudoku[index][jj] = value + 1;
	didSomething++;
	EvaluatePossibilities(possible, print && _debug);
	Print();
	PrintPossibilities(possible);
	cout <<"isConsistent: " << isConsistent() << endl;
      } else {
	if (print && _debug)
	  cout << "Found " << nPossible << " solutions for " << value + 1 << " in column " << jj << "." << endl;
      }
    } // jj (columns)
  } // value
  

  // --- in each subsquare:
  if (print)
    Print();
  int i_only = -1;
  int j_only = -1;

  for (int value = 0; value < dim; ++value) {
    for (int isq = 0; isq < dim; ++isq) {
      //      cout << "Checking subsquare " << isq << ", value " << value+1 << endl;
      int nPossible = 0;
      // line begin index:
      int i0 = subdim * (isq / subdim);
      // column begin index:
      int j0 = subdim * (isq % subdim);
      for (int ii = 0; ii < dim; ++ii) {

	int i_current = i0 + ii / subdim;
	int j_current = j0 + ii % subdim;

	if (_sudoku[i_current][j_current] != kEmpty)
	  continue;

	if (possible[i_current][j_current][value]) {
	  nPossible++;
	  i_only = i_current;
	  j_only = j_current;
	}
      } // elements in a subsquare
      if (nPossible == 1) {
	if (print)
	  cout << "Found only solution for " << value + 1 << " based on subsquare " << isq << " at i,j " << i_only << "," << j_only << endl;
	_sudoku[i_only][j_only] = value + 1;
	didSomething++;
	EvaluatePossibilities(possible, print && _debug);
	Print();
	PrintPossibilities(possible);
	cout <<"isConsistent: " << isConsistent() << endl;
      } else {
	if (print && _debug)
	  cout << "Found " << nPossible << " solutions for " << value + 1 << " subsquare " << isq << "." << endl;
      }
    } // isq (subsquares)
  } // value

  

  return didSomething;

}

//_________________________________

int TSudoku::EnforceOnlySolutions(bool possible[dim][dim][dim], bool print)
{

  if (print)
    cout << "number of solutions: " << endl;

  int didSomething = 0;

 // evaluate possible values for every field of sudoku:
  for (int ii = 0; ii < dim; ++ii) {
    for (int jj = 0; jj < dim; ++jj) {
     
      if (_sudoku[ii][jj] != kEmpty) {
	if (print) {
	  cout << "X" << " ";
	  if (! ((jj + 1) % dim))
	    cout << endl;
	}
	continue;
      }
 
      int nsolutions = 0;
      TElement solution = kEmpty;
      for (int kk = 0; kk < dim; ++kk)
	if (possible[ii][jj][kk]) {
	  nsolutions++;
	  solution = kk;
	}
      
      cout << nsolutions << " ";
      if (! ((jj + 1) % dim))
	cout << endl;

      if (nsolutions == 1) {
	_sudoku[ii][jj] = solution + 1;
	didSomething++;
      }
    }
  } 

  if (print)
    cout << endl;


  return didSomething;

}

//_________________________________

void TSudoku::PrintPossibilities(bool possible[dim][dim][dim])
{
  int nPossible[dim][dim];
  //  bool print = false;
  //  EvaluatePossibilities(possible, print);

  cout << "Possible values: " << endl;
  for (int ii = 0; ii < dim; ++ii) {
    for (int jj = 0; jj < dim; ++jj) {
      nPossible[ii][jj] = 0;
      for (int value = 0; value < dim; ++value) {
	if (_sudoku[ii][jj] == kEmpty && possible[ii][jj][value]) {
	  cout << value + 1;
	  nPossible[ii][jj]++;
	}
      } // values
      if (_sudoku[ii][jj] != kEmpty) {
	cout << _sudoku[ii][jj];
	for (int kk = 0; kk < dim - 1; ++kk)
	  cout << " ";	
      } else {
	for (int kk = 0; kk < dim - nPossible[ii][jj]; ++kk)
	  cout << " ";
      }
    } // columns
    cout << endl;
  } // rows

}

//_________________________________

int TSudoku::solve()
{
    
  cout << "--- Solving the sudoku ---" << endl;

  if (!_initialised)
    return 0;

  bool possible[dim][dim][dim];
  bool print = true;
  int changed = 1;
  int totalChanges = 0;
  int iter = 0;
  while (changed) {
    
    cout << "=== Iteration: " << iter << " ===" << endl;
    Print();

    changed = 0;
    int changed1 = 0;
    int changed2 = 0;

    EvaluatePossibilities(possible, print);
    PrintPossibilities(possible);

    changed2 = EnforceIndividualValues(possible, print);
    if (!isConsistent())
      cout << "ERROR! After EnforceIndividualValues, Sudoku is not consistent any more!" << endl;
    totalChanges += changed2;

    changed1 = EnforceOnlySolutions(possible, print);
    if (!isConsistent())
      cout << "ERROR! After EnforceOnlySolutions, Sudoku is not consistent any more!" << endl;
    totalChanges += changed1;
    
    changed = (changed1 || changed2) && isConsistent();

    ++iter;

    cout << "  Individual values changes: " << changed2 << endl; 
    cout << "  Enforced only solutions changes: " << changed1 << endl; 
  }

  cout << "---> TSudoku::solve(): Total changes: " << totalChanges << endl;

    
  // when solved, return number of solutions!
  //  return 1;
  
  cout << "--- End of TSudoku::solve() ---" << endl;
  return (isCorrectSolution());

}

//_________________________________

void TSudoku::PrintPlain()
{
  if (!_initialised)
    return;

  for (int i = 0; i < dim; ++i) {
    for (int j = 0; j < dim; ++j) {
      cout << _sudoku[i][j];
      cout << " ";
    }
    cout << endl;
  }
}

//_________________________________

void TSudoku::Print()
{
  if (!_initialised)
    return;

  cout << "+-----+-----+-----+" << endl;
  for (int i = 0; i < dim; ++i) {
    for (int j = 0; j < dim; ++j) {
      if (j == 0)
	cout << "|";
      cout << _sudoku[i][j];
      if ( !((j+1) % subdim))
	cout << "|";
      else
	cout << " ";
    }
    if ( !((i+1) % subdim))
      cout << endl << "+-----+-----+-----+" << endl;      
    else
      cout << endl;
  }

}

//_________________________________

void TSudoku::PrintSubSquare(int isq)
{
  if (!_initialised)
    return;

  // line begin index:
  int i0 = subdim * (isq / subdim);
  // column begin index:
  int j0 = subdim * (isq % subdim);

  for (int i = 0; i < dim; ++i) {
    cout << _sudoku[i0 + i / subdim][j0 + i % subdim] << " ";
    if ((i+1) % subdim == 0)
      cout << endl;
  }

}

//_________________________________

int TSudoku::debug()
{
  return _debug;
}
//_________________________________

void TSudoku::SetDebug(int debug)
{
  _debug = debug;
}
//_________________________________

