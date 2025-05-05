/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:32:06 by jcongolo          #+#    #+#             */
/*   Updated: 2025/05/05 18:08:26 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * ft_open_map_file - Abre o arquivo do mapa e retorna o descritor de arquivo.
 * @filename: Nome do arquivo do mapa.
 * Retorno: O descritor do arquivo se bem-sucedido, ou -1 em caso de erro.
 */
static int  ft_open_map_file(const char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        write(2, "Error: Invalid map file.\n", 26);
    return (fd);
}

/*
 * ft_allocate_map_memory - Aloca memória para armazenar o mapa.
 * Retorno: Ponteiro para o array do mapa ou NULL em caso de falha.
 */
static char **ft_allocate_map_memory(void)
{
    char    **map;
    
    map = malloc(sizeof(char *) * 100); // Ajuste conforme necessário
    if (!map)
        write(2, "Error: Failed to allocate memory.\n", 35);
    return map;
}

/*
 * ft_process_map_lines - Lê e processa linhas do mapa,
    identificando jogador e colecionáveis.
 * @fd: Descritor do arquivo do mapa.
 * @game: Estrutura do jogo que armazenará os dados do mapa.
 * Retorno: 1 se bem-sucedido, ou 0 em caso de erro.
 */
static int  ft_process_map_lines(int fd, t_game *game)
{
    int     i;
    char    *line;
    size_t  j;

    // Lê e armazena cada linha do mapa
    i = 0;
    while ((line = ft_get_next_line(fd)) != NULL)
    {
        game->map[i] = ft_strdup(line);
        free(line);
        if (!game->map[i])
        {
            write(2, "Error: Failed to copy map line.\n", 32);
            return (0);
        }

        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] == 'P')
            {
                game->player_x = j;
                game->player_y = i;
            }
            else if (game->map[i][j] == 'C')
                game->collectibles++;
            j++;
        }
        i++;
    }
    game->map[i] = NULL;
    return (1);
}

/*
 * ft_read_map - Coordena a leitura do arquivo e o processamento das linhas do mapa
 * @game: Estrutura principal do jogo.
 * @filename: Nome do arquivo do mapa.
 * Retorno: 1 se bem-sucedido, ou 0 em caso de falha.
 */
int ft_read_map(t_game *game, const char *filename)
{
    int fd;
    
    fd = ft_open_map_file(filename);
    if (fd < 0)
        return (0);

    game->map = ft_allocate_map_memory();
    if (!game->map)
    {
        close(fd);
        return (0);
    }

    if (!ft_process_map_lines(fd, game))
    {
        close(fd);
        return (0);
    }

    close(fd);
    return (1);
}
