

CPP=g++ -g

SuDoKu_x: sudoku.o SuDoKu.o
	$(CPP) -o SuDoKu_x sudoku.o SuDoKu.o

sudoku.o: sudoku.cpp sudoku.hpp
	$(CPP) -c sudoku.cpp 

SuDoKu.o: SuDoKu.cpp 
	$(CPP) -c SuDoKu.cpp 
clean:
	rm *.o SuDoKu_x
