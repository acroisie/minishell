/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:55:25 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/13 13:39:38 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_ctrl_c(int signal)
{
	(void) signal;
	if (signal == SIGINT)
	{
		printf("\n");
		g_rvalue = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_ctrl_c_h(int signal)
{
	(void) signal;
	if (signal == SIGINT)
	{
		exit(130);
	}
}

void	sig_put_endl(int signal)
{
	(void) signal;
	ft_putchar_fd('\n', 1);
}

void	ft_ctrl_bslash(int signal)
{
	(void) signal;
	if (signal == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
}
