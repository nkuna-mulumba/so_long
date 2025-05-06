/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 00:49:39 by jcongolo          #+#    #+#             */
/*   Updated: 2025/05/06 16:28:50 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/*
 * ft_load_sprites - Carrega sprites do jogo e armazena na estrutura game
 
 * Elementos visuais são carregados apenas uma vez para 
    otimizar a execução
 * @param game: Ponteiro para a estrutura principal do jogo (t_game),
               onde as imagens serão armazenadas.
 */
void    ft_load_sprites(t_game *game)
{
    int sprite_width;  //Para armazenar largura da imagen carregada
    int sprite_height; //Para armazenar altura da imagem cerregada
    int i;
    
    //Array com caminhos dos arquivos de imagens dos sprites do jogo
    char  *sprit_files[] =
    {
        "assets/collectible.xpm",
        "assets/exit.xpm",
        "assets/player.xpm",
        "assets/wall.xpm"
    };
    
    //Evitar carregamento desnecessário
    game->sprites_loaded = 0;
    if (game->sprites_loaded == 1)
        return;
    
    // Carregar as imagens usando while
    i = 0;
    while (i < 4)
    {
        game->sprites[i] = mlx_xpm_file_to_image(game->mlx, sprit_files[i], &sprite_width, &sprite_height);
        //Verificar se houve erro ao carregar alguma imagem
        if (!game->sprites[i])
        {
            write(2, "Error: Failed to load sprite\n", 30);
            exit(EXIT_FAILURE);
        }
        i++;
    }
    
    //Marcar que os sprites foram carregados
    game->sprites_loaded = 1;
}

/*
 * ft_draw_tile - Exibe único bloco do mapa na posição (x, y).
 
 * A função identifica qual elemento está presente na posição indicada
    e desenha a imagem correspondente na janela.

 * @param game: Ponteiro para a estrutura principal do jogo (t_game).
 * @param x: Posição horizontal do bloco no mapa.
 * @param y: Posição vertical do bloco no mapa.
 */
static void ft_draw_tile(t_game *game, int x, int y)
{
    void    *img;
    int     pos_x;
    int     pos_y;

    //Identificar sprites correspondam no mapa
    img = NULL;
    pos_x = x * TILE_SIZE;
    pos_y = y * TILE_SIZE;
    if (game->map[y][x] == '1')
        img = game->sprites[3]; // Paredes
    else if (game->map[y][x] == 'C')
        img = game->sprites[0]; // Colecionáveis
    else if (game->map[y][x] == 'E')
        img = game->sprites[1]; // Saída
    else if (game->map[y][x] == 'P')
        img = game->sprites[2]; // Jogador

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
void    ft_render_map(t_game *game)
{
    int y;
    int x;

    //Limpa a janela antes de desenhar
    mlx_clear_window(game->mlx, game->win);

    // Percorre todas as células do mapa
    y = 0;
    while (y < game->map_height)
    {
        x = 0;
        while (x < game->map_width)
        {
            ft_draw_tile(game, x, y);// Exibe o bloco da posição (x, y)
            x++;
        }
        y++;
    }
}
