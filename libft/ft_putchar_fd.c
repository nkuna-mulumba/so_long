/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:30:25 by jcongolo          #+#    #+#             */
/*   Updated: 2025/05/12 14:59:30 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
	{
		write (fd, &c, 1);
	}
}
/*
int main() {
	int fd = open("test.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
	{
       perror("Error opening file");
       return 1;
	}

   char c;
   printf("Introduce un carácter: ");
   c = getchar(); 
   ft_putchar_fd(c, fd);

   close(fd);
   return 0;
}
*/
