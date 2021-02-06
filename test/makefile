alltests: main.o exceptiontest.o exception.o bitboard_internaltest.o bitboard_internal.o bitboardtest.o bitboard.o boardtest.o board.o piecetest.o piece.o
	g++ -std=c++17 main.o exceptiontest.o ../build/exception.o bitboard_internaltest.o ../build/bitboard_internal.o bitboardtest.o ../build/bitboard.o boardtest.o ../build/board.o piecetest.o ../build/piece.o -lgtest -lgtest_main -pthread -o alltests

main.o:
	g++ -std=c++17 -c main.cpp -o main.o

exceptiontest.o:
	g++ -std=c++17 -c exceptiontest.cpp -o exceptiontest.o

exception.o:
	g++ -std=c++17 -c ../src/exception.cpp -o ../build/exception.o

bitboard_internaltest.o:
	g++ -std=c++17 -c bitboard_internaltest.cpp -o bitboard_internaltest.o

bitboard_internal.o:
	g++ -std=c++17 -c ../src/bitboard_internal.cpp -o ../build/bitboard_internal.o

bitboardtest.o:
	g++ -std=c++17 -c bitboardtest.cpp -o bitboardtest.o

bitboard.o:
	g++ -std=c++17 -c ../src/bitboard.cpp -o ../build/bitboard.o

boardtest.o:
	g++ -std=c++17 -c boardtest.cpp -o boardtest.o

board.o:
	g++ -std=c++17 -c ../src/board.cpp -o ../build/board.o

piecetest.o:
	g++ -std=c++17 -c piecetest.cpp -o piecetest.o

piece.o:
	g++ -std=c++17 -c ../src/piece.cpp -o ../build/piece.o

clean:
	rm ./alltests *.o
