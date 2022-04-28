/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 09:50:22 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/28 13:49:06 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>

int		g_rvalue;

typedef struct s_lst_redir
{
	char				*file;
	int					append;
	struct s_lst_redir	*next;
}t_lst_redir;

typedef struct s_lst_cmd
{
	t_lst_redir			*first_out;
	t_lst_redir			*first_in;
	t_lst_redir			*first_here;
	pid_t				pid;
	char				**args;
	char				*path;
	char				*relativ_path;
	int					id;
	int					pipe_fd[2];
	t_lst_redir			*lst_out;
	t_lst_redir			*lst_in;
	t_lst_redir			*lst_herdoc;
	struct s_minishell	*data;
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
	char				*cd_pwd;
	char				*pwd;
	char				*path_temp;
	t_lst_cmd			*start_cmd;
	char				*line;
	int					error;
	int					shell_lvl;
}t_minishell;
/************************LINKED_LISTS****************************/

t_lst_redir	*ft_create_tab(char *file);
t_lst_redir	*ft_lstadd_tab(t_lst_redir *lst, char *file);
t_lst_cmd	*ft_create_cell(t_lst_cmd *prev);
t_lst_cmd	*ft_lstadd_cell(t_lst_cmd *lst);
t_lst_redir	*ft_lstlast_tab(t_lst_redir *lst);
void		print_lst(t_lst_cmd *lst);

/***************************PARSING*******************************/

# ifndef DEFAULT_TAB_SIZE
#  define DEFAULT_TAB_SIZE 3
# endif

typedef struct s_var
{
	t_lst_cmd	*lst_cmd;
	int			output;
	int			i;
	int			j;
	int			tab_size;
	char		*temp;
}t_var;

typedef struct s_ki
{
	int	k;
	int	i;
}t_ki;

t_lst_cmd	*ft_parse_args(char *line, char **env);
char		*ft_add_char(char *s1, char c);
void		ft_init_var(t_var *var);
void		ft_write_char_output(char *line, t_var *var);
void		ft_write_string_output(int k, t_var *var, char **env, int mem);
void		ft_pipe_process(char *line, t_var *var);
void		ft_space_process(char *line, t_var *var);
void		ft_quotes_process(char *line, t_var *var, char **env);
void		ft_dol_sign_process(char *line, t_var *var, char **env, int option);
void		ft_tilde_process(t_var *var, char **env);
void		ft_redir_process(char *line, t_var *var);
void		ft_copy_char(char *line, t_var *var);
char		**ft_double_array(t_var *var);
int			ft_heredoc(t_lst_cmd *lst_cmd, t_minishell *data);

/****************************EXEC*********************************/

void		prompt(t_lst_cmd *lst_cmd, t_minishell *data);
int			exec_cmds(t_minishell *data, t_lst_cmd *lst_cmd);
char		*find_path(t_minishell *data, char *cmd);
int			open_redir(t_lst_cmd *lst_cmd);
void		init_dup(t_lst_cmd *lst_cmd);
int			ft_strlencustom(char *s);
int			ft_heredoc(t_lst_cmd *lst_cmd, t_minishell *data);
void		the_noar2(unsigned int nb);
void		the_noar3(unsigned int nb);
void		prompt(t_lst_cmd *lst_cmd, t_minishell *data);

/***************************BUILTINS******************************/

void		ft_cd(t_minishell *data, char **cmd_args, t_lst_cmd *lst_cmd);
void		ft_env(t_minishell *data);
int			is_builtin(t_lst_cmd *lst_cmd);
void		do_builtin(t_minishell *data, t_lst_cmd *lst_cmd);
int			ft_unset(t_minishell *data, char **args);
int			ft_pwd(t_minishell *data);
void		ft_export(t_minishell *data, t_lst_cmd *lst_cmd);
void		ft_exit(t_lst_cmd *lst_cmd);
void		ft_echo(char **args);
void		replace_exist_line(t_minishell *data, char *args);
char		**replace_exist_line_2(t_minishell *data, char *args, char **dest);
char		**replace_exist_line_3(t_minishell *data, char *args, char **dest);

/****************************UTILS*******************************/

void		return_error(char *arg, char *msg, int nb);
void		return_error_2(char *arg, char *msg, int nb);
void		return_error_builtin(char *cmd, char *arg, char *msg, int nb);
void		return_error_exit(char *cmd, char *arg, char *msg, int nb);
int			return_error_export(char *cmd, char *arg, char *msg, int nb);
int			return_error_syntax(void);
int			return_error_syntax_2(void);
int			return_error_fork(void);
int			return_error_syntax_redir(void);
void		display_export(t_minishell *data);
void		the_noar(char *line);
void		ft_ctrl_c(int signal);
void		ft_ctrl_c_h(int signal);
void		ft_ctrl_bslash(int signal);
void		ft_ctrl_bslash_h(int signal);
void		ft_ctrl_f_bslash(int signal);
void		sig_do_nothing(int signal);
void		sig_exit(int signal);
void		ft_ctrl_c_fork(int signal);
int			find_in_env(t_minishell *data, char *var_env);
void		copy_dest(t_minishell *data, char **dest);
int			is_in_env(t_minishell *data, char *arg);
int			do_heredoc(t_lst_cmd *lst_cmd, t_minishell *data);
int			check_redir(t_lst_cmd *lst_cmd);
int			rterf(char *arg);
int			rterp(char *arg);
int			return_error_redir(char *arg, char *msg);
void		oldpwd(t_minishell *data);

#endif