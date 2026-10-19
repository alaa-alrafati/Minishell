/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:29:06 by hsbeh             #+#    #+#             */
/*   Updated: 2026/04/23 15:29:07 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*int main ()
{

        printf("%d the # is \n",ft_isdigit(5));


    int x = 5;
    if  (ft_isdigit (x))
    {
        printf("%d is digit\n",x);

    }
    else
    {
        printf("%d is NOT digit\n",x);
    }
}*/
