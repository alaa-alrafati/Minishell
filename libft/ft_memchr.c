/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:29:51 by hsbeh             #+#    #+#             */
/*   Updated: 2026/04/23 15:29:52 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*string;

	string = (unsigned char *)s;
	while (n--)
	{
		if (*string == (unsigned char)c)
		{
			return ((void *)string);
		}
		string++;
	}
	return (NULL);
}
/*int main ()
{
	char a[20]="hello world!";
	printf("%s" ,(char *)ft_memchr(a,'o',4) );
}*/
