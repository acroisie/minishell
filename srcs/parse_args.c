/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:47:25 by acroisie          #+#    #+#             */
/*   Updated: 2022/02/24 14:31:06 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	*ft_parse_args(char *line)
{
	t_data	*data;
	// char	**temp;

	data = ft_lstnew_cell();
	// temp = ft_split(line, '|');
	data->args = ft_split(line, ' ');
	return (data);
}
