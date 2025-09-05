# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                                              #
# **************************************************************************** #

# ---------------------- Config ----------------------
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes

# ---------------------- Libft ----------------------
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# ---------------------- Sources ----------------------
SRCS_SERVER = server.c utils.c
SRCS_CLIENT = client.c utils.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

# ---------------------- Targets ----------------------
NAME_SERVER = server
NAME_CLIENT = client

# ---------------------- Rules ----------------------
all: $(LIBFT) $(NAME_SERVER) $(NAME_CLIENT)

# Compila a libft
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Server
$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBFT) $(INCLUDES) -o $(NAME_SERVER)

# Client
$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBFT) $(INCLUDES) -o $(NAME_CLIENT)

# Regra genérica para compilar .o
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Limpar objetos
clean:
	@make clean -C $(LIBFT_DIR)
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)

# Limpar objetos + binários
fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME_SERVER) $(NAME_CLIENT)

# Recompilar tudo do zero
re: fclean all

.PHONY: all clean fclean re
