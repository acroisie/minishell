/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 22:16:47 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/22 22:17:20 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_ctrl_bslash(int signal)
{
	(void) signal;
	if (signal == SIGQUIT)
	{
		ft_putstr_fd(ft_strjoin(rl_prompt, rl_line_buffer), 2);
		ft_putstr_fd("  \b\b", 2);
		rl_redisplay();
	}
}

void	ft_ctrl_f_bslash(int signal)
{
	(void) signal;
	if (signal == SIGQUIT)
	{
		g_rvalue = 131;
		ft_putstr_fd("Quit: 3\n", 2);
		rl_redisplay();
	}
}
