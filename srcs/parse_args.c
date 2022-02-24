/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:47:25 by acroisie          #+#    #+#             */
/*   Updated: 2022/02/24 17:58:46 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lst_cmd	*ft_parse_args(char *line)
{
	t_lst_cmd	*lst_cmd;
	char		**temp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	lst_cmd = ft_create_cell(ft_split(line, ' '));
	temp = ft_split(line, '|');
	while (temp[i])
		i++;
	if (i > 1)
	{
		while (j < i)
		{
			ft_lstadd_cell(lst_cmd, ft_split(temp[j], ' '));
			j++;
		}
	}
	return (lst_cmd);
}
