/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:53:33 by jcongolo          #+#    #+#             */
/*   Updated: 2025/04/07 13:17:41 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"   //Biblioteca lbft

# define TILE_SIZE 64 // Tamanho dos sprites (em pixels)
# define KEY_ESC 53   // ESC: encerrar jogo
# define KEY_W 13     // W: movimento para cima
# define KEY_A 0      // A: movimento para esquerda
# define KEY_S 1      // S: movimento para baixo
# define KEY_D 2      // D: movimento para  direita

typedef struct s_game
{
	void	*mlx; //Ponteiro para gerenciar o MiniLibX
	void	*win; //Ponteiro para a janela do jogo
	char	**map; //Mapa do jogo representado por uma matriz de caracteres
	int		map_width; //Largura do mapa (numero de tiles)
	int		map_height; //Altura do mapa (numero de tiles)
	int		player_x; //Posiçao X do jogador no mapa
	int		player_y; //Posiçao Y do jogador no mapa
	int		collectibles; //Total de objectos colecionaveis no mapa
	int		moves; //Contador de movimentos realizados pelo jogador
	int		exit_x; //Corrdenada X da saida no mapa 
	int		exit_y; //Corredenada Y da saida no mapa
}			t_game;

// Validar Map
int			ft_validate_map(char *file, t_game *game);
#endif
