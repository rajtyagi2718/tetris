alltests: main.o exception.o exceptiontest.o bitboard.o bitboardtest.o board.o boardtest.o piece.o piecetest.o agent.o agenttest.o game.o gametest.o
	g++ -std=c++17 main.o ../build/exception.o exceptiontest.o ../build/bitboard.o bitboardtest.o ../build/board.o boardtest.o ../build/piece.o piecetest.o ../build/agent.o agenttest.o ../build/game.o gametest.o -lgtest -lgtest_main -pthread -o alltests

main.o:
	g++ -std=c++17 -c main.cpp -o main.o

exception.o:
	g++ -std=c++17 -c ../src/exception.cpp -o ../build/exception.o

exceptiontest.o:
	g++ -std=c++17 -c exceptiontest.cpp -o exceptiontest.o

bitboard.o:
	g++ -std=c++17 -c ../src/bitboard.cpp -o ../build/bitboard.o

bitboardtest.o:
	g++ -std=c++17 -c bitboardtest.cpp -o bitboardtest.o

board.o:
	g++ -std=c++17 -c ../src/board.cpp -o ../build/board.o

boardtest.o:
	g++ -std=c++17 -c boardtest.cpp -o boardtest.o

piece.o:
	g++ -std=c++17 -c ../src/piece.cpp -o ../build/piece.o

piecetest.o:
	g++ -std=c++17 -c piecetest.cpp -o piecetest.o

agent.o:
	g++ -std=c++17 -c ../src/agent.cpp -o ../build/agent.o

agenttest.o:
	g++ -std=c++17 -c agenttest.cpp -o agenttest.o

game.o:
	g++ -std=c++17 -c ../src/game.cpp -o ../build/game.o

gametest.o:
	g++ -std=c++17 -c gametest.cpp -o gametest.o

clean:
	rm ./alltests *.o
