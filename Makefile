# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 14:11:10 by lnemor            #+#    #+#              #
#    Updated: 2022/03/29 18:21:05 by lnemor           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CC = gcc 

CC_FLAGS = -Wall -Werror -Wextra

NAME := minishell

SRCS := main.c \
		parse_args.c \
		parse_args_utils.c \
		exec.c \
		find_path.c \
		ft_cd.c \
		ft_env.c \
		ft_builtins.c \
		exec_utils.c \
		cells_utils.c \
		parse_args_process_part01.c \
		parse_args_process_part02.c \
		ft_strlencustom.c \
		redir.c \
		return_error.c \
		ft_unset.c \
		ft_prompt.c \
		ft_pwd.c \
		ft_export.c \
		ft_exit.c

OBJS := $(SRCS:.c=.o)

all : libft $(NAME)

$(NAME):		$(addprefix objs/, $(OBJS)) Makefile
					$(CC) -o $(NAME) $(addprefix objs/, $(OBJS)) libft/libft.a -lreadline  -g3 -fsanitize=address -framework CoreFoundation

objs/%.o:		srcs/%.c includes/minishell.h libft/libft.a libft/libft.h
					@mkdir -p objs
					$(CC) $(CC_FLAGS) -c $< -o $@

libft :	
		$(MAKE) -C libft
		
clean :
		rm -rf objs
		make clean -C libft

fclean : clean
		rm -f $(NAME)
		make fclean -C libft

re : fclean all

.PHONY : re clean fclean libft all