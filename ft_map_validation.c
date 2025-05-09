/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:33:07 by jcongolo          #+#    #+#             */
/*   Updated: 2025/05/09 16:06:22 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * ft_check_map_dimensions - Calcula e valida dimensões do mapa
 * @game: Estrutura principal que contém o mapa
 * Retorna 1 se todas linhas tiverem mesmo comprimento, ou 0 caso contrário
 */
static int	ft_check_map_dimensions(t_game *game)
{
    int	i;

    //Verificar se mapa está corretamente carregado antes de usar
    if (!game->map || !game->map[0])
    {
        write(2, "Error: Invalid or corrupted map.\n", 34);
        return (0);
    }

    //Obter tamanho da primeira linha
    game->map_width = ft_strlen(game->map[0]);

    //Calcular altura do mapa usando
    game->map_height = 0;
    while (game->map[game->map_height])
        game->map_height++;

    //Ajuste final para evitar acesso fora dos limites
    if (game->map_height > 0 && game->map[game->map_height] != NULL)
        game->map_height--;
 
    //Verificar todas linhas do mapa antes de validar
    i = 0;
    while (i < game->map_height)
    {
        if (!game->map[i])
        {
            write(2, "Error: Unexpected NULL row in map.\n", 36);
            return (0);
        }

        //Comparar tamanho da linha atual com o da primeira linha
        if ((int)ft_strlen(game->map[i]) != game->map_width)
        {
            write(2, "Error: Map rows must have the same width.\n", 43);
            return (0);
        }
        i++;
    }
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
int ft_check_map_walls(t_game *game)
{
    int i;

	//Verificar primeira e ultima linha de matriz .ber
    i = 0;
    while (i < game->map_width)
    {
        if (game->map[0][i] != '1')
            return (0);
        if (game->map[game->map_height - 1][i] != '1')
            return (0);
        i++;
    }

    //Verificar primeira e última coluna da matriz .ber
    i = 0;
    while (i < game->map_height)
    {
        if (game->map[i][0] != '1')
            return (0);
        if (game->map[i][game->map_width - 1] != '1')
            return (0);
        i++;
    }
    return (1);
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
int ft_validate_map(char *file, t_game *game)
{
	if (!ft_read_map(game, file))// Validar a leitura do mapa a partir do arquivo
		return (0);
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
		write(2, "Error: No valid path in the map.\n", 34);
        ft_free_map(game->map, game->map_height);
        return (0);
	}
	return (1);
}
