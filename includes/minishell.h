/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 09:50:22 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/15 14:29:09 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_lst_redir
{
	char				*file;
	struct s_lst_redir	*next;
}t_lst_redir;

typedef struct s_lst_cmd
{
	pid_t				pid;
	char				**args;
	char				*path;
	char				*relativ_path;
	int					id;
	int					pipe_fd[2];
	t_lst_redir			*lst_out;
	t_lst_redir			*lst_in;
	t_lst_redir			*lst_herdoc;
	int					fd_in;
	int					fd_out;
	struct s_lst_cmd	*next;
	struct s_lst_cmd	*prev;
}t_lst_cmd;

typedef struct s_minishell
{
	struct s_lst_cmd	*cmd;
	char				**new_env;
	char				**path;
	char				cd_pwd[256];
	char				*path_temp;
	t_lst_cmd			*start_cmd;

}t_minishell;

/************************LINKED_LISTS****************************/

t_lst_redir	*ft_create_tab(char *file);
t_lst_redir	*ft_lstadd_tab(t_lst_redir *lst, char *file);
t_lst_cmd	*ft_create_cell(char **args, t_lst_cmd	*prev);
t_lst_cmd	*ft_lstadd_cell(t_lst_cmd *lst, char **args);
t_lst_redir	*ft_lstlast_tab(t_lst_redir *lst);
void		print_lst(t_lst_cmd *lst);

/***************************PARSING*******************************/

# ifndef DEFAULT_TAB_SIZE
#  define DEFAULT_TAB_SIZE 20
# endif

typedef struct s_var
{
	t_lst_cmd	*lst_cmd;
	char		**temp;
	int			i;
	int			j;
}t_var;

t_lst_cmd	*ft_parse_args(char *line);
char		*ft_add_char(char *s1, char c);
void		ft_init_var(t_var *var);
void		ft_space_process(char *line, t_var *var);
void		ft_d_quotes_process(char *line, t_var *var);

/****************************EXEC*********************************/

void		exec_cmds(t_minishell *data, t_lst_cmd *lst_cmd);
char		*find_path(t_minishell *data, char *cmd);

/***************************BUILTINS******************************/

void		ft_cd(t_minishell *data, char **cmd_args);
void		ft_env(t_minishell *data);
int			is_builtin(t_lst_cmd *lst_cmd);
void		do_builtin(t_minishell *data, t_lst_cmd *lst_cmd);

#endif