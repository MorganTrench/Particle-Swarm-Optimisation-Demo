CC=clang++
FLAGS= -framework sfml-graphics -framework sfml-window -framework sfml-system

make:
	$(CC) main.cpp $(FLAGS) -o test

run:
	./test