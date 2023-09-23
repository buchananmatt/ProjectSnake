CXX=clang++
CXXFLAGS=-std=gnu++14

output: ./src/main.o ./src/game/game.o ./src/printer/printer.o
	g++ -lncurses ./src/main.o ./src/game/game.o ./src/printer/printer.o -o ./bin/snake.out

main.o: ./src/main.cpp
	g++ -c ./src/main.cpp ./bin/main.o

game.o: ./src/game/game.cpp	./src/game/game.hpp
	g++ -c ./src/game/game.cpp ./bin/game.o

printer.o: ./src/printer/printer.cpp ./src/printer/printer.hpp
	g++ -c ./src/printer/printer.cpp ./bin/printer.o

demo:
	clang++ -std=gnu++14 -lncurses ./test/demo.cpp -o ./test/demo.out

debug:
	clang++ -std=gnu++14 -lncurses ./src/main.cpp ./src/game/game.cpp ./src/printer/printer.cpp ./src/debug/debug_printer.cpp -o ./bin/snake_debug.out

clean:
	rm ./src/*.o
	rm ./game/*.o
	rm ./printer/*.o

run:
	./bin/snake.out
