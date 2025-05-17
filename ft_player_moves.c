/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_moves.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 00:16:41 by jcongolo          #+#    #+#             */
/*   Updated: 2025/05/17 22:20:04 by jcongolo         ###   ########.fr       */
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
int	ft_handle_collision(t_game *game, int new_x, int new_y)
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
 * ft_handle_collectibles - Atualiza estado do jogo ao coletar um item ('C')
 * Se o jogador coletar um item, diminui a contagem de coletáveis 
 * @param game: Ponteiro para estrutura principal do jogo (t_game).
 * @param new_y: Nova posição vertical desejada.
 * @param new_x: Nova posição horizontal desejada.
*/
void	ft_handle_collectibles(t_game *game, int new_x, int new_y)
{
	//Verificar celula contem colectabel 'C'
	if (game->map[new_y][new_x] == 'C')
	{
		game->collectibles--;//Decrementado total de 'C' no mapa
		game->map[new_y][new_x] = '0';//Marcar célula como vazia
		
		//Exibir mensagem actualizando colectable
		ft_putstr_fd("Item collected! Remaining: ", 1);
		ft_putnbr_fd(game->collectibles, 1);
		ft_putchar_fd('\n', 1);
	}
}

/*
 * ft_check_victory - Verifica se jogador atingiu saída após coletar os itens.
 * Se todos os coletáveis forem obtidos e jogador alcançar a saída ('E'),
	o jogo termina.
 * @param game: Ponteiro para estrutura principal do jogo (t_game).
 */
void	ft_check_victory(t_game *game)
{
	//Validar vitória: jogador na saída 'E', todos coletáveis 'C' obtidos
	if (game->player_x == game->exit_x &&
		game->player_y == game->exit_y &&
		game->collectibles == 0)
	{
		//Exibir mensagem de vitória
		ft_putstr_fd("You win! Total moves: ", 1);
		ft_putnbr_fd(game->moves, 1);
		ft_putchar_fd('\n', 1);
		
		//Encerra o jogo com segurança
		ft_close_game(game);
	}
}

/*
 * ft_update_player - Atualiza posição do jogador no mapa
	e lida com colisões e coletáveis antes da movimentação.
 * @param game: Estrutura principal do jogo.
 * @param dx: Deslocamento horizontal (-1 para esquerda, 1 para direita, 0 sem alteração).
 * @param dy: Deslocamento vertical (-1 para cima, 1 para baixo, 0 sem alteração).
*/
void	ft_update_player(t_game *game, int dx, int dy)
{
    int	new_x;
    int	new_y;

    // Verificar colisões antes de mover
    new_x = game->player_x + dx;
    new_y = game->player_y + dy;
    if (ft_handle_collision(game, new_x, new_y))
        return;

    // Atualiza coletáveis se houver um item na nova posição
    ft_handle_collectibles(game, new_x, new_y);

    // Atualizar posição do jogador no mapa
    game->map[game->player_y][game->player_x] = '0'; // Remove posição antiga
    game->player_x = new_x;
    game->player_y = new_y;
    game->map[new_y][new_x] = 'P'; // Atualiza posição no mapa
}

/*
 * ft_finalize_move - Finaliza o movimento do jogador,
 * imprimindo os movimentos, atualizando a tela e verificando vitória.
 *
 * @param game: Estrutura principal do jogo.
 */
void	ft_finalize_move(t_game *game)
{
    char	*num_str;
    char	*message;

    // Exibir número de movimentos
    num_str = ft_itoa(game->moves);
    if (!num_str)
        return;
    message = ft_strjoin("playes moves -> ", num_str);
    free(num_str); // Liberar string numérica

    if (message)
    {
        ft_putendl_fd(message, 1);
        free(message); // Liberar mensagem final
    }

    game->moves++;

    // Atualizar tela após o movimento
    ft_render_map(game);

    // Verificar condição de vitória
    ft_check_victory(game);
}

/*
	*
	*
*/