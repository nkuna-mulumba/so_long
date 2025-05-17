/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 00:49:39 by jcongolo          #+#    #+#             */
/*   Updated: 2025/05/17 17:43:30 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * ft_load_sprite_files - Define caminhos dos arquivos de sprites do jogo
 	Sera chamada dentro de `ft_load_sprites()` para garantir que os
	arquivos sejam corretamente organizados e carregados.
 * @param sprit_files: Array de strings onde caminhos dos sprites serão
 	armazenados.
*/
static void	ft_load_sprite_files(char *sprit_files[])
{
	sprit_files[0] = "assets/collectible.xpm";
	sprit_files[1] = "assets/exit.xpm";
	sprit_files[2] = "assets/player.xpm";
	sprit_files[3] = "assets/wall.xpm";
}

/*
 * ft_load_sprites - Carrega os sprites do jogo na estrutura `game`. 
 * Função inicializa os sprites a partir dos arquivos XPM fornecidos
	em `ft_load_sprite_files()`, garantindo que cada imagem seja
	corretamente carregada, armazenada na estrutura `game->sprites`.
 * Se ocorrer um erro ao carregar qualquer sprite, execução do
 	jogo é interrompida.
 * @param game: Estrutura principal do jogo onde sprites serão armazenados
*/
void	ft_load_sprites(t_game *game)
{
	int		total_sprites;
	int		i;
	int		sprite_width;
	int		sprite_height;
	char	*sprit_files[4];

    // Chama a função que inicializa a lista de arquivos dos sprites
	ft_load_sprite_files(sprit_files);

    // Inicializa variáveis antes de atribuir valores
	total_sprites = sizeof(sprit_files) / sizeof(sprit_files[0]);
	i = -1;
	sprite_width = 0;
	sprite_height = 0;
	game->sprites_loaded = 0;

    printf("DEBUG: sprite_width = %d, sprite_height = %d antes da carga\n", sprite_width, sprite_height);

    // Se os sprites já foram carregados, evitar carregamento repetitivo
	if (game->sprites_loaded == total_sprites)
		return ;

    // Carregar sprites dinamicamente com base no array
	while (++i < total_sprites)
	{
		game->sprites[i] = mlx_xpm_file_to_image(game->mlx, sprit_files[i],
				&sprite_width, &sprite_height);
		if (!game->sprites[i])
		{
			write(2, "Error: Failed to load sprite\n", 30);
			exit(EXIT_FAILURE);
		}

        printf("DEBUG: Sprite carregado [%d]: %s\n", i, sprit_files[i]);
		game->sprites_loaded++;// Atualizar quantidade de sprites carregados
	}

    printf("DEBUG: Total de sprites carregados: %d\n", game->sprites_loaded);
}

/*
 * ft_draw_tile - Exibe único bloco do mapa na posição (x, y).
 
 * A função identifica qual elemento está presente na posição indicada
	e desenha a imagem correspondente na janela.

 * @param game: Ponteiro para a estrutura principal do jogo (t_game).
 * @param x: Posição horizontal do bloco no mapa.
 * @param y: Posição vertical do bloco no mapa.
*/
static void	ft_draw_tile(t_game *game, int x, int y)
{
	void	*img;
	int		pos_x;
	int		pos_y;

	//Identificar sprites correspondam no mapa
	img = NULL;
	pos_x = x * TILE_SIZE;
	pos_y = y * TILE_SIZE;
	if (game->map[y][x] == '1')
		img = game->sprites[3];//Paredes
	else if (game->map[y][x] == 'C')
		img = game->sprites[0];//Colecionáveis
	else if (game->map[y][x] == 'E')
		img = game->sprites[1];//Saída
	else if (game->map[y][x] == 'P')
		img = game->sprites[2];//Jogador

	//Colocar imagem na janela
	if (img)
		mlx_put_image_to_window(game->mlx, game->win, img, pos_x, pos_y);
}

/*
 * ft_render_map - Percorre o mapa e desenha cada elemento na janela.
 *
 * A função percorre todas as células do mapa e chama ft_draw_tile para 
 * desenhar cada bloco correspondente.
 *
 * @param game: Ponteiro para a estrutura principal do jogo (t_game),
 *              contendo o mapa e as imagens carregadas.
*/
void	ft_render_map(t_game *game)
{
	int y;
	int x;

	//Limpa janela antes de desenhar
	mlx_clear_window(game->mlx, game->win);

	//Percorre todas células do mapa
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			ft_draw_tile(game, x, y);//Exibe bloco da posição (x, y)
			x++;
		}
		y++;
	}
}

/*
	*
	*
	* 
*/
