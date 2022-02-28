/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 09:50:22 by lnemor            #+#    #+#             */
/*   Updated: 2022/02/28 15:57:48 by lnemor           ###   ########lyon.fr   */
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
	pid_t				pid;
	char				**args;
	char				*path;
	int					id;
	struct s_lst_cmd	*next;

}t_lst_cmd;

typedef struct s_minishell
{
	struct s_lst_cmd	*cmd;
	char				**new_env;
	char				**path;
	char				*path_temp;
	char				*path_1;
	int					file_in;
	int					file_out;
	int					pipe_fd[2];

}t_minishell;

t_lst_cmd	*ft_create_cell(char **args, int id);
t_lst_cmd	*ft_lstadd_cell(t_lst_cmd *lst, char **args, int id);
t_lst_cmd	*ft_parse_args(char *line);
void		print_lst(t_lst_cmd *lst);
void		exec_cmds(t_minishell *data, t_lst_cmd *lst_cmd);
char		*find_path(t_minishell *data, char *cmd);

#endif