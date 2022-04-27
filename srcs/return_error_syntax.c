/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_error_syntax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:11:15 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/27 21:27:23 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	return_error_syntax(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	g_rvalue = 258;
	return (-1);
}

int	return_error_syntax_redir(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `newline\"\n", 2);
	g_rvalue = 258;
	return (-1);
}

int	return_error_syntax_2(void)
{
	ft_putstr_fd("minishell: error syntax unexpected symbol\n", 2);
	g_rvalue = 2;
	return (-1);
}

int	return_error_fork(void)
{
	ft_putstr_fd("minishell: fork: Resource temporarily unavailable\n", 2);
	g_rvalue = 1;
	return (-1);
}

int	return_error_redir(char *arg, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(msg, 2);
	g_rvalue = 1;
	return (-1);
}
