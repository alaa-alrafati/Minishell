/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:30:01 by hsbeh             #+#    #+#             */
/*   Updated: 2026/04/23 15:30:03 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ss1;
	const unsigned char	*ss2;

	ss1 = (const unsigned char *)s1;
	ss2 = (const unsigned char *)s2;
	while (n != 0)
	{
		if (*ss1 != *ss2)
		{
			return (*ss1 - *ss2);
		}
		n--;
		ss1++;
		ss2++;
	}
	return (0);
}
/*int main()
{
	char a [20] ="helloa";
	char b [20] ="hellob";
	printf("%d", ft_memcmp(a , b , 6));
}*/
