/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:47:25 by acroisie          #+#    #+#             */
/*   Updated: 2022/03/14 16:46:15 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_check_status(char c, int *i, t_status *status)
{
	if (c == '"')
		status->d_quotes = (!status->d_quotes);
	if (c == '\'')
		status->s_quote = (!status->s_quote);
	if (c == '$')
		status->dollar = (!status->dollar);
	if (c == ' ')
		status->space = (!status->space);
	if (c == '|')
		status->pipe = (!status->pipe);
}

t_lst_cmd	*ft_parse_args(char *line)
{
	t_lst_cmd	lst_cmd;
	t_status	*status;
	char		**temp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	temp = malloc(STD_TAB * sizeof(char *));
	while (line[i])
	{
		temp[i] = malloc(1 * sizeof(char));
		temp[i] = '\0';
		while (ft_isspace(line[i]))
			i++;
		ft_check_status(line[i], &i, status);
		if (ft_process_status(status))
			ft_add_char(temp[i], line[i]);
		if (status->space)
			j++;
		if (status->pipe)
		{
			if (!&lst_cmd)
				ft_create_cell(temp, NULL);
			else
				ft_lstadd_cell(&lst_cmd, temp);
		}
	}
}
