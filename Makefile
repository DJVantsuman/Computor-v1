NAME =	computor.exe
FLAGS = -Wall -Werror -Wextra -std=c++11
SRC = main.cpp computor,cpp
CC = clang++
OSRC =	$(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OSRC)
        clang++ -o $(NAME) $(FLAGS) $(OSRC)

%.o: %.cpp
        clang++ $(FLAGS) -c -o $@ $<

clean:
        rm -f *.o

fclean: clean
        rm -f $(NAME)

re: fclean all
