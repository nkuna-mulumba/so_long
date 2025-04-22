# Nome do executável
NAME = so_long

# Arquivos fontes
SRCS = ft_game_init.c\
	main.c

OBJS = $(SRCS:.c=.o)

# Compilador e flags
CC = cc
FLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm -lbsd

# Diretórios
MINILIBX_DIR = mnlbx
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Regra para compilar objetos
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

# Regras para compilar o executável
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) mnlbx
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

# Regra para compilar MiniLibX automaticamente
mnlbx: $(MINILIBX_DIR)/libmlx.a

$(MINILIBX_DIR)/libmlx.a:
	$(MAKE) -C $(MINILIBX_DIR)

# Regras para compilar LIBFT
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Limpeza dos arquivos objetos e MiniLibX
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MINILIBX_DIR) clean

# Limpeza total (objetos e bibliotecas)
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MINILIBX_DIR) clean
	rm -f $(MINILIBX_DIR)/libmlx.a $(MINILIBX_DIR)/libmlx_Linux.a

# Regra para recompilar tudo
re: fclean all
