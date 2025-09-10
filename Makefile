CC = gcc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I./includes -I./libft

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# ---------- Mandatory ----------
SRCS_SERVER = server.c utils.c
SRCS_CLIENT = client.c utils.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

NAME_SERVER = server
NAME_CLIENT = client

# ---------- Bonus ----------
SRCS_SERVER_BONUS = server_bonus.c utils_bonus.c
SRCS_CLIENT_BONUS = client_bonus.c utils_bonus.c

OBJS_SERVER_BONUS = $(SRCS_SERVER_BONUS:.c=.o)
OBJS_CLIENT_BONUS = $(SRCS_CLIENT_BONUS:.c=.o)

NAME_SERVER_BONUS = server_bonus
NAME_CLIENT_BONUS = client_bonus

# ---------- Rules ----------
all: $(LIBFT) $(NAME_SERVER) $(NAME_CLIENT)

bonus: $(LIBFT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

$(LIBFT):
	@make -C $(LIBFT_DIR)

# --- Mandatory targets ---
$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBFT) $(INCLUDES) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBFT) $(INCLUDES) -o $(NAME_CLIENT)

# --- Bonus targets ---
$(NAME_SERVER_BONUS): $(OBJS_SERVER_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_SERVER_BONUS) $(LIBFT) $(INCLUDES) -o $(NAME_SERVER_BONUS)

$(NAME_CLIENT_BONUS): $(OBJS_CLIENT_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT_BONUS) $(LIBFT) $(INCLUDES) -o $(NAME_CLIENT_BONUS)

# --- Compilation rules ---
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Limpeza
clean:
	@make clean -C $(LIBFT_DIR)
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_SERVER_BONUS) $(OBJS_CLIENT_BONUS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME_SERVER) $(NAME_CLIENT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
