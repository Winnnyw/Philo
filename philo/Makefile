NAME        = philo
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -pthread
RM          = rm -f

SRC         = main.c \
              utils.c \
			  routine.c \
			  monitor.c \
			  utils2.c 

OBJ         = $(SRC:.c=.o)

# ======================= RÈGLES ==========================
all: $(NAME)

# Build push_swap uniquement si .o ou libft.a ont changé
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# Compile .c → .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des .o
clean:
	$(RM) $(OBJ)
# Nettoyage complet
fclean: clean
	$(RM) $(NAME)
# Recompile propre
re: fclean all

# Compilation debug
debug: CFLAGS += -g3 -fsanitize=address -fsanitize=mutex
debug: re

# Norminette
norm:
	norminette $(SRC) *.h

# ======================= PHONY ==========================
.PHONY: all clean fclean re debug norm
