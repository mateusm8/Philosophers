NAME = philosophers
CC = cc

CFLAGS = -g -Iinclude -Wall -Wextra -Werror # -fsanitize=address -fno-omit-frame-pointer 
LDFLAGS = -pthread

SRC = 	src/execution/actions.c \
		src/execution/monitor.c \
		src/execution/philosophers.c \
		src/parse/cleanup.c \
		src/parse/init.c \
		src/parse/parse.c \
		src/parse/populate.c \
		src/parse/threads.c \
		src/utils/ft_atol.c
	
OBJ = $(SRC:src/%.c=obj/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo "Makefile successfully compiled"

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf obj

fclean: clean
	@rm -f $(NAME)
	@echo "All files have been deleted."

re: fclean all

reclear:
	make re && clear

r: reclear
	@./$(NAME)

v: reclear
	 valgrind  ./$(NAME)

vl: reclear
	valgrind --leak-check=full --show-leak-kinds=all  ./$(NAME)

vc: reclear
	valgrind --track-origins=yes  ./$(NAME)

vall: reclear
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes  ./$(NAME)

.PHONY: all clean fclean re r
