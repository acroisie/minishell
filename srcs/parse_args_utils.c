/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:53:16 by acroisie          #+#    #+#             */
/*   Updated: 2022/03/07 16:11:44 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lst_cmd	*ft_create_cell(char **args, int id, t_lst_cmd *prev)
{
	t_lst_cmd	*cell;

	cell = malloc(sizeof(t_lst_cmd));
	if (cell == NULL)
		return (NULL);
	cell->args = args;
	cell->path = NULL;
	cell->pid = 0;
	cell->id = id;
	cell->next = NULL;
	cell->prev = prev;
	return (cell);
}

t_lst_cmd	*ft_lstadd_cell(t_lst_cmd *lst, char **args, int id)
{
	t_lst_cmd	*cell;
	t_lst_cmd	*temp;

	temp = lst;
	cell = ft_create_cell(args, id , NULL);
	if (lst == NULL)
	{
		lst = cell;
		return (cell);
	}
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = cell;
	temp->next->prev = temp;
	return (cell);
}

void	print_lst(t_lst_cmd *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i = 0;
		while (lst->args[i])
		{
			//if (lst->prev)
			//	printf("prev %s\n", lst->prev->args[i]);
			i++;
		}
		lst = lst->next;
	}
}
