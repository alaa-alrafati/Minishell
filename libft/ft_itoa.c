/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:29:21 by hsbeh             #+#    #+#             */
/*   Updated: 2026/04/23 15:29:22 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n != 0)
	{
		n = n / 10 ;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long				num;
	int					digits;
	char				*s;

	num = n;
	digits = count_digits(num);
	s = malloc(digits + 1);
	if (s == NULL)
		return (NULL);
	s[digits] = '\0';
	if (num == 0)
		s[0] = '0';
	if (num < 0)
	{
		s[0] = '-';
		num = -num ;
	}
	while (num > 0)
	{
		s[digits - 1] = (num % 10) + '0';
		num = num / 10;
		digits--;
	}
	return (s);
}
