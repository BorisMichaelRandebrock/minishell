/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:29:12 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/07 17:32:51 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SYS_FDS	2
# define RD			0
# define WR			1

# define INIT		-100
# define MEM_ERROR	-10
# define NULL_ERROR	-11

# define SUCCESS	0
# define FAILURE	1

# define IDX_OFFST	1
# define CH_SZ		1

# define DOLL_CH	'$'
# define NUL_CH		'\0'
# define SPC_CH		' '
# define TAB_CH		'\t'
# define SQU_CH		'\''
# define NL_CH		'\n'
# define DQU_CH		'"'
# define PIP_CH		'|'
# define OUT_CH		'>'
# define IN_CH		'<'

# define APP_STR	">>"
# define HER_STR	"<<"
# define NL_STR		"\n"

# include <signal.h>
# include <stdbool.h>
# include "libft.h"

# include <stdio.h> //TODO para pruebas retirar

typedef struct s_env t_env;
typedef int (*t_bltin)(t_list *args, int fd);
typedef void (*t_cdop)(int fd);

typedef enum e_tkntype
{
	CMD,
	ARG,
	OP
}	t_tkntype;

typedef enum e_optype
{
	PIPE,
	REDIR
}	t_optype;

typedef struct s_token
{
	char		*str;
	t_tkntype	type;
	t_optype	optype;
}	t_token;

typedef struct s_cmd
{
	t_token	*cmd;
	t_list	*args;
	bool	is_piped;
}	t_cmd;

typedef struct s_shell
{
	bool	is_running;
	char	*input;
	char	**env;
	size_t	env_sz;
	t_list	*free_lst;
	t_list	*tkn_lst;
	t_list	*ppln;
}	t_shell;

t_shell		*new_sh(char **sys_env);
char		**new_env(char **sys_env);
char		*get_evar(char *var_name);
void		set_evar(char *var_name, char *value);
void		unset_evar(char *var_name);
void		parse( char *raw);
t_shell		*get_shell();
void		*sh_calloc(size_t num, size_t size);
void		*sh_ralloc(void *old, size_t new_sizeof);
void		sh_perror(int error_code);
void		sh_exit(int exit_code);
void		*sh_addfree(void *alloc);
void		typify(t_list *tkn_lst);
void		expand_var(t_token *tkn);
void		run_pipeline(t_list *tkn_lst);
void		exec_pipeline(t_list *ppln);
char		*get_next_line(int fd);
int			__echo(t_list *args, int fd);
int			__cd(t_list *args, int fd);
int			__pwd(t_list *args, int fd);
int			__export(t_list *args, int fd);
int			__unset(t_list *args, int fd);
int			__env(t_list *args, int fd);
int			__exit(t_list *args, int fd);

#endif
