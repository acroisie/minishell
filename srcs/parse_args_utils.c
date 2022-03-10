/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:53:16 by acroisie          #+#    #+#             */
/*   Updated: 2022/03/10 16:42:18 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lst_cmd	*ft_create_cell(char **args, t_lst_cmd *prev)
{
	t_lst_cmd	*cell;

	cell = malloc(sizeof(t_lst_cmd));
	if (cell == NULL)
		return (NULL);
	cell->args = args;
	cell->path = NULL;
	cell->pid = 0;
	cell->next = NULL;
	cell->prev = prev;
	return (cell);
}

t_lst_cmd	*ft_lstadd_cell(t_lst_cmd *lst, char **args)
{
	t_lst_cmd	*cell;
	t_lst_cmd	*temp;

	temp = lst;
	cell = ft_create_cell(args, NULL);
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
			printf("%s*/*", lst->args[i]);
			i++;
		}
		printf("\n");
		lst = lst->next;
	}
}

// void	ft_quotes_clean(t_lst_cmd *lst_cmd)
// {
// 	int		i;
// 	int		j;
// 	int		n;
// 	char	tmp;

// 	while (lst_cmd)
// 	{
// 		i = 0;
// 		while (lst_cmd->args[i])
// 		{
// 			j = 0;
// 			n = 0;
// 			while (lst_cmd->args[i][j])
// 			{
// 				if (lst_cmd->args[i][j] == '"' || lst_cmd->args[i][j] == '\'')
// 				{
// 					tmp = lst_cmd->args[i][j];
// 					n++;
// 					while (lst_cmd->args[i][n] && lst_cmd->args[i][n] != tmp)
// 						lst_cmd->args[i][j++] = lst_cmd->args[i][n++];
// 					n++;
// 				}
// 				lst_cmd->args[i][j++] = lst_cmd->args[i][n++];
// 			}
// 			// lst_cmd->args[i][j++] = '\0';
// 			i++;
// 		}
// 		lst_cmd = lst_cmd->next;
// 	}
// }

char	*ft_strnjoin_free_s1(char *s1, char *s2, int n)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j] && j < n)
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

void	ft_quotes_clean(t_lst_cmd *lst_cmd)
{
	int		i;
	int		j;
	char	q_type;
	char	*temp;

	i = 0;
	temp = malloc(1 * sizeof(char));
	while (lst_cmd)
	{
		q_type = '\0';
		// temp = "\0";
		while (lst_cmd->args[i])
		{
			j = 0;
			while (lst_cmd->args[i][j])
			{
				if (lst_cmd->args[i][j] == '"')
				{
					
				}
				temp = ft_strnjoin_free_s1(temp, &lst_cmd->args[i][j], 1);
				if (lst_cmd->args[i][j] == '"' || lst_cmd->args[i][j] == '\'')
				{
					q_type = lst_cmd->args[i][j];
					j++;
					while (lst_cmd->args[i][j] != q_type)
					{
						j++;
					}
					j++;
					// while (lst_cmd->args[i][j])
					// {
					// 	temp = ft_strnjoin_free_s1(temp, &lst_cmd->args[i][j], 1);
					// 	j++;
					// }
				}
				temp = ft_strnjoin_free_s1(temp, &lst_cmd->args[i][j], 1);
				j++;
			}
			if(q_type)
				lst_cmd->args[i] = temp;
			// free(temp);
			i++;
		}
		lst_cmd = lst_cmd->next;
	}
}
