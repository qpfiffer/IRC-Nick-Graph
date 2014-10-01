FLAGS=-std=c++0x -g3 -O2 -Wall
CC=clang++
NAME=nick_normalize

%.o: ./src/%.cpp
	$(CC) $(FLAGS) -c $<

all: test nick_graph

test: test.o
	$(CC) $(FLAGS) -o test_$(NAME) $^

nick_graph: tst_map.o common.o edge.o node.o graph.o main.o
	$(CC) $(FLAGS) -o $(NAME) $^

clean:
	rm *.o
	rm $(NAME)
	rm test_$(NAME)
