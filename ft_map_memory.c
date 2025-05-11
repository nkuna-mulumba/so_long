/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:49:13 by jcongolo          #+#    #+#             */
/*   Updated: 2025/05/12 01:20:50 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Funçao que libera memória alocada para mapa
 * @map: Ponteiro para o array bidimensional (matriz) que contém mapa.
 * @line_count: Número de linhas atualmente alocadas no mapa.
 
 * Esta função percorre todas as linhas do array 'map', liberando
 * cada uma delas individualmente, e em seguida libera o próprio 
 * array 'map'. Isso garante que toda a memória alocada dinamicamente
 * para o mapa seja corretamente liberada, evitando vazamentos de memória.
*/
void	ft_free_map(char **map, int line_count)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

/*
 * ft_allocate_map_memory - Aloca memória para armazenar o mapa.
 * Retorno: Ponteiro para o array do mapa ou NULL em caso de falha.
*/
char **ft_allocate_map_memory(int map_height)
{
    char **map;

    if (map_height <= 0)
    {
        write(2, "Error: Invalid map height.\n", 27);
        return (NULL);
    }

    // Aloca memória baseada no número de linhas do mapa
    map = malloc(sizeof(char *) * (map_height + 1)); // +1 para a linha NULL no final
    if (!map)
    {
        write(2, "Error: Failed to allocate memory.\n", 35);
        return (NULL);
    }

    return (map);
}

/*
 * ft_free_sprites - Libera memória alocada para os sprites do jogo.
 
 * Função percorre todos sprites carregados e libera memória
 	usando `mlx_destroy_image()`, evitando vazamentos
	
 * @param game: Ponteiro para a estrutura principal do jogo (t_game).
 */
static	void	ft_free_sprites(t_game *game)
{
    int i = 0;
    while (i < 4) // Assumindo 4 sprites carregados
    {
        if (game->sprites[i])
            mlx_destroy_image(game->mlx, game->sprites[i]); // Libera cada sprite individualmente
        i++;
    }
}

/*
 * ft_close_game - Encerra o jogo, liberando memória e fechando a janela.
 
 * Esta função libera os recursos usados pelo jogo, como mapa e sprites,
 	e fecha a janela gráfica caso esteja utilizando MiniLibX.

 * @param game: Ponteiro para a estrutura principal do jogo (t_game).
 */
void	ft_close_game(t_game *game)
{
	// Libera sprites carregados antes de fechar janela
    ft_free_sprites(game);
	
	// Libera memória do mapa
	if (game->map)
    {
		ft_free_map(game->map, game->map_height);
	}

    // Libera recursos gráficos (se houver)
    if (game->mlx && game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
	}

    // Finaliza o programa corretamente
    exit(0);
}

/*
 * ft_handle_close - Captura evento de fechamento da janela e encerra o jogo.
 
 * Esta função é acionada quando usuário clica botão [X] no canto superior
 	direito da janela. Chama ft_close_game() para garantir que todos os 
 	recursos do jogo sejam corretamente liberados antes de encerrar a execução
	
 * @param game: Ponteiro para a estrutura principal do jogo (t_game)
 * @return (0): Retorna 0 para indicar encerramento bem-sucedido
 */
int	ft_handle_close(t_game *game)
{
    ft_close_game(game);
    return (0);
}


/*
    Obs:
    A funçao (ft_free_sprites) nao pode assumir quantidade de sprites
	carregadas sem colocar (4)?
*/
