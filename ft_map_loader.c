/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:32:06 by jcongolo          #+#    #+#             */
/*   Updated: 2025/05/17 14:17:32 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * ft_open_map_file - Abre arquivo do mapa, retorna descritor de arquivo
 * @filename: Nome do arquivo do mapa
 * Retorno: O descritor do arquivo se bem-sucedido, ou -1 em caso de erro.
*/
static int	ft_open_map_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error: Invalid map file.\n", 26);
		return(-1);   
	}
	return (fd);
}

/*
 * ft_read_map_line - Processa e remove '\n' da linha do mapa
 	antes de armazená-la.
 * @line: Linha lida do arquivo do mapa.
 * Retorno:
 * - Uma cópia da linha sem '\n', pronta para ser armazenada no mapa.
*/
static char	*ft_read_map_line(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')//Remover '\n' caso esteja presente
		line[len - 1] = '\0';
	return (ft_strdup(line));
}

/*
 * ft_load_map_lines - Lê e armazena as linhas do mapa.
 * @fd: Descritor do arquivo do mapa.
 * @game: Estrutura do jogo que armazenará os dados do mapa.
 * Retorno: 1 se bem-sucedido, ou 0 em caso de erro.
*/
static int	ft_load_map_lines(int fd, t_game *game)
{
	char	*line;
	int		i;

	printf("DEBUG: Iniciando leitura do mapa...\n");
	i = 0;

	//Lê cada linha do arquivo e armazena no array `game->map`
	while ((line = ft_get_next_line(fd)) != NULL)
	{
		printf("DEBUG: Linha lida [%d]: %s\n", i, line);

		//Processa e copia a linha para a estrutura do jogo
		game->map[i] = ft_read_map_line(line);
		free(line);

		//Verificar se a cópia falhou
		if (!game->map[i])
		{
			write(2, "Error: Failed to copy map line.\n", 33);
			ft_free_map(game->map, i);
			return (0);
		}

		//Atualizar largura do mapa com base na primeira linha lida
		if (i == 0)
			game->map_width = ft_strlen(game->map[i]);

		i++;
	}

	//Finalizar array do mapa com `NULL` para indicar o fim
	game->map[i] = NULL;

	printf("DEBUG: Leitura do mapa concluída!\n");
	return (1);
}

/*
 * ft_estimate_map_height - Obtém quantidade de linhas de mapa
	a partir de um arquivo.
 
 * @filename - Nome do arquivo que contém o mapa.
 
 * Descrição:
    - Abre o arquivo de mapa em modo leitura.
    - Conta o número de linhas no arquivo, que representa a altura do mapa.
    - Libera a memória das linhas lidas para evitar vazamentos.
    - Fecha o arquivo após a contagem.
    - Retorna o número total de linhas do mapa.
    - Em caso de erro, retorna -1.
 
 * Retorno:
    - Número total de linhas do mapa (altura).
    - Retorna -1 se arquivo não puder ser aberto ou estiver vazio/corrompido.
*/
static int	ft_estimate_map_height(const char *filename)
{
	int		fd;
	char	*line;
	int		height;

	height = 0;
	//Abrir arquivo do mapa
	fd = ft_open_map_file(filename);

	//Contar número de linhas no arquivo
	while ((line = ft_get_next_line(fd)) != NULL)
	{
		free(line);
		height++;
	}

	//Fechar arquivo
	close(fd);

	//Verificação final para evitar valores inválidos
	if (height <= 0)
	{
		write(2, "Error: Map file is empty or corrupted.\n", 39);
		return (-1);
	}

	return (height);
}

/*
 * ft_read_map - Processa e carrega mapa do jogo a partir de arquivo.
 
 * @game     - Estrutura principal do jogo onde o mapa será armazenado.
 * @filename - Nome do arquivo contendo o mapa.
 
 * Descrição:
    - Abre arquivo do mapa para leitura.
    - Determina altura (`map_height`) contando número de linhas no arquivo.
    - Aloca memória para armazenar o mapa.
    - Carrega as linhas do mapa na estrutura `game->map`.
    - Fecha arquivo após a leitura completa.
    - Em caso de erro (arquivo inválido, falha na alocação), retorna 0.
 
 * Retorno:
    - Retorna 1 se a leitura do mapa for bem-sucedida.
    - Retorna 0 se ocorrer qualquer erro durante a execução
*/
int	ft_read_map(t_game *game, const char *filename)
{
	int	fd;
	int	map_height;

	//Inicializar contagem de colecionáveis (`C`)
	game->collectibles = 0;

	//Abrir arquivo do mapa
	fd = ft_open_map_file(filename);
	
	//Determinar altura do mapa
	map_height = ft_estimate_map_height(filename);
	if (map_height <= 0)
	{
		write(2, "Error: Failed to determine map height.\n", 38);
		if (fd != -1)
			close(fd);
		return (0);
	}

	//Inicializar com altura do mapa correcta
	game->map_height = map_height;
	game->map_width = 0;

	//Alocar memória para armazenar matriz do mapa
	game->map = ft_allocate_map_memory(map_height);
	if (!game->map)
		return (close(fd), 0);

	//Carregar linhas do mapa
	if (!ft_load_map_lines(fd, game))
	{
		ft_free_map(game->map, map_height);
		close(fd);
		return (0);
	}

	printf("DEBUG: Dimensões do mapa - Largura: %d | Altura: %d\n", game->map_width, game->map_height);

	//Fechar arquivo corretamente após a leitura
	return (close(fd), 1);
}

/*
  * 
  * 
  *
  *   
*/

