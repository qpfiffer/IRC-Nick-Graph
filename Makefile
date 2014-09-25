FLAGS=-std=c++0x -g3 -O2 -Wall
CC=clang++
NAME=nick_normalize

%.o: ./src/%.cpp
	$(CC) $(FLAGS) -c $<

all: common.o edge.o node.o graph.o main.o
	$(CC) $(FLAGS) -o $(NAME) $^

clean:
	rm *.o
	rm $(NAME)

test: all
	./$(NAME) log.txt
