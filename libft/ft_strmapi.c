/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:31:19 by hsbeh             #+#    #+#             */
/*   Updated: 2026/04/23 15:31:20 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new_s;
	size_t			lenofs;

	if (s == NULL || f == NULL)
	{
		return (NULL);
	}
	lenofs = 0;
	while (s[lenofs] != '\0')
	{
		lenofs++;
	}
	new_s = malloc((lenofs + 1) * sizeof(char));
	if (new_s == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		new_s[i] = f(i, s[i]);
		i++;
	}
	new_s[lenofs] = '\0';
	return (new_s);
}
