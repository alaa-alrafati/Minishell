/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:31:06 by hsbeh             #+#    #+#             */
/*   Updated: 2026/04/23 15:31:07 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *ptr)
{
	size_t	x;

	x = 0;
	while (ptr[x] != '\0')
	{
		x++;
	}
	return (x);
}
/*int main ()
{
    char* c ="hello world";
    printf("%d is the length of the given string\n", ft_strlen(c));
}*/
