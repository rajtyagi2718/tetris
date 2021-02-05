alltests: main.o exceptiontest.o exception.o bitutilstest.o bitutils.o boardtest.o board.o
	g++ -std=c++17 main.o exceptiontest.o ../build/exception.o bitutilstest.o ../build/bitutils.o boardtest.o ../build/board.o -lgtest -lgtest_main -pthread -o alltests

main.o:
	g++ -std=c++17 -c main.cpp -o main.o

exceptiontest.o:
	g++ -std=c++17 -c exceptiontest.cpp -o exceptiontest.o

exception.o:
	g++ -std=c++17 -c ../src/exception.cpp -o ../build/exception.o

boardtest.o:
	g++ -std=c++17 -c boardtest.cpp -o boardtest.o

board.o:
	g++ -std=c++17 -c ../src/board.cpp -o ../build/board.o

bitutilstest.o:
	g++ -std=c++17 -c bitutilstest.cpp -o bitutilstest.o

bitutils.o:
	g++ -std=c++17 -c ../src/bitutils.cpp -o ../build/bitutils.o

clean:
	rm ./alltests *.o
