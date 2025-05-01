/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:39:48 by jcongolo          #+#    #+#             */
/*   Updated: 2025/04/28 02:13:48 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * ft_init_mlx - Inicializa sistema gráfico MLX e cria a janela do jogo
 * A função utiliza a MiniLibX (MLX) para inicializar a interface gráfica e
    criar uma janela com as dimensões do mapa. Em caso de falha, retorna 0 e 
    exibe mensagens de erro detalhadas. Caso contrário, retorna 1.
 * @param game: Ponteiro para a estrutura principal do jogo (t_game),
                que contém os dados necessários para criar a janela.
 * Retorno:
    - 1: Sucesso na inicialização do sistema gráfico e na criação da janela.
    - 0: Falha ao inicializar o MLX ou criar a janela.
 */
static int  ft_init_mlx(t_game *game)
{
    int     window_width;
    int     window_height;
    char    *window_name;
    
    // Inicializa a instância gráfica da MiniLibX
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        write(2, "Error: MLX initialization failed\n", 33);
        return (0);
    }
    //Largura de mapa multiplicada por tamanho de sprite em pixels
    window_width = game->map_width * TILE_SIZE;
    //Altura de mapa multiplicada por tamanho de sprite em pixels
    window_height = game->map_height * TILE_SIZE;
    //Nome fixada na janela do jogo
    window_name = "so_long";
    // Cria uma nova janela com largura, altura e título especificados
    game->win = mlx_new_window(game->mlx, window_width, window_height, window_name);
    
    if (!game->win)
    {
        free(game->mlx);
        write(2, "Error: Window creation failed\n", 29);
        return (0);
    }
    return (1); // Sucesso na inicialização gráfica
}

/*
 * ft_init_elements - Inicializa elementos essenciais do jogo no mapa.
    A função percorre matriz do mapa para identificar posição inicial
    do jogador ('P'), da saída ('E'), contabilizar colecionáveis ('C').
    - Caso algum dos elementos obrigatórios esteja ausente, retorna erro.
 * @param game: Ponteiro para a estrutura principal do jogo (t_game),
                contendo informações sobre o mapa e os elementos.
 * Retorno:
      - 1: Sucesso na localização dos elementos essenciais.
      - 0: Falha caso jogador ('P') ou saída ('E') não sejam encontrados.
 */
static int  ft_init_elements(t_game *game)
{
    int y;
    int x;

    // Inicializa variáveis para rastrear os elementos
    game->player_found = 0;
    game->exit_found = 0;
    game->collectibles = 0;
    y = -1;

    // Percorre o mapa linha por linha
    while (++y < game->map_height)
    {
        x = -1;
        while (++x < game->map_width)
        {
            // Se encontrar o jogador ('P') e ainda não tiver sido registrado
            if (game->map[y][x] == 'P' && !game->player_found)
            {
                game->player_x = x;
                game->player_y = y;
                game->player_found = 1; // Marca que o jogador foi encontrado
            }
            // Se encontrar a saída ('E') e ainda não tiver sido registrada
            else if (game->map[y][x] == 'E' && !game->exit_found)
            {
                game->exit_x = x;
                game->exit_y = y;
                game->exit_found = 1; // Marca que a saída foi encontrada
            }
            // Se encontrar um colecionável ('C'), aumenta o contador
            else if (game->map[y][x] == 'C')
            {
                game->collectibles++;
            }
        }
    }
    // Se o jogador ('P') ou a saída ('E') não forem encontrados, retorna erro
    if (!game->player_found || !game->exit_found)
    {
        write(2, "Error: Missing player ('P') or exit ('E')\n", 42);
        return (0);
    }
    return (1);// Sucesso ao localizar elementos obrigatórios
}

/*
 * ft_init_game - Orquestra a inicialização do jogo garantindo que 
   todos componentes essenciais sejam configurados corretamente.
 
    -A função inicializa contador de movimentos do jogador, verifica
    elementos gráficos (MiniLibX) e objetos do mapa foram corretamente
    carregados. Caso algum dos componentes falhe na inicialização,
    função libera recursos gráficos alocados e retorna um erro para
    evitar problemas durante a execução do jogo.
 
 * @param game: Ponteiro para estrutura principal do jogo (t_game),
                contendo dados necessários para inicialização.
 * Retorno:
    - 1: Sucesso na inicialização do jogo.
    - 0: Falha na inicialização gráfica ou na verificação dos elementos.
 */
int ft_init_game(t_game *game)
{
    // Inicializa o contador de movimentos do jogador
    game->moves = 0;

    // Verifica inicialização gráfica e elementos do mapa
    if (!ft_init_mlx(game) || !ft_init_elements(game))
    {
        // Libera recursos gráficos em caso de falha
        if (game->mlx)
        {
            if (game->win)
            {
                // Destroi a janela caso tenha sido criada
                mlx_destroy_window(game->mlx, game->win);
            }
            // Libera instância do sistema gráfico
            free(game->mlx);
        }
        // Retorna falha
        return (0);
    }
    return (1);// Sucesso na inicialização do jogo
}
