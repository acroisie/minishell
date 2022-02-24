/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 09:50:46 by lnemor            #+#    #+#             */
/*   Updated: 2022/02/24 14:24:38 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_display_data(t_data data) // To delete
{ // To delete
	int	i; // To delete
 // To delete
	i = 0; // To delete
	while (data.args[i]) // To delete
	{ // To delete
		ft_putendl_fd(data.args[i], 1); // To delete
		i++; // To delete
	} // To delete
} // To delete

int	main(void)
{
	char	*line;
	t_data	*data;

	while (1)
	{
		line = readline("\033[1;92mminishell>\033[0m");
		if (line)
		{
			add_history(line);
			data = ft_parse_args(line);
		}
		ft_display_data(*data); // To delete
	}
	return (0);
}
