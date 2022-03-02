/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor.student@42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:47:25 by acroisie          #+#    #+#             */
/*   Updated: 2022/03/01 13:11:23 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lst_cmd	*ft_parse_args(char *line)
{
	t_lst_cmd	*lst_cmd;
	// int			i;
	// int			j;

	// i = 0;
	// while (line[i])
	// {
	// 	if (line[i] == '"')
	// 		while ((line[j] != '"'))
	// 			j++;
	// 	if (line[i] == '|')
			
	// 	i++;
	// }

	char		**temp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	lst_cmd = ft_create_cell(ft_split(line, ' '), j + 1, NULL);
	temp = ft_split(line, '|'); //Sub str
	while (temp[i])
		i++;
	if (i > 1)
	{
		lst_cmd->args = ft_split(temp[j], ' ');
		j++;
		while (j < i)
		{
			ft_lstadd_cell(lst_cmd, ft_split(temp[j], ' '), j + 1);
			j++;
		}
	}
	return (lst_cmd);
}
 