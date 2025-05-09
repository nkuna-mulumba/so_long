/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_moves.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 00:16:41 by jcongolo          #+#    #+#             */
/*   Updated: 2025/05/09 13:41:40 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * ft_handle_collision - Verifica se jogador pode se mover para nova posição.
 * Se houver uma parede ('1'), o movimento é impedido.
 
 * @param game: Ponteiro para a estrutura principal do jogo (t_game).
 * @param new_y: Nova posição vertical desejada.
 * @param new_x: Nova posição horizontal desejada.
 * @return: 1 se houver colisão, 0 se movimento for permitido.
 */
int ft_handle_collision(t_game *game, int new_x, int new_y)
{
    //Verifica limites horizontais
    if (new_x < 0 || new_x >= game->map_width)
    {
        return (1);
    }

    //Verifica limites verticais
    if (new_y < 0 || new_y >= game->map_height)
    {
        return (1);
    }

    //Só checa a parede se as coordenadas forem válidas!
    if (game->map[new_y][new_x] == '1')
    {
        return (1);
    }

    return (0); // Movimento válido
}

/*
 * ft_handle_collectibles - Atualiza o estado do jogo ao coletar um item ('C').
 
 * Se o jogador coletar um item, diminui a contagem de coletáveis e remove do mapa.
 
 * @param game: Ponteiro para a estrutura principal do jogo (t_game).
 * @param new_y: Nova posição vertical desejada.
 * @param new_x: Nova posição horizontal desejada.
 */
void    ft_handle_collectibles(t_game *game, int new_x, int new_y)
{
    //Verificar a celula contem colectabel 'C'
    if (game->map[new_y][new_x] == 'C')
    {
        game->collectibles--;//Decrementado total de 'C' no mapa
        game->map[new_y][new_x] = '0'; // Marca célula como vazia
        printf("Item collected! Remaining: %d\n", game->collectibles);//Vou ainda usar printf, depois sera substituido por ft_printf
    }
}

/*
 * ft_check_victory - Verifica se jogador atingiu saída após coletar os itens.
 
 * Se todos os coletáveis forem obtidos e o jogador alcançar a saída ('E'),
    o jogo termina.
 * @param game: Ponteiro para a estrutura principal do jogo (t_game).
 */
void    ft_check_victory(t_game *game)
{
    //Validar vitória: jogador na saída 'E', todos coletáveis 'C' obtidos
    if (game->player_x == game->exit_x &&
        game->player_y == game->exit_y &&
        game->collectibles == 0)
    {
        printf("You win! Total moves: %d\n", game->moves);//Depois substituir printf por ft_printf
        //Encerra o jogo com segurança
        ft_close_game(game);
    }
}

/*
 * ft_move_player - Move jogador para nova posição no mapa.
 
 * Verifica colisões, coleta itens e verifica condição de vitória antes de movimentar.
 
 * @param game: Ponteiro para a estrutura principal do jogo (t_game).
 * @param dx: Deslocamento horizontal (-1 para esquerda, 1 para direita, 0 sem alteração).
 * @param dy: Deslocamento vertical (-1 para cima, 1 para baixo, 0 sem alteração).
*/
void    ft_move_player(t_game *game, int dx, int dy)
{
    int new_x = game->player_x + dx;
    int new_y = game->player_y + dy;

    //Verifica colisões antes de mover
    if (ft_handle_collision(game, new_x, new_y))
        return;

    //Atualiza coletáveis se houver um item na nova posição
    ft_handle_collectibles(game, new_x, new_y);

    //Atualiza posição do jogador
    game->map[game->player_y][game->player_x] = '0'; // Remove posição antiga
    game->player_x = new_x;
    game->player_y = new_y;
    game->map[new_y][new_x] = 'P'; // Atualiza posição no mapa

    //Exibe cada movimento do 'P'
    ft_putendl_fd(ft_strjoin("playes moves -> ",ft_itoa(game->moves)),0);
    game->moves++;

    //Atualizar tela após o movimento
    ft_render_map(game);

    //Verifica condição de vitória
    ft_check_victory(game);
}


/*
 * ft_handle_keypress - Captura eventos de teclado e executa ações do jogo.
 
 * Quando uma tecla é pressionada, verifica se é um comando de movimento
 * ('W', 'A', 'S', 'D') e chama a função de movimentação `ft_move_player()`.
 * Se for 'ESC', encerra o jogo chamando `ft_close_game()`.
 
 * @param keycode: Código da tecla pressionada pelo jogador.
 * @param game: Ponteiro para a estrutura principal do jogo (t_game).
 * @return: Retorna 0 após processar a entrada.
 */
int ft_handle_keypress(int keycode, t_game *game)
{
    if (!game)
        return (-1);
    
    //Capturar evento de teclas   
    if (keycode == KEY_ESC)//Tecla ESC para sair do jogo
    {
        ft_close_game(game);
        return (0);
    }
    if (keycode == KEY_W)
    {
        //Movimento para cima
        ft_move_player(game, 0, -1);
    }
    else if (keycode == KEY_S)
    {
        //Movimento para baixo
        ft_move_player(game, 0, 1);
    }
    else if (keycode == KEY_A)
    {
        //Movimento para esquerda
        ft_move_player(game, -1, 0);
    }
    else if (keycode == KEY_D)
    {
        //Movimento para direita
        ft_move_player(game, 1, 0);
    }
    
    return (0);
}

/*
    substituir "printf" em funçoes:
    ft_handle_collectibles;
    ft_handle_collectibles;
*/