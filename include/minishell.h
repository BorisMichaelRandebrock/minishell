/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:29:12 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/19 19:52:06 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUF_1MB	1048576
# define BUF_1KB	1024

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
# define EQ_CH		'='

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
	t_token	*tkn;
	t_list	*args;
	bool	is_piped;
}	t_cmd;

typedef struct s_shell
{
	char	*input;
	char	**env;
	t_list	*tkn_lst;
	t_list	*ppln;
}	t_shell;

t_shell		*new_shell(char **sys_env);
void		set_prompt(void);
void		new_env(t_shell *sh, char **sys_env);
char		*get_evar(char *var_name);
void		set_evar(char *var_name, char *value);
void		unset_evar(char *var_name);
void		tokenizer(char *input);
t_shell		*get_shell();
void		token_expansion(t_token *tkn);
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
int			__history(t_list *args, int fd);
void		*sh_calloc(size_t num, size_t size);
void		*sh_ralloc(void *old, size_t new_sizeof);
void		sh_freexit(int exit_code);
void		free_iteration(void);
void		free_env(void);
void		free_shell(void);
void		*sh_guard(void *alloc, void *nullable_old);
void		sh_perror(int error_code);

#endif
