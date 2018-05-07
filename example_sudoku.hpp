

#ifndef EXAMPLE_SUDOKU
#define EXAMPLE_SUDOKU

TElement sudoku2[dim][dim] = { {3,6,0, 0,0,4, 0,0,0},
			       {5,0,0, 0,9,0, 0,0,0},
			       {0,7,4, 0,2,0, 0,0,5},
			       {0,0,2, 0,7,0, 0,0,1},
			       {0,4,0, 0,0,0, 0,5,0},
			       {6,0,0, 0,8,0, 7,0,0},
			       {2,0,0, 0,4,0, 3,6,0},
			       {0,0,0, 0,1,0, 0,0,8},
			       {0,0,0, 8,0,0, 0,4,9}  };
  

// solution of sudoku3:
TElement sudoku1[dim][dim] = { {4,9,3, 6,5,2, 1,7,8},
			       {6,8,2, 7,1,3, 5,9,4},
			       {7,1,5, 4,9,8, 2,3,6},
			       {1,6,4, 2,8,9, 7,5,3},
			       {5,3,9, 1,4,7, 6,8,2},
			       {2,7,8, 3,6,5, 9,4,1},
			       {9,5,6, 8,3,1, 4,2,7},
			       {8,4,7, 9,2,6, 3,1,5},
			       {3,2,1, 5,7,4, 8,6,9} };


// solution of sudoku3 with knock-out'ed few fields:
TElement sudoku3x[dim][dim] = { {4,0,3, 6,5,2, 1,7,8},
				{6,0,2, 7,1,3, 5,0,4},
				{7,1,5, 4,9,8, 2,3,6},
				{1,6,0, 0,8,9, 7,5,3},
				{5,3,9, 1,4,7, 6,8,2},
				{2,7,8, 3,6,5, 9,4,1},
				{9,0,6, 0,3,1, 4,2,7},
				{0,0,7, 9,2,6, 0,1,0},
				{3,2,1, 5,7,4, 8,6,9} };

// assignment:
TElement sudoku3[dim][dim] = { {4,0,3, 0,5,0, 0,0,8},
			       {0,0,0, 7,1,0, 5,0,0},
			       {0,0,0, 0,0,0, 0,3,6},
			       {0,0,4, 2,0,9, 7,0,0},
			       {0,0,9, 1,0,7, 6,0,0},
			       {0,0,8, 0,0,0, 9,4,0},
			       {0,5,0, 0,0,0, 4,2,0},
			       {0,0,0, 9,0,0, 0,1,0},
			       {3,2,0, 0,0,0, 0,0,0} };

// assignment:

TElement sudoku4[dim][dim] = { {0,2,5, 0,0,0, 0,0,0},
			       {0,0,0, 3,0,0, 7,6,4},
			       {0,3,0, 6,8,0, 0,0,0},
			       {2,5,3, 0,0,0, 0,0,0},
			       {0,0,9, 0,0,0, 0,3,6},
			       {0,0,0, 7,2,0, 0,5,0},
			       {0,8,0, 0,0,4, 0,0,0},
			       {0,6,2, 0,0,0, 0,0,9},
			       {0,0,0, 0,0,5, 4,8,2} };

TElement sudoku5[dim][dim] = { {3,0,0, 0,0,9, 5,0,0},
			       {0,0,0, 0,0,0, 4,7,0},
			       {6,7,0, 0,0,3, 0,0,0},
			       {0,3,9, 0,2,0, 7,0,0},
			       {0,0,0, 1,0,0, 9,0,0},
			       {0,0,5, 4,0,0, 0,0,0},
			       {0,0,0, 0,0,0, 0,8,2},
			       {0,0,0, 5,1,0, 0,0,0},
			       {4,6,7, 0,0,0, 0,0,0} };
  
TElement sudoku_empty[dim][dim] = { {0,0,0, 0,0,0, 0,0,0},
				    {0,0,0, 0,0,0, 0,0,0},
				    {0,0,0, 0,0,0, 0,0,0},
				    {0,0,0, 0,0,0, 0,0,0},
				    {0,0,0, 0,0,0, 0,0,0},
				    {0,0,0, 0,0,0, 0,0,0},
				    {0,0,0, 0,0,0, 0,0,0},
				    {0,0,0, 0,0,0, 0,0,0},
				    {0,0,0, 0,0,0, 0,0,0} };

#endif
