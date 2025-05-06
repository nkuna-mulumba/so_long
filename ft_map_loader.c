/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:32:06 by jcongolo          #+#    #+#             */
/*   Updated: 2025/05/06 16:19:39 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * ft_open_map_file - Abre arquivo do mapa, retorna descritor de arquivo
 * @filename: Nome do arquivo do mapa
 * Retorno: O descritor do arquivo se bem-sucedido, ou -1 em caso de erro.
 */
static int  ft_open_map_file(const char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        write(2, "Error: Invalid map file.\n", 26);
        return(-1);   
    }
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
    return (map);
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
    int     len;
    size_t  j;

    // Lê e armazenar cada linha do mapa
    i = 0;
    while ((line = ft_get_next_line(fd)) != NULL)
    {        
        len = ft_strlen(line);
        if (line[len - 1] == '\n')//Removendo o '\n' caso ele esteja presente
            line[len - 1] = '\0';

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

        if (i == 0)
            game->map_width = ft_strlen(game->map[i]);//Define largura baseada na linha sem '\n'

        i++;
    }
    game->map[i] = NULL;
    return (1);
}

/*
 * ft_read_map - Coordena leitura do arquivo e processamento das linhas do mapa
 * @game: Estrutura principal do jogo.
 * @filename: Nome do arquivo do mapa.
 * Retorno: 1 se bem-sucedido, ou 0 em caso de falha.
 */
int ft_read_map(t_game *game, const char *filename)
{
    int fd;

    // Inicializa a contagem de colecionáveis (`C`) presentes no mapa
    game->collectibles = 0;

    // Abre o arquivo do mapa e obtém seu descritor (`fd`)
    fd = ft_open_map_file(filename);
    if (fd < 0)
        return (0);

    // Aloca memória para armazenar a matriz do mapa
    game->map = ft_allocate_map_memory();
    if (!game->map)
    {
        close(fd);
        return (0);
    }

    // Processa e lê as linhas do mapa, armazenando os dados
    if (!ft_process_map_lines(fd, game))
    {
        close(fd);
        return (0);
    }

    // Define a altura do mapa (`map_height`) contando o número de linhas lidas
    game->map_height = 0;
    while (game->map[game->map_height])
        game->map_height++;

    // Fecha o arquivo após a leitura completa
    close(fd);
    return (1);
}

/*
    obs:
    diminuir as linhas em (ft_process_map_lines)
*/