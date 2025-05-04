/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:33:07 by jcongolo          #+#    #+#             */
/*   Updated: 2025/05/04 23:29:30 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/*
 * ft_read_map - Lê o arquivo e armazena o conteúdo no array 'map'.
 * @file: Caminho para o arquivo do mapa.
 * @game: Estrutura principal que contém dados do mapa.
 * Retorna 1 se bem-sucedido, ou 0 em caso de falha.
 */
static int ft_read_map(t_game *game, const char *filename)
{
    int fd, i = 0, len;
    char *line;

    // Inicializa contador de colecionáveis
    game->collectibles = 0;

    // Abre arquivo do mapa
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (0);

    // Aloca memória para armazenar o mapa
    game->map = malloc(sizeof(char *) * 100); // Ajuste conforme necessário
    if (!game->map)
    {
        close(fd);
        return (0);
    }

    // Lê e armazena cada linha do mapa
    while ((line = ft_get_next_line(fd)) != NULL)
    {
        len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        game->map[i] = strdup(line);
        free(line);
        if (!game->map[i])
        {
            close(fd);
            return (0);
        }

        // Identifica posição do jogador (`P`) e conta colecionáveis (`C`)
        for (size_t j = 0; j < ft_strlen(game->map[i]); j++)
        {
            if (game->map[i][j] == 'P')
            {
                game->player_x = j;
                game->player_y = i;
            }
            else if (game->map[i][j] == 'C')
                game->collectibles++;
        }
        i++;
    }

    // Finaliza estrutura do mapa e fecha o arquivo
    game->map[i] = NULL;
    close(fd);

    return (1);
}


/*
 * ft_check_map_dimensions - Calcula e valida dimensões do mapa
 * @game: Estrutura principal que contém o mapa
 * Retorna 1 se todas linhas tiverem mesmo comprimento, ou 0 caso contrário
 */
static int  ft_check_map_dimensions(t_game *game)
{
    int i;

    // Verificar se o mapa está corretamente carregado antes de usar
    if (!game->map || !game->map[0])
    {
        printf("Erro: Mapa corrompido ou não carregado corretamente!\n");
        return (0);
    }

    // Depuração: Verificar o primeiro elemento do mapa
    printf("Debug: Primeiro elemento do mapa -> [%s]\n", game->map[0]);

    // Obter tamanho da primeira linha
    game->map_width = ft_strlen(game->map[0]);
    printf("Dimensão inicial do mapa -> largura: %d\n", game->map_width);

    // Depuração: Verificar `game->map` antes de calcular altura
    printf("Depuração: Verificando estado do mapa antes de calcular altura...\n");
    i = 0;
    while (game->map[i])
    {
        printf("Linha %d -> [%s] (endereço: %p)\n", i, game->map[i], (void*)game->map[i]);
        if (!game->map[i])
        {
            printf("Erro: Ponteiro inesperado NULL encontrado antes da verificação de altura!\n");
            return (0);
        }
        i++;
    }

    // Calcular altura do mapa usando `while`
    game->map_height = 0;
    while (game->map[game->map_height])
    {
        printf("Depuração: Verificando `game->map[%d]` -> [%p]\n", game->map_height, game->map[game->map_height]);
        game->map_height++;
    }

    // Ajuste final para evitar acesso fora dos limites
    if (game->map_height > 0 && game->map[game->map_height] != NULL)
    {
        printf("Correção: Última posição do mapa não é NULL como esperado, ajustando altura...\n");
        game->map_height--;
    }

    printf("Altura do mapa calculada: %d\n", game->map_height);

    // Depuração: Verificar todas as linhas do mapa antes de validar
    i = 0;
    while (i < game->map_height)
    {
        printf("Depuração: Conferindo linha %d antes da validação -> [%s]\n", i, game->map[i]);

        if (!game->map[i])
        {
            printf("Erro: Linha %d do mapa está NULL inesperadamente!\n", i);
            return (0);
        }

        printf("Linha %d -> tamanho esperado: %d, tamanho real: %ld\n",
            i, game->map_width, ft_strlen(game->map[i]));

        // Comparar o tamanho da linha atual com o da primeira linha
        if ((int)ft_strlen(game->map[i]) != game->map_width)
        {
            write(1, "Error: Map rows must have the same width.\n", 42);
            return (0);
        }
        i++;
    }

    printf("Dimensões finais do mapa -> largura: [%d], altura: [%d]\n",
        game->map_width, game->map_height);

    return (1);
}



/*
 * ft_check_map_walls - Verifica se o mapa está cercado por paredes (1).
 * Esta função analisa as bordas do mapa, garantindo que:
 	- A primeira e a última linha sejam compostas apenas por '1'.
 	- A primeira e a última coluna de cada linha também sejam '1'.
 * @game: Estrutura principal que contém os dados do mapa, incluindo o array 
 	bidimensional, linhas (`map_height`) e o colunas (`map_width`).
 * Retorna:
 	- 1, se o mapa estiver corretamente cercado por paredes.
 	- 0, caso contrário, indicando um erro na formação das bordas.
*/
int	ft_check_map_walls(t_game *game)
{
	int	i;
	
	// Verificar a primeira linha e ultima
	i = 0;
	while (i < game->map_width)
	{
		//Verificar primeira linha de matriz .ber
		if (game->map[0][i] != '1') //Primeira Linha
		{
			return (0);
		}
		//Verificar ultima linha de matriz .ber
		if (game->map[game->map_height - 1][i] != '1')
		{
			return (0);
		}
		i++;
	}
	//Verificar primeira coluna e utimo
	i = 0;
	while (i < game->map_height)
	{
		//Verificar primeira coluna de matriz .ber)
		if (game->map[i][0] != '1')
		{
			return (0);
		}
		//Verificar ultima de matriz .ber
		if (game->map[i][game->map_width - 1] != '1')
		{
			return (0);
		}
		i++;
	}
	return(1);
}

/*
 * ft_validate_map - Coordena todas as validações do mapa do jogo.
 * Responsabilidades:
 	- Chama ft_read_map para ler mapa a partir do arquivo fornecido.
 	- Chama ft_check_map_dimensions para verificar se todas linhas têm mesmo comprimento
 	- Chama ft_check_map_walls para garantir que mapa esteja cercado por paredes ('1')
 	- Chama ft_check_map_content para validar caracteres do mapa e elementos obrigatórios
	  ('P', 'E', 'C').
 	- Chama ft_flood_fill_check para verificar se há conectividade entre o jogador,
	  os colecionáveis e a saída.
 * @file: Caminho para o arquivo do mapa (.ber).
 * @game: Estrutura principal que contém os dados do jogo, incluindo o mapa.
 * Retorna:
 	- 1, se o mapa for válido e atender a todos os critérios obrigatórios.
 	- 0, caso contrário, indicando erro na validação.
 */
int	ft_validate_map(char *file, t_game *game)
{
	printf("2->Abrindo arquivo %s...\n", file);//Depuraçao
	if (!ft_read_map(game, file))
	if (!ft_read_map(game, file))// Validar a leitura do mapa a partir do arquivo
	{
		return (0);
	}
	if (!ft_check_map_dimensions(game))// Validar dimensões do mapa
	{
		ft_free_map(game->map, game->map_height);
		return (0);
	}
	if (!ft_check_map_walls(game))// Validar paredes do mapa
	{
		ft_free_map(game->map, game->map_height);
		return (0);
	}
	if (!ft_check_map_content(game))// Validar conteúdo do mapa (P, E, C)
	{
		ft_free_map(game->map, game->map_height);
		return (0);
	}
	if (!ft_flood_fill_check(game))// Validar conectividade do mapa
	{
		write(1, "Error: No valid path in the map.\n", 34);
        ft_free_map(game->map, game->map_height);
        return (0);
	}
	return (1);
}

