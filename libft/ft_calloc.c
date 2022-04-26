/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:21:16 by acroisie          #+#    #+#             */
/*   Updated: 2022/04/26 10:37:08 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*ptr;

	ptr = malloc(elementCount * elementSize);
	if (ptr == NULL)
	{
		ft_gc_destroy();
		exit(1);
	}
	ft_bzero(ptr, elementCount * elementSize);
	return (ptr);
}
