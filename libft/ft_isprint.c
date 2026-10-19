/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:29:11 by hsbeh             #+#    #+#             */
/*   Updated: 2026/04/23 15:29:12 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int x)
{
	if (x >= 32 && x <= 126)
		return (1);
	return (0);
}
/*int main ()
{

    int x = 40;
    if(ft_isprint(x))
        printf("%d is printable\n ", x);

    else
        printf("%d is NOT printable\n ", x);


}*/
