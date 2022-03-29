/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cells_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:53:16 by acroisie          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/03/28 17:09:11 by lnemor           ###   ########lyon.fr   */
=======
/*   Updated: 2022/03/29 11:21:23 by acroisie         ###   ########lyon.fr   */
>>>>>>> 54280faa938793e7c6df39c4cd52dc576a49da2e
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lst_cmd	*ft_create_cell(t_lst_cmd *prev)
{
	t_lst_cmd	*cell;

	cell = malloc(sizeof(t_lst_cmd));
	if (cell == NULL)
		return (NULL);
	cell->args = ft_calloc(DEFAULT_TAB_SIZE, sizeof(char *));
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

	lst = malloc(sizeof(t_lst_redir));
	if (lst == NULL)
		return (NULL);
	lst->file = file;
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

void	print_lst(t_lst_cmd *lst)
{
	int	i;
	// int	j;

	i = 0;
	// j = 0;
	while (lst)
	{
		i = 0;
		while (lst->args[i])
		{
			printf("%s*/*", lst->args[i]);
			i++;
		}
		// while (lst->lst_out)
		// {
		// 	printf("%s*/*", lst->lst_out->file);
		// 	j++;
		// 	printf("\n");
		// 	lst->lst_out = lst->lst_out->next;
		// }
		printf("\n");
		lst = lst->next;
	}
}
