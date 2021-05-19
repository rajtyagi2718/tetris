# alltests: main.o exception.o exceptiontest.o bitboard.o bitboardtest.o board.o boardtest.o piece.o piecetest.o agent.o agenttest.o game.o gametest.o graphics.o graphicsgame.o graphicsgametest.o searchgame.o searchgametest.o features.o featurestest.o
# 	g++ -std=c++17 main.o ../build/exception.o exceptiontest.o ../build/bitboard.o bitboardtest.o ../build/board.o boardtest.o ../build/piece.o piecetest.o ../build/agent.o agenttest.o ../build/game.o gametest.o ../build/graphics.o ../build/graphicsgame.o graphicsgametest.o ../build/searchgame.o searchgametest.o ../build/features.o featurestest.o -lsfml-graphics -lsfml-window -lsfml-system -lgtest -lgtest_main -pthread -o alltests

# create_graph: bitboard.o board.o piece.o grapher.o
	# g++ -std=c++17 build/bitboard.o build/board.o build/piece.o build/grapher.o src/create_graph.cpp -o build/create_graph

# test_game: bitboard.o board.o graph.o features.o agent.o search.o game.o
	# g++ -std=c++17 build/bitboard.o build/board.o build/graph.o build/features.o build/agent.o build/search.o build/game.o test/test_game.cpp -o test/test_game

test_graphics_game: bitboard.o board.o graph.o features.o agent.o search.o game.o graphics.o graphics_game.o
	g++ -std=c++17 build/bitboard.o build/board.o build/graph.o build/features.o build/agent.o build/search.o build/game.o build/graphics.o build/graphics_game.o -lsfml-graphics -lsfml-window -lsfml-system test/test_graphics_game.cpp -o test/test_graphics_game

bitboard.o:
	g++ -std=c++17 -c src/bitboard.cpp -o build/bitboard.o

board.o:
	g++ -std=c++17 -c src/board.cpp -o build/board.o

features.o:
	g++ -std=c++17 -Wno-narrowing -c src/features.cpp -o build/features.o

piece.o:
	g++ -std=c++17 -c src/piece.cpp -o build/piece.o

grapher.o:
	g++ -std=c++17 -c src/grapher.cpp -o build/grapher.o

graph.o:
	g++ -std=c++17 -c src/graph.cpp -o build/graph.o

search.o:
	g++ -std=c++17 -c src/search.cpp -o build/search.o

agent.o:
	g++ -std=c++17 -c src/agent.cpp -o build/agent.o

game.o:
	g++ -std=c++17 -c src/game.cpp -o build/game.o

graphics.o:
	g++ -std=c++17 -c src/graphics.cpp -o build/graphics.o

graphics_game.o:
	g++ -std=c++17 -c src/graphics_game.cpp -o build/graphics_game.o

clean:
	rm build/*.o
