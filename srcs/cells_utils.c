/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cells_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:53:16 by acroisie          #+#    #+#             */
/*   Updated: 2022/04/27 14:05:10 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lst_cmd	*ft_create_cell(t_lst_cmd *prev)
{
	t_lst_cmd	*cell;

	cell = ft_gc_calloc(1, sizeof(t_lst_cmd));
	if (cell == NULL)
		return (NULL);
	cell->args = ft_gc_calloc(DEFAULT_TAB_SIZE, sizeof(char *));
	cell->path = NULL;
	cell->relativ_path = NULL;
	cell->pid = 0;
	cell->fd_in = -1;
	cell->fd_out = -1;
	cell->lst_in = NULL;
	cell->lst_out = NULL;
	cell->lst_herdoc = NULL;
	cell->next = NULL;
	cell->prev = prev;
	return (cell);
}

t_lst_cmd	*ft_lstadd_cell(t_lst_cmd *lst)
{
	t_lst_cmd	*cell;
	t_lst_cmd	*temp;

	temp = lst;
	cell = ft_create_cell(temp);
	if (lst == NULL)
	{
		lst = cell;
		return (cell);
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = cell;
	return (cell);
}

t_lst_redir	*ft_create_tab(char *file)
{
	t_lst_redir	*lst;

	(void) file;
	lst = ft_gc_calloc(1, sizeof(t_lst_redir));
	if (lst == NULL)
		return (NULL);
	lst->file = ft_gc_calloc(1, sizeof(char));
	lst->next = NULL;
	lst->append = 0;
	return (lst);
}

t_lst_redir	*ft_lstadd_tab(t_lst_redir *lst, char *file)
{
	t_lst_redir	*tab;
	t_lst_redir	*temp;

	temp = lst;
	tab = ft_create_tab(file);
	if (lst == NULL)
	{
		lst = tab;
		return (tab);
	}
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = tab;
	return (tab);
}

t_lst_redir	*ft_lstlast_tab(t_lst_redir *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/*
void	print_lst(t_lst_cmd *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i = 0;
		while (lst->args[i])
		{
			printf("%s+0+", lst->args[i]);
			i++;
		}
		printf("\n");
		lst = lst->next;
	}
}
*/
