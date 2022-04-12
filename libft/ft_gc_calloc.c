/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_calloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 09:51:00 by acroisie          #+#    #+#             */
/*   Updated: 2022/04/12 10:11:45 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	**ft_gc_start(void)
{
	static t_list	*gc_start;

	return (&gc_start);
}

void	ft_gc_destroy(void)
{
	t_list	*current;
	t_list	*next;
	t_list	**gc_start;

	gc_start = ft_gc_start();
	current = *gc_start;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*gc_start = 0;
}

int	ft_gc_free(void *ptr)
{
	t_list	*prev;
	t_list	*current;
	t_list	*next;
	t_list	**gc_start;

	prev = 0;
	gc_start = ft_gc_start();
	current = *gc_start;
	while (current)
	{
		next = current->next;
		if (current->content == ptr)
		{
			free(ptr);
			free(current);
			if (prev)
				prev->next = next;
			else
				*gc_start = next;
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

void	*ft_gc_calloc(size_t elementCount, size_t elementSize)
{
	char	*ptr;
	t_list	*lst;

	ptr = ft_calloc(elementCount, elementSize);
	if (!ptr)
	{
		ft_gc_destroy();
		return (0);
	}
	lst = ft_calloc(1, sizeof(t_list));
	if (!lst)
	{
		free(ptr);
		ft_gc_destroy();
		return (0);
	}
	lst->content = ptr;
	ft_lstadd_back(ft_gc_start(), lst);
	return (ptr);
}
