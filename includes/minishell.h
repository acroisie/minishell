/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 09:50:22 by lnemor            #+#    #+#             */
/*   Updated: 2022/02/24 17:37:43 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_lst_cmd
{
	char				**args;
	struct s_lst_cmd	*next;

}t_lst_cmd;

t_lst_cmd	*ft_create_cell(char **args);
t_lst_cmd	*ft_lstadd_cell(t_lst_cmd *lst, char **args);
t_lst_cmd	*ft_parse_args(char *line);
void		print_lst(t_lst_cmd *lst);

#endif