/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:30:53 by hsbeh             #+#    #+#             */
/*   Updated: 2026/04/23 15:30:54 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s1ands2;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s1ands2 = malloc (s1_len + s2_len + 1);
	if (s1ands2 == NULL)
		return (NULL);
	ft_memcpy(s1ands2, s1, s1_len);
	ft_memcpy(s1ands2 + s1_len, s2, s2_len);
	s1ands2[s1_len + s2_len] = '\0';
	return (s1ands2);
}
/*int main()
{
    char *a = "hello";
    char *b = "world!";
    printf("%s\n",ft_strjoin(a,b));
}*/
