/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 09:50:46 by lnemor            #+#    #+#             */
/*   Updated: 2022/02/24 19:47:16 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char		*line;
	t_lst_cmd	*data;

	while (1)
	{
		line = readline("\033[1;92mminishell>\033[0m");
		if (line)
		{
			add_history(line);
			data = ft_parse_args(line);
		}
		printf("----------------------------------\n");
		print_lst(data);
	}
	return (0);
}
