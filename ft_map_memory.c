/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:49:13 by jcongolo          #+#    #+#             */
/*   Updated: 2025/04/14 14:49:28 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Funçao que libera memória alocada para mapa
 * @map: Ponteiro para o array bidimensional (matriz) que contém mapa.
 * @line_count: Número de linhas atualmente alocadas no mapa.
 
 * Esta função percorre todas as linhas do array 'map', liberando
 * cada uma delas individualmente, e em seguida libera o próprio 
 * array 'map'. Isso garante que toda a memória alocada dinamicamente
 * para o mapa seja corretamente liberada, evitando vazamentos de memória.
*/
void	ft_free_map(char	**map, int line_count)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		free(map[i]);
		i++;
	}
	free(map);
}