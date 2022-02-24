/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:53:16 by acroisie          #+#    #+#             */
/*   Updated: 2022/02/24 15:08:47 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	*ft_lstnew_cell(void)
{
	t_data	*new_lst;

	new_lst = malloc(sizeof(t_data));
	if (new_lst == NULL)
		return (NULL);
	new_lst->next = NULL;
	return (new_lst);
}

void	ft_lstadd_cell(t_data **alst, t_data *new)
{
	new->next = *alst;
	*alst = new;
}
