/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:55:25 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/21 13:48:41 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd(ft_strjoin(rl_prompt, rl_line_buffer), 2);
		ft_putstr_fd("  \b\b", 2);
		rl_redisplay();
		g_rvalue = 131;
		ft_putendl_fd("", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_ctrl_c_f(int signal)
{
	if (signal == SIGINT)
	{
		rl_redisplay();
		g_rvalue = 131;
	}
}

void	ft_ctrl_c_h(int signal)
{
	(void) signal;
	if (signal == SIGINT)
		exit(130);
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
	{
		ft_putstr_fd(ft_strjoin(rl_prompt, rl_line_buffer), 2);
		ft_putstr_fd("  \b\b", 2);
		rl_redisplay();
	}
}
