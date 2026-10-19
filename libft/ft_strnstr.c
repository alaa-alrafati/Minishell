/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:31:56 by hsbeh             #+#    #+#             */
/*   Updated: 2026/04/23 15:31:57 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	b;
	size_t	l;

	b = 0;
	if (*little == '\0')
	{
		return ((char *) big);
	}
	while (big[b] != '\0' && b < len)
	{
		l = 0;
		while ((b + l) < len && big[b + l] == little[l])
		{
			l++;
			if (little[l] == '\0')
			{
				return ((char *)(big + b));
			}
		}
		b++;
	}
	return (NULL);
}
/*int main ()
{
	char a[]="hello world";
	char b[]="l";
	printf("%s\n", ft_strnstr(a , b, 11));
}*/
