
GREEN = \033[32;01m
RED = \033[31;01m
BLUE = \033[34;01m
RESET = \033[0m
YELLOW = \033[33;01m

NAME = scrapper

SRC = \
main.cpp \
CurlRequest.cpp \
ParseJson.cpp \
Scraper.cpp \

OBJ = $(SRC:.cpp=.o)

CC = g++

FLAGS = -Wall -Wextra -Werror -Wshadow -std=c++11

LIBS = -ljsoncpp -lcurl

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LIBS)
	@printf "$(GREEN)Program built successfully! $(RESET)\n"

%.o: %.cpp
	@$(CC) $(FLAGS) -c -o $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re