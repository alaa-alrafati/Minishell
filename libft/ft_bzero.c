/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:28:43 by hsbeh             #+#    #+#             */
/*   Updated: 2026/04/23 15:28:44 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
/*int main(void)
{
    char buffer[10] = "abcdefghi";

    printf("Before: %s\n", buffer);
    ft_bzero(buffer, 6);
    printf("After:  %s\n", buffer);// Expected: (empty or garbage after nulls)

    return 0;
}*/
