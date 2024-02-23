/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:29:12 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/23 17:30:54 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define INIT -100
# define MEM_ERROR -10
# define NULL_ERROR -11

# define SUCCESS 0
# define FAILURE 1
# define CH_SZ	1

# define NUL_CH '\0'
# define SPC_CH ' '
# define TAB_CH '\t'
# define SQU_CH '\''
# define DQU_CH '"'
# define PIP_CH '|'
# define OUT_CH '>'
# define IN_CH '<'
# define APP_STR ">>"
# define HER_STR "<<"

# include <signal.h>
# include <stdbool.h>
# include "libft.h"

# include <stdio.h> //TODO para pruebas retirar

typedef struct s_env t_env;





typedef enum e_tkntype
{
	CMD,
	ARG,
	OP
}	t_tkntype;

typedef struct s_token
{
	char		*string;
	t_tkntype	type;
}	t_token;

typedef struct s_cmd
{
	t_token	*name;
	t_list	*args;
}	t_cmd;

typedef struct s_shell
{
	bool	is_running;
	char	*raw;
	t_env	*env;
	t_list	*free_lst;
	t_list	*tkn_lst;
	t_list	*cmd_lst;
}	t_shell;

typedef struct s_env
{
	char	*path;
	char	*pwd;
	char	*old_pwd;
	char	*tmp_dir;
	char	*last_proc;
	char	*last_exit;
}	t_env;

t_shell		*new_sh(char **env);
t_env		*new_env(char **env);
void		parse( char *raw);
t_shell		*get_shell();
void		*sh_calloc(size_t num, size_t size);
void		sh_perror(int error_code);
void		sh_exit(int exit_code);
void		*sh_addfree(void *alloc);
void		sequence_cmd(t_shell *sh, t_list *tkn_lst);

#endif
