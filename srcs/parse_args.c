/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:47:25 by acroisie          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2022/02/24 23:06:29 by acroisie         ###   ########lyon.fr   */
=======
/*   Updated: 2022/02/28 09:08:48 by lnemor           ###   ########lyon.fr   */
>>>>>>> Stashed changes
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
	lst_cmd = ft_create_cell(ft_split(line, ' '));
	temp = ft_split(line, '|'); //Sub str
	while (temp[i])
		i++;
	if (i > 1)
	{
		lst_cmd->args = ft_split(temp[j], ' ');
		j++;
		while (j < i)
		{
			ft_lstadd_cell(lst_cmd, ft_split(temp[j], ' '));
			j++;
		}
	}
	return (lst_cmd);
}
 