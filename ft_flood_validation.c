/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flood_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:33:07 by jcongolo          #+#    #+#             */
/*   Updated: 2025/04/27 16:08:45 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * ft_flood_fill - Algoritmo (Flood Fill) para verificar acessibilidade no mapa.

 * Percorre o mapa a partir de (`x`, `y`), processa colecionáveis ('C'),
 * verifica se a saída ('E') foi alcançada e marca áreas acessíveis no mapa.
 
 * @flood: Estrutura com informações do mapa, dimensões e colecionáveis.
 * @y: Coordenada vertical atual.
 * @x: Coordenada horizontal atual.
 
 * Comportamento:
 	- Retorna se as coordenadas forem inválidas, ou a célula for uma parede ('1')
      ou já visitada ('X').
 	- Reduz o contador de 'C' ou marca a saída ('E') como alcançada.
 	- Marca a célula como visitada e propaga nas 4 direções: baixo, cima,
	  direita, esquerda.
 */
void	ft_flood_fill(t_flood *flood, int y, int x)
{
	// Verifica se as coordenadas estão fora dos limites do mapa
	if (y < 0 || x < 0 || y >= flood->map_height || x >= flood->map_width)
	{
		return ;//Coordenadas inválidas
	}
	// Verifica se a célula atual é uma parede ('1') ou já foi visitada ('X')
	if (flood->map[y][x] == '1' || flood->map[y][x] == 'X')
	{
		return ; // Célula não acessível
	}

	//Processa celula actual
	if (flood->map[y][x] == 'C')// Se a célula contém um colecionável ('C')
	{
		flood->collectibles--; // Reduz o número de colecionáveis restantes
	}
	else if (flood->map[y][x] == 'E') // Se a célula contém a saída ('E')
	{
		flood->exit_found = 1; //Saida foi encontrada
	}

	// Marca a célula como visitada
	flood->map[y][x] = 'X';

	// Propaga para as 4 direções
	ft_flood_fill(flood, y + 1, x);//Abaixo
	ft_flood_fill(flood, y - 1, x);//Cima
	ft_flood_fill(flood, y, x + 1);//Direita
	ft_flood_fill(flood, y, x - 1);//Esquerda
}


/*
 * Inicializa a estrutura auxiliar usada no Flood Fill.
 * @flood: Ponteiro para a estrutura auxiliar.
 * @game: Ponteiro para a estrutura principal do jogo.
*/
static void ft_init_flood_struct(t_flood *flood, t_game *game)
{
	flood->collectibles = game->collectibles;
	flood->exit_found = 0;
	flood->map_height = game->map_height;
	flood->map_width = game->map_width;
}

/*
 * Criar uma cópia do mapa original.
 * @original_map: Mapa original do jogo.
 * @map_height: Número de linhas do mapa.
 * Retorna o mapa copiado ou NULL em caso de falha.
*/
static char **ft_create_map_copy(char **original_map, int map_height)
{
	char	**map_copy;
	int		i;
	//Validar mapa orginal
	if (!original_map || map_height <= 0)
    {
		return (NULL);
	}	
	//Alocar memora para bidimencional
	map_copy = malloc(sizeof(char *) * map_height);
	if (!map_copy)
	{
    	write(2, "Error: Failed to allocate memory for map copy\n", 46);
    	return (NULL);
	}
	//Duplicar mapa da estrutura "t_game" para "t_flood"
	i = 0;
	while ((i < map_height))
	{
		map_copy[i] = ft_strdup(original_map[i]);
		if(!map_copy[i])
		{
			ft_free_map(map_copy, i);
			return (NULL);
		}
		i++;
	}
	return(map_copy);
}

/*
 * Valida os resultados do Flood Fill.
 * @flood: Ponteiro para a estrutura auxiliar.
 * Retorna 1 se válido, 0 caso contrário.
*/
static int ft_validate_flood_results(t_flood *flood)
{
	if (flood->collectibles != 0 || !flood->exit_found)
	{
		write(1, "Error: No valid path (collectibles or exit unreachable)\n", 52);
        return (0);
	}
	return (1);
}

/*
 * Verifica se o mapa é válido usando o algoritmo Flood Fill.
 * Cria uma cópia do mapa, executa Flood Fill e valida acessibilidade.
 * Retorna 1 se válido, 0 caso contrário.
*/
int	ft_flood_fill_check(t_game *game)
{
	t_flood flood;
	char	**map_copy;

	// Inicializa a estrutura auxiliar para o Flood Fill
	ft_init_flood_struct(&flood, game);
	
	// Cria uma cópia do mapa original
	map_copy = ft_create_map_copy(game->map, game->map_height);
	if (!map_copy)
	{
		return (0);
	}
	
	// Executa o Flood Fill a partir da posição do jogador
	flood.map = map_copy;
	ft_flood_fill(&flood, game->player_y, game->exit_x);

	// Libera a memória do mapa copiado
	ft_free_map(map_copy, game->map_height);

	// Verifica se o caminho é válido
	return (ft_validate_flood_results(&flood));	
}
