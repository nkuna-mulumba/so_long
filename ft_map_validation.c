/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:33:07 by jcongolo          #+#    #+#             */
/*   Updated: 2025/04/07 14:17:05 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Esta funçao valida o mapa do jogo carregado a partir de um arquivo.
 * @file: Caminho para o arquivo do mapa (formato .ber).
 * @game: Estrutura principal que contém dados do jogo, como o mapa.
 * 
 * A função lê o mapa linha por linha, armazena-o na matriz 'map' dentro da
 * estrutura 'game', e valida se o mapa segue os requisitos básicos:
 * - Está cercado por paredes ('1').
 * - Contém os elementos obrigatórios (P, E, C).
 * - Possui um caminho válido entre o jogador, os colecionáveis e a saída.
 * 
 * Retorna 1 se o mapa for válido, ou 0 se houver algum erro.
 */
int	ft_validate_map(char *file, t_game *game)
{
	int     fd;
	char    *line;
	int     line_count;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		write(1, "Error: Could not open map file.\n", 33);
        return (0);
	}
	line_count = 0;
	game->map = NULL;

	// Ler o mapa linha por linha
	while ((line = ft_get_next_line(fd)) != NULL)
	{
		game->map = ft_realloc(game->map, (line_count + 1) * sizeof(char *));
		game->map[line_count++] = line;
	}
	close(fd);
    
	game->map_height = line_count;
	game->map_width = ft_strlen(game->map[0]) - 1; // Remover '\n'

	// Verificar paredes, conteudo e caminho valido
	if (!check_map_walls(game))
	{
		write(1, "Error: Map must be surrounded by walls.\n", 41);
		return (0);
	}
	if (!check_map_content(game))
	{
		write(1, "Error: Invalid map content.\n", 29);
		return (0);
	}
	if (!flood_fill_check(game))
	{
		write(1, "Error: No valid path in the map.\n", 34);
		return (0);
	}
	return (1); // Mapa valido
}
