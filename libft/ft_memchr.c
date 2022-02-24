/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:37:33 by acroisie          #+#    #+#             */
/*   Updated: 2021/11/03 09:37:33 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size)
{
	char	*str_mb;
	size_t	i;

	str_mb = (char *)memoryBlock;
	i = 0;
	while (i < size)
	{
		if (str_mb[i] == (char)searchedChar)
			return ((void *)&str_mb[i]);
		i++;
	}
	return (NULL);
}
