/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:33:07 by jcongolo          #+#    #+#             */
/*   Updated: 2025/04/23 00:38:51 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/*
 * ft_read_map - Lê o arquivo e armazena o conteúdo no array 'map'.
 * @file: Caminho para o arquivo do mapa.
 * @game: Estrutura principal que contém dados do mapa.
 * Retorna 1 se bem-sucedido, ou 0 em caso de falha.
 */
static int	ft_read_map(char *file, t_game *game)
{
	int		fd;
	int		line_count;
	char	*line;
	size_t	old_size;
	size_t	new_size;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		write(1, "Error: Could not open map file\n", 32);
		return (0);
	}
	line_count = 0;
	game->map = NULL;
	//Ler cada linha do arquivo do Mapa ou matriz do jogo
	while ((line = ft_get_next_line(fd)) != NULL)
	{
		// Substituir '\n' por '\0' para ajustar o término da linha.
		if (line[ft_strlen(line) - 1] == '\n')
		{
			line[ft_strlen(line) - 1] = '\0';
		}
	
		//Tamanho atual do mapa
		old_size = line_count * sizeof(char *);
		//Tamanho com espaço para nova linha
		new_size = (line_count + 1) * sizeof(char *);
		game->map = ft_realloc(game->map, old_size, new_size);
		
		//Em caso de falhar reallocar espaço
		if (!game->map)
		{
			ft_free_map(game->map, line_count);
			close(fd);
			return (0);
		}
		game->map[line_count++] = line;
	}
	close(fd);
	return(line_count > 0);
}

/*
 * ft_check_map_dimensions - Calcula e valida dimensões do mapa
 * @game: Estrutura principal que contém o mapa
 * Retorna 1 se todas linhas tiverem mesmo comprimento, ou 0 caso contrário
 */
static int	ft_check_map_dimensions(t_game *game)
{
	int	i;

	// Inicializar contador de linhas do mapa
	game->map_height = 0;
	//Obter tamanho da primeira linha completo
	game->map_width = ft_strlen(game->map[0]);
	i = 0;

	//Iniciar com a primeira linha do Matriz
	while (game->map[i])
	{
		// Comparar o tamanho da linha atual com o da primeira linha
		if (ft_strlen(game->map[i]) != game->map_width)
		{
			write(1, "Error: Map rows must have the same width.\n", 42);
            return (0);
		}
		game->map_height++;
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
	if (!ft_read_map(file, game))// Validar a leitura do mapa a partir do arquivo
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

