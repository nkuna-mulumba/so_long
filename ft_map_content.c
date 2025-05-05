/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:22:38 by jcongolo          #+#    #+#             */
/*   Updated: 2025/05/05 13:49:29 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * ft_validate_map_characters - Verifica se todos caracteres do mapa são válidos
 * Percorre mapa e verifica se cada célula contém um dos caracteres permitidos:
 	- 'P' (jogador)
 	- 'E' (saída)
 	- 'C' (colecionável)
 	- '0' (espaço vazio)
 	- '1' (parede)
 * @game: Estrutura principal que contém dados do mapa, incluindo array bidimensional,
          número de linhas (map_height), número de colunas (map_width).
 * Retorna:
 * - 1, se todos os caracteres do mapa forem válidos.
 * - 0, se houver algum caractere inválido no mapa, e imprime uma mensagem de erro.
*/
static int	ft_validate_map_characters(t_game *game)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			// Verifica se o caractere atual é inválido
			if (game->map[i][j] != 'P' && game->map[i][j] != 'E' &&
				game->map[i][j] != 'C' && game->map[i][j] != '0' &&
				game->map[i][j] != '1')
			{
				write(1, "Error: Invalid character\n", 26);
				return (0);
			}
			j++;
		}
		i++;
	}
	return(1);// Todos os caracteres são válidos
}

/*
 * ft_count_map_elements - Conta os elementos obrigatórios no mapa.
 * A função percorre mapa, conta quantidade de jogadores ('P'), saídas ('E') 
   e colecionáveis ('C'), armazenando os resultados nos ponteiros fornecidos.
 * @game: Estrutura principal, contendo dados do mapa, incluindo array bidimensional,
 		  o número de linhas (`map_height`) e o número de colunas (`map_width`).
 * @p: Ponteiro para armazenar contagem de jogadores ('P').
 * @e: Ponteiro para armazenar contagem de saídas ('E').
 * @c: Ponteiro para armazenar contagem de colecionáveis ('C').
 * Retorna:
 * Esta função não retorna um valor diretamente. 
   Resultados da contagem são armazenados nos ponteiros fornecidos.
*/
static void	ft_count_map_elements(t_game *game, int *p, int *e, int *c)
{
	int	i;
	int	j;
	
	*p = 0;
	*e = 0;
	*c = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			// Incrementa contadores com base nos elementos encontrados
			if (game->map[i][j] == 'P')
				(*p)++;
			else if (game->map[i][j] == 'E')
				(*e)++;
			else if (game->map[i][j] == 'C')
				(*c)++;
			j++;
		}
		i++;
	}	
}

/*
 * ft_check_map_content - Valida o conteúdo do mapa do jogo
 	- Chama ft_validate_map_characters, garantindo que todos caracteres do mapa são válidos
 	- Chama ft_count_map_elements, contando elementos obrigatórios ('P', 'E', 'C')
 * Em seguida, verifica se o mapa atende aos requisitos mínimos:
 	- Exatamente 1 jogador ('P').
 	- Pelo menos 1 saída ('E').
 	- Pelo menos 1 colecionável ('C').
 * @game: Estrutura principal que contém os dados do mapa.
 * Retorna:
 	- 1, se o mapa estiver válido e atender aos critérios obrigatórios.
 	- 0, caso contrário, indicando erro na validação.
*/
int	ft_check_map_content(t_game *game)
{
	int	p; // Jogador
	int	e; // Saída
	int	c; // Colecionáveis
	
	// Validar caracteres no mapa
	if (!ft_validate_map_characters(game))
	{
		write(1, "Error: Invalid map characters\n", 29);
		return (0);
	}
	// Contar os elementos obrigatórios
	ft_count_map_elements(game, &p, &e, &c);

	// Verificar se há 1 jogador, pelo menos 1 saída, e 1 colecionável
	if (p != 1 )
	{
		write(1, "Error: Need exactly 1 'P'\n", 25);
        return (0);
	}
	if (e != 1 )
	{
		write(1, "Error: Need exactly 1 'E'\n", 25);
        return (0);
	}
	if (c < 1)
    {
        write(1, "Error: Need at least 1 'C'\n", 26);
        return (0);
    }
	return (1);// Mapa válido
}
