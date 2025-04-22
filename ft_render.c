/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 00:49:39 by jcongolo          #+#    #+#             */
/*   Updated: 2025/04/23 00:51:53 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/*
 * ft_load_sprites - Carrega os sprites do jogo e armazena na estrutura game.
 *
 * Os elementos visuais são carregados apenas uma vez para otimizar a execução
 * e evitar múltiplas chamadas desnecessárias.
 *
 * @param game: Ponteiro para a estrutura principal do jogo (t_game),
 *              onde as imagens serão armazenadas.
 */
static void ft_load_sprites(t_game *game)
{
    
}



/*
 * ft_draw_tile - Renderiza um único bloco do mapa na posição (x, y).
 *
 * A função identifica qual elemento está presente na posição indicada
 * e desenha a imagem correspondente na janela.
 *
 * @param game: Ponteiro para a estrutura principal do jogo (t_game).
 * @param x: Posição horizontal do bloco no mapa.
 * @param y: Posição vertical do bloco no mapa.
 */
static void ft_draw_tile(t_game *game, int x, int y)
{
    
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
void ft_render_map(t_game *game)
{
    
}