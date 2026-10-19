/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:28:48 by hsbeh             #+#    #+#             */
/*   Updated: 2026/04/23 15:28:49 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t len, size_t size)
{
	unsigned char	*a;
	size_t			total_size;
	size_t			i;

	total_size = len * size;
	if (len != 0 && total_size / len != size)
		return (NULL);
	if (total_size == 0)
		return (malloc(1));
	a = (unsigned char *)malloc(total_size);
	if (a == NULL)
		return (NULL);
	i = 0;
	while (i < total_size)
	{
		a[i] = 0;
		i++;
	}
	return (a);
}
/*
int main(void)
{
    int *ptr =ft_calloc(3,sizeof(int));
    if (ptr == NULL)
    {
        printf("memory allocation failed\n");
        return (1);
    }
    for (size_t i =0;i <3 ;i++)
    {
        printf("ptr[%zu] = %d \n", i, ptr[i]);
    }
    free(ptr);
    return 0;
}
*/
