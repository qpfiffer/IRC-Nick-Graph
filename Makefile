FLAGS=-std=c++0x -O2
CC=clang++
NAME=nick_normalize

all:
	$(CC) $(FLAGS) -o $(NAME) *.cpp
	
test: all
	./$(NAME) log.txt
