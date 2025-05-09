/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:32:06 by jcongolo          #+#    #+#             */
/*   Updated: 2025/05/09 16:00:21 by jcongolo         ###   ########.fr       */
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
    
    map = malloc(sizeof(char *) * 100);//Ajuste conforme necessário
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
            write(2, "Error: Failed to copy map line.\n", 33);
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
 */
/*
    1️⃣ ft_read_map_line(line)OK
    2️⃣ ft_check_map_elements(game, i) substituída por ft_count_map_elements(game, &p, &e, &c).
    3️⃣ ft_define_map_width(game, i)OK
    4️⃣ ft_process_map_lines(fd, game)OK
*/


/*
 * ft_read_map_line - Processa e remove '\n' da linha do mapa antes de armazená-la.
 * @line: Linha lida do arquivo do mapa.
 * Retorno:
 * - Uma cópia da linha sem '\n', pronta para ser armazenada no mapa.
*/
static char *ft_read_map_line(char *line)
{
    int len = ft_strlen(line);
    if (line[len - 1] == '\n')  // Remove o '\n' caso esteja presente
        line[len - 1] = '\0';
    return ft_strdup(line);
}

/*
 * ft_define_map_width - Define a largura do mapa com base na primeira linha lida.
 * @game: Estrutura principal do jogo.
 * @i: Índice da linha sendo processada.
*/
// static void ft_define_map_width(t_game *game, int i)
// {
//     if (i == 0)  // Define a largura na primeira linha
//         game->map_width = ft_strlen(game->map[i]);
// }
static void ft_define_map_width(t_game *game, int i)
{
    if (i == 0)
    {
        game->map_width = ft_strlen(game->map[i]);
        printf("DEBUG: Definição da largura do mapa - game->map_width = %d\n", game->map_width);
    }
}


/*
 * ft_process_map_lines - Lê e processa as linhas do mapa.
 * @fd: Descritor do arquivo do mapa.
 * @game: Estrutura do jogo que armazenará os dados do mapa.
 * Retorno: 1 se bem-sucedido, ou 0 em caso de erro.
static int ft_process_map_lines(int fd, t_game *game)
{
    int i = 0;
    char *line;

    while ((line = ft_get_next_line(fd)) != NULL)
    {
        game->map[i] = ft_read_map_line(line);  // Processa a linha
        free(line);
        if (!game->map[i])
        {
            write(2, "Error: Failed to copy map line.\n", 33);
            return (0);
        }

        ft_define_map_width(game, i);  // Define a largura do mapa
        i++;
    }
    game->map[i] = NULL;

    // **Chamando a validação de caracteres**
    if (!ft_validate_map_characters(game))
    {
        write(2, "Error: Invalid characters in map file\n", 38);
        return (0);
    }

    // **Chamando a contagem de elementos**
    int p;
    int e;
    int c;
    ft_count_map_elements(game, &p, &e, &c);
    game->collectibles = c;

    // **Verificando se existe exatamente 1 jogador**
    if (p != 1)
    {
        write(2, "Error: Need exactly 1 'P'\n", 27);
        return (0);
    }

    return (1);
}
*/
static int ft_process_map_lines(int fd, t_game *game)
{
    int i = 0;
    char *line;

    printf("DEBUG: Iniciando leitura do mapa...\n");

    while ((line = ft_get_next_line(fd)) != NULL)
    {
        printf("DEBUG: Linha lida [%d]: %s\n", i, line);
        game->map[i] = ft_read_map_line(line);
        free(line);

        if (!game->map[i])
        {
            write(2, "Error: Failed to copy map line.\n", 33);
            return (0);
        }

        ft_define_map_width(game, i);
        i++;
    }
    game->map[i] = NULL;

    // **Definir a altura do mapa após a leitura**
    game->map_height = i;
    printf("DEBUG: game->map_height atualizado = %d\n", game->map_height);

    printf("DEBUG: Leitura do mapa concluída!\n");
    printf("DEBUG: Total de linhas lidas (game->map_height): %d\n", i);

    // **Chamando a validação de caracteres**
    printf("DEBUG: Validando caracteres do mapa...\n");
    if (!ft_validate_map_characters(game))
    {
        write(2, "Error: Invalid characters in map file\n", 38);
        return (0);
    }
    printf("DEBUG: Validação de caracteres concluída!\n");

    // **Chamando a contagem de elementos**
    int p, e, c;

    // **Mensagens de depuração para verificar game->map_height e game->map_width**
    printf("DEBUG: Verificando game->map_height antes da contagem - %d\n", game->map_height);
    printf("DEBUG: Verificando game->map_width antes da contagem - %d\n", game->map_width);

    printf("DEBUG: Contando elementos do mapa...\n");
    ft_count_map_elements(game, &p, &e, &c);
    game->collectibles = c;

    printf("DEBUG: Contagem concluída - P: %d | E: %d | C: %d\n", p, e, c);

    // **Verificando se existe exatamente 1 jogador**
    if (p != 1)
    {
        write(2, "Error: Need exactly 1 'P'\n", 27);
        return (0);
    }
    printf("DEBUG: Validação do jogador concluída - Total P: %d\n", p);

    return (1);
}




/*
 * ft_read_map - Coordena leitura do arquivo e processamento das linhas do mapa
 * @game: Estrutura principal do jogo.
 * @filename: Nome do arquivo do mapa.
 * Retorno: 1 se bem-sucedido, ou 0 em caso de falha.

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
 */
int ft_read_map(t_game *game, const char *filename)
{
    int fd;
    game->collectibles = 0;

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

    game->map_height = 0;
    while (game->map[game->map_height])
        game->map_height++;

    printf("DEBUG: Definição da altura do mapa - game->map_height = %d\n", game->map_height);

    close(fd);
    return (1);
}




/*
    obs:
    diminuir as linhas em (ft_process_map_lines)
*/