/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:06:11 by jcongolo          #+#    #+#             */
/*   Updated: 2025/05/03 16:29:28 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* 

==Testar interface gráfica e criar janela usando biblioteca de MiniLibX
int main(void)
{
    void    *mlx;
    void    *win;

    //Inicializar MLX
    mlx = mlx_init();
    if (!mlx)
    {
        write(2, "Error: MLX initialization failed\n", 33);
        return (1);
    }

    // Criar janela
    win = mlx_new_window(mlx, 640, 480, "Test Window");
    if (!win)
    {
        write(2, "Error: Window creation failed\n", 29);
        return (1);
    }

    // Loop MLX para manter janela aberta
    mlx_loop(mlx);

    return (0);
}
*/


/*
// ==Função para imprimir o código da tecla pressionada==
int print_key(int keycode, void *param)
{
    (void)param; // Ignora o parâmetro não utilizado
    printf("Key pressed: %d\n", keycode);
    return (0);
}
//Captura valor de teclas
int main(void)
{
    void *mlx;   // Ponteiro para a instância gráfica
    void *win;   // Ponteiro para a janela

    // Inicializa a MiniLibX
    mlx = mlx_init();
    if (!mlx)
    {
        printf("Error: Failed to initialize MLX\n");
        return (1);
    }

    // Cria uma nova janela
    win = mlx_new_window(mlx, 640, 480, "Test Window");
    if (!win)
    {
        printf("Error: Failed to create window\n");
        return (1);
    }

    // Captura eventos de teclas e executa a função print_key
    mlx_hook(win, 2, 1L << 0, print_key, NULL);

    // Loop para manter a janela aberta
    mlx_loop(mlx);

    return (0);
}
*/


/*
//==Testar carregamento de SPRITES==
int main(void)
{
    t_game game;

    // Define o mapa manualmente (para teste)
    char *test_map[] =
    {
        "1111",
        "1P01",
        "1C01",
        "111E"
    };

    game.map = test_map;
    game.map_width = 4;
    game.map_height = 4;
    
    // Inicializa MiniLibX e janela
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, game.map_width * TILE_SIZE, game.map_height * TILE_SIZE, "Test Map");

    // Carrega os sprites
    ft_load_sprites(&game);

    // Renderiza o mapa
    ft_render_map(&game);

    // Loop para manter a janela aberta
    mlx_loop(game.mlx);

    return (0);
}

    // *wall.xpm : Se refere a mapa onde estara o jogo
    // *collectible.xpm : se refere a sprite de que vai colectada durante o jogo
    // exit.xpm : se refere a sprite de ponto de saida no jogo
    // *player.xpm : se refere a sprite de jogador
*/

/*
//==Testar movimento de PLayer==
int main(void)
{
    t_game game; // Criar instância do jogo manualmente

    // Inicializar manualmente os valores do jogo
    game.map_width = 5;  
    game.map_height = 5;
    game.player_x = 1;   // Posição inicial do jogador
    game.player_y = 1;
    game.moves = 0;
    game.collectibles = 1; // Simular que há coletáveis no jogo
    game.exit_x = 3; // Definir a saída fictícia
    game.exit_y = 3;

    // Criar um mapa simples para teste
    game.map = malloc(sizeof(char *) * game.map_height);
    
    int i = 0;
    while (i < game.map_height)
    {
        game.map[i] = ft_strdup("11111"); // Inicializar linhas como paredes
        i++;
    }

    // Adicionar coletável e saída no mapa
    game.map[1][1] = 'P'; // Player na posição inicial
    game.map[1][2] = '0'; // Caminho livre
    game.map[2][2] = 'C'; // Coletável
    game.map[3][2] = '0'; // Caminho livre
    game.map[3][3] = 'E'; // Saída do jogo

    // Exibir estado inicial
    printf("Coletível inicial: %d\n", game.collectibles);
    printf("Posição inicial do jogador: x = %d, y = %d\n", game.player_x, game.player_y);
    printf("Número inicial de movimentos: %d\n", game.moves);
    fflush(stdout);

    // Teste `ft_move_player()` garantindo a chamada de `ft_check_victory()`
    ft_move_player(&game, 1, 0); // Movimento para a direita
    ft_check_victory(&game); // Verifica vitória

    ft_move_player(&game, 0, 1); // Movimento para baixo
    ft_check_victory(&game);

    ft_move_player(&game, 0, 1); // Movimento para baixo
    ft_check_victory(&game);

    ft_move_player(&game, 1, 0); // Movimento para a direita (saída)
    ft_check_victory(&game);

    printf("Coletível final: %d\n", game.collectibles);
    
    // Liberar memória
    ft_free_map(game.map, game.map_height);

    return (0);
}

// 1 1 1 1 1
// 1 P 0 1 1
// 1 1 C 1 1
// 1 1 0 E 1
// 1 1 1 1 1
*/

/*
//==Testar movimentos de Player com graficas==
int main(void)
{
    t_game game;

    //Inicializar valores do jogo **ANTES** da criação da janela!
    game.map_width = 5;
    game.map_height = 5;
    game.player_x = 1;
    game.player_y = 1;
    game.moves = 0;
    game.collectibles = 1;
    game.exit_x = 3;
    game.exit_y = 3;

    //Inicializar MLX
    game.mlx = mlx_init();
    if (!game.mlx)
    {
        write(2, "Error: MLX initialization failed\n", 32);
        return (1);
    }

    //Teste para evitar valores inválidos de `map_width` e `map_height`
    if (game.map_width <= 0 || game.map_height <= 0)
    {
        write(2, "Error: Invalid map dimensions\n", 30);
        return (1);
    }

    //Criar a janela **somente após inicializar os valores corretamente**
    game.win = mlx_new_window(game.mlx, game.map_width * TILE_SIZE, game.map_height * TILE_SIZE, "So Long");
    if (!game.win)
    {
        write(2, "Error: Failed to create window\n", 32);
        return (1);
    }

    //Criar mapa para teste
    game.map = malloc(sizeof(char *) * game.map_height);
    int i = 0;
    while (i < game.map_height)
    {
        game.map[i] = ft_strdup("11111"); 
        i++;
    }

    //Adicionar coletável e saída
    game.map[1][1] = 'P';
    game.map[1][2] = '0';
    game.map[2][2] = 'C';
    game.map[3][2] = '0';
    game.map[3][3] = 'E';

    //Carregar sprites e renderizar mapa
    ft_load_sprites(&game);
    ft_render_map(&game);

    //Capturar eventos do teclado
    mlx_hook(game.win, 2, 1L << 0, ft_handle_keypress, &game);

    //Capturar o evento de fechamento da janela (`[X]`)
    mlx_hook(game.win, 17, 1L << 17, ft_handle_close, &game);

    //Manter a janela aberta
    mlx_loop(game.mlx);

    //Liberar memória antes de fechar
    ft_free_map(game.map, game.map_height);

    return (0);
}
*/

//map_validation.c  -> ft_map_validation OK
//game_init.c -> ft_game_init OK
//player_movement.c -> ft_player_moves OK
//graphics_render.c -> ft_render OK


//Main final do jogo
int main(int argc, char **argv)
{
    printf("Iniciando programa...\n"); // Teste inicial
    t_game  game;

    if (argc != 2)
    {
        printf("Usage: ./so_long maps/map1.ber\n");
        return (1);
    }
    
    printf("Validando mapa...\n");
    if (!ft_validate_map(argv[1], &game))
    {
        printf("Erro ao validar o mapa!\n");
        return (1);
    }    
    
    printf("Inicializando jogo...\n");
    ft_init_game(&game);
    
    printf("Carregando sprites...\n");
    ft_load_sprites(&game);

    printf("Renderizando mapa...\n");
    ft_render_map(&game);

    printf("Configurando eventos...\n");
    mlx_key_hook(game.win, ft_handle_keypress, &game);  // Capturar teclas para mover o jogador
    mlx_hook(game.win, 17, 1L << 17, ft_handle_close, &game);  // Capturar evento de fechamento da janela `[X]`

    printf("Iniciando loop MLX...\n");
    mlx_loop(game.mlx); // Iniciar o loop gráfico da MLX

    return (0);
}
