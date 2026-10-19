/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:32:01 by hsbeh             #+#    #+#             */
/*   Updated: 2026/04/23 15:32:02 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*lastchr;

	lastchr = NULL ;
	while (*s != '\0')
	{
		if (*s == (char) c)
		{
			lastchr = s;
		}
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return ((char *)lastchr);
}
/*int main ()
{
	char a[15] ="hello alla";
	int w= 108;
	printf("%s ",ft_strrchr(a,w));
}*/
