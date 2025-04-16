#Nome do executavel
NAME = so_long

#Arquivos fontes para parte obrigatorio
SRCS = ft_map_memory.c\
	ft_map_content.c\
    ft_flood_validation.c\
	ft_map_validation.c\
    ft_game_init.c\
	main.c

OBJS = $(SRCS:.c=.o)

#Compilador e flags
CC = cc
FLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm -lbsd

#Diretorios
MINILIBX_DIR = minilibx-linux
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

#Regras para compilar o executavel
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

#Regras para compilar LIBFT
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Limpeza dos arquivos objetos
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

# Limpeza total
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Regra para recompilar tudo
re: fclean all