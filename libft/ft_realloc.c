/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:20:55 by jcongolo          #+#    #+#             */
/*   Updated: 2025/04/09 19:51:48 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * ft_realloc - Redimensiona um bloco de memória existente.
 * @ptr: Ponteiro para o bloco de memória existente.
 * @old_size: Tamanho do bloco de memória original.
 * @new_size: Novo tamanho desejado para o bloco de memória.
 * 
 * Copia o menor tamanho entre 'old_size' e 'new_size' para evitar
 * acesso indevido além do tamanho original. Retorna um ponteiro
 * para o novo bloco de memória, ou NULL em caso de falha ou 
 * quando 'new_size' é zero.
 */
void    *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void    *new_ptr;
    size_t  copy_size;

    if (!ptr)
    {
        return (ft_calloc(1, new_size));
    }
    if (new_size == 0)
    {
        free(ptr);
        return (NULL);
    }
    new_ptr = ft_calloc(1, new_size);
    if (!new_ptr)
        return (NULL);
    copy_size = old_size;
    if (new_size < old_size)
    {
        copy_size = new_size;
    }
    ft_memcpy(new_ptr, ptr, copy_size);
    free(ptr);
    return (new_ptr);
}
