/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 08:27:59 by acroisie          #+#    #+#             */
/*   Updated: 2022/04/14 08:34:43 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_gc_free(tab[i]);
		i++;
	}
	ft_gc_free(tab);
}
