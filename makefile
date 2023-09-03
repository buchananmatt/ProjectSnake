output:

main.o:

demo:
	clang++ -std=gnu++14 -lncurses ./test/demo.cpp -o ./test/demo.out

clean: