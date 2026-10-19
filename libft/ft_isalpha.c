/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:28:57 by hsbeh             #+#    #+#             */
/*   Updated: 2026/04/23 15:28:58 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
/*int main ()
{
    char c ='3';
    if(isalpha(c) == 1)
    {
        printf("%c is an alphabetic character.\n" ,c);
    }else{
         printf("%c is not an alphabetic character.\n", c);
    }

}*/
