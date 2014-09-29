FLAGS=-std=c++0x -g3 -O2 -Wall
CC=clang++
NAME=nick_normalize

%.o: ./src/%.cpp
	$(CC) $(FLAGS) -c $<

test: test.o
	$(CC) $(FLAGS) -o test_$(NAME) $^

all: test tst_set.o common.o edge.o node.o graph.o main.o
	$(CC) $(FLAGS) -o $(NAME) $^

clean:
	rm *.o
	rm $(NAME)
