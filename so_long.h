/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:53:33 by jcongolo          #+#    #+#             */
/*   Updated: 2025/05/05 18:04:33 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"   //Biblioteca lbft
# include "mnlbx/mlx.h" //Biblioteca de MiniLibX

// ==Teclas para movimentação e saída==
# define TILE_SIZE 80 //Tamanho dos Sprites
# define KEY_ESC 65307   // ESC: encerrar jogo
# define KEY_W 119     // W: movimento para cima
# define KEY_A 97      // A: movimento para esquerda
# define KEY_S 115      // S: movimento para baixo
# define KEY_D 100      // D: movimento para  direita

/*
 * struct t_game - Estrutura principal para gerenciamento do estado do jogo
 * Campos:
   - map: Mapa do jogo representado como uma matriz de caracteres.
   - map_width/map_height: Dimensões do mapa.
   - mlx/win: Ponteiros para gerenciar a MiniLibX e a janela do jogo.
   - player_x/player_y: Posição atual do jogador no mapa.
   - collectibles: Quantidade total de objetos colecionáveis no mapa.
   - moves: Número de movimentos realizados pelo jogador.
   - exit_x/exit_y: Coordenadas da saída do mapa.
 */
typedef struct s_game
{
	char	**map; //Mapa do jogo representado por uma matriz de caracteres
	int		map_width; //Largura do mapa (numero de tiles)
	int		map_height; //Altura do mapa (numero de tiles)
	void	*mlx; //Ponteiro para gerenciar o MiniLibX
	void	*win; //Ponteiro para a janela do jogo
	int		player_x; //Coluna actual da posiçao do jogador no mapa
	int		player_y; //Celula actual da posiçao do jogador no mapa
    int		exit_x; //Numeros de colunas para encontrar a saida no mapa 
	int		exit_y; //Numeros de celulas para encontrar a saida no mapa
	int		collectibles; //Total de objectos colecionaveis no mapa
	int		moves; //Contador de movimentos realizados pelo jogador
	int		player_found;  // Flag: jogador encontrado (1) ou não encontrado (0)
    int		exit_found;    // Flag: saída encontrada (1) ou não encontrada (0)
	void    *sprites[4]; // Armazena todas as imagens carregadas
    int     sprites_loaded; // Flag para evitar carregamento repetitivo
}			t_game;

/*
 * struct s_flood - Estrutura auxiliar para o algoritmo (Flood Fill)
 
 * Auxilia na validação do mapa, encapsulando:
 * - map: Cópia do mapa para simulação
 * - collectibles: Contador de coletáveis restantes
 * - exit_found: Flag que indica se a saída foi alcançada
 * - map_height/map_width: Dimensões do mapa para navegação
 */
typedef struct	s_flood
{
	char	**map;		 // Cópia do mapa para simulação
	int		collectibles;// Contador de coletáveis restantes
	int		exit_found;  // Flag de saída alcançada (0 ou 1)
	int		map_height;	 // Altura do mapa
	int		map_width;	 // Largura do mapa
}			t_flood;

// Inicializaçao do jogo
int		ft_init_game(t_game *game);
//Funçao para liberar memoria a locada em mapa(matriz bidimensional)
void	ft_free_map(char	**map, int line_count);
//Funçao para encerrar o jogo
void	ft_close_game(t_game *game);
//Funçao captura evento de fechamento da janela e encerra o jogo
int		ft_handle_close(t_game *game);
//Funçao para coordenar a leitura do arquivo e processamento das linhas do mapa
int		ft_read_map(t_game *game, const char *filename);
//Garante que mapa ter exatamente 1 jogador(P), 1 saída(E), e pelo menos 1 coletável(C)
int		ft_check_map_content(t_game *game);


//Algoritmo Flood Fill para simular o caminho do jogador
void	ft_flood_fill(t_flood *flood, int y, int x);
/*
	- Usa um algoritmo Flood Fill para simular caminho do jogador
	- Verifica se todos os C são coletáveis e se a saída E é alcançável.
	- Cria uma cópia temporária do mapa para não modificar o original.
*/
int		ft_flood_fill_check(t_game *game);

//Verifica se todas as bordas do mapa são paredes(1)
int		ft_check_map_walls(t_game *game);
// Validar Map, chamando todas funçoes anteriores
int		ft_validate_map(char *file, t_game *game);
//Carrega sprites do jogo e armazena na estrutura game
void    ft_load_sprites(t_game *game);
//ft_render_map - Percorre o mapa e desenha cada elemento na janela
void	ft_render_map(t_game *game);
//Move jogador para nova posição no mapa
void    ft_move_player(t_game *game, int dx, int dy);
//Captura eventos de teclado e executa ações do jogo
int     ft_handle_keypress(int keycode, t_game *game);

#endif


// sudo apt update
// sudo apt install -y libx11-dev libxext-dev libxrandr-dev libxrender-dev libbsd-dev
// Método 1: Fechar com CTRL + C no terminal

/*
	== MiniLiBX fazer parte diretorio do projecto ==
	
	ls mnlbx/.git
	rm -rf mnlbx/.git

	verificar sempre se esta arquivo existe, depois de compilar
	libmlx.a
*/



