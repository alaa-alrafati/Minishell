/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:30:58 by hsbeh             #+#    #+#             */
/*   Updated: 2026/04/23 15:30:59 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	x;

	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	x = 0;
	if (destlen >= size)
		return (size + srclen);
	while (src[x] != '\0' && destlen + x < size - 1)
	{
		dest[destlen + x] = src[x];
		x++;
	}
	dest[destlen + x] = '\0';
	return (destlen + srclen);
}
