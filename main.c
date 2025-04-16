/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:06:11 by jcongolo          #+#    #+#             */
/*   Updated: 2025/04/16 11:51:37 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


// Função para imprimir o código da tecla pressionada
int print_key(int keycode, void *param)
{
    (void)param; // Ignora o parâmetro não utilizado
    printf("Key pressed: %d\n", keycode);
    return (0);
}
/*Captura valor de teclas */
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

/* Testar interface gráfica e criar janela usando biblioteca de MiniLibX
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