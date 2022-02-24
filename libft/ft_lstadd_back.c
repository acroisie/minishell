/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 09:05:56 by acroisie          #+#    #+#             */
/*   Updated: 2021/11/15 13:07:39 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*start;

	if (*alst == NULL)
	{
		(*alst) = new;
		return ;
	}
	start = *alst;
	*alst = ft_lstlast(*alst);
	(*alst)->next = new;
	*alst = start;
}
