/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:39:48 by jcongolo          #+#    #+#             */
/*   Updated: 2025/05/17 13:34:46 by jcongolo         ###   ########.fr       */
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
    
    //Inicializar instância gráfica da MiniLibX
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
    //Criar nova janela com largura, altura e título especificados
    game->win = mlx_new_window(game->mlx, window_width, window_height, window_name);
    
    if (!game->win)
    {
        free(game->mlx);
        write(2, "Error: Window creation failed\n", 29);
        return (0);
    }
    return (1);
}

/*
 * ft_process_map_elements - Percorre mapa do jogo e identifica 
    os elementos essenciais.
 * Função verifica cada célula da matriz do mapa, atribuindo valores adequados
    para o jogador ('P'), a saída ('E') e os colecionáveis ('C').
 
 * @param game: Ponteiro para a estrutura principal do jogo (t_game),
              contendo informações sobre o mapa e os elementos.
 */
static void ft_process_map_elements(t_game *game)
{
    int y;
    int x;

    y = -1;
    while (++y < game->map_height)
    {
        x = -1;
        while (++x < game->map_width)
        {
            //Se encontrar ('P'), define sua posição e marca como encontrado
            if (game->map[y][x] == 'P' && !game->player_found)
            {
                game->player_x = x;
                game->player_y = y;
                game->player_found = 1;
            }
            //Se encontrar saída ('E'), define sua posição e marca como encontrada
            else if (game->map[y][x] == 'E' && !game->exit_found)
            {
                game->exit_x = x;
                game->exit_y = y;
                game->exit_found = 1;
            }
            //Se encontrar colecionável ('C'), incrementa o contador
            else if (game->map[y][x] == 'C')
                game->collectibles++;
        }
    }
}

/*
 * ft_init_elements - Inicializa, valida os elementos essenciais do 
    jogo no mapa
 * Função define variáveis de rastreamento dos elementos antes de chamar
    `ft_process_map_elements()` para realizar a análise do mapa.
 
 * Caso o ('P') ou a ('E') estejam ausentes, função retorna erro.
 * @param game: Ponteiro para a estrutura principal do jogo (t_game),
 *              contendo informações sobre o mapa e os elementos.
 * Retorno:
       - 1: Sucesso na localização dos elementos essenciais.
       - 0: Falha caso ('P') ou saída ('E') não sejam encontrados.
 */
static int ft_init_elements(t_game *game)
{
    //Inicializar variáveis para rastrear elementos no mapa
    game->player_found = 0;
    game->exit_found = 0;
    game->collectibles = 0;

    //Percorrer mapa e identificar elementos essenciais
    ft_process_map_elements(game);

    //Verificar se elementos obrigatórios foram encontrados
    if (!game->player_found || !game->exit_found)
    {
        write(2, "Error: Missing player ('P') or exit ('E')\n", 42);
        return (0);
    }
    return (1);
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
    //Inicializar contador de movimentos do jogador
    game->moves = 0;

    //Verificar inicialização gráfica e elementos do mapa
    if (!ft_init_mlx(game) || !ft_init_elements(game))
    {
        //Liberar recursos gráficos em caso de falha
        if (game->mlx)
        {
            if (game->win)
            {
                //Destruir janela caso tenha sido criada
                mlx_destroy_window(game->mlx, game->win);
            }
            //Liberar instância do sistema gráfico
            free(game->mlx);
        }
        //Retornar falha
        return (0);
    }
    return (1);
}

/*
    *
    *
    * 
*/