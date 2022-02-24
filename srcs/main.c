/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 09:50:46 by lnemor            #+#    #+#             */
/*   Updated: 2022/02/24 17:36:26 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//void	ft_display_data(t_lst_cmd data) // To delete
//{ // To delete
//	int	i; // To delete
// // To delete
//	i = 0; // To delete
//	while (data.args[i]) // To delete
//	{ // To delete
//		ft_putendl_fd(data.args[i], 1); // To delete
//		i++; // To delete
//	} // To delete
//} // To delete

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
