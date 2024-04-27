/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:29:12 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/27 15:01:59 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUF_1MB		1048576
# define BUF_1KB		1024
# define SUCCESS		0
# define FAILURE		1
# define ERROR_MSG		"Minishell error"

# include <stdbool.h>
# include <termios.h>
# include "libft.h"

# include <stdio.h> //TODO para pruebas retirar

typedef int	(*t_bltin)(t_list *args);
typedef	struct termios t_trmcfg;

typedef enum e_tkntype
{
	CMD,
	ARG,
	RDAPP,
	RDHDOC,
	RDOUT,
	RDIN,
	PIPE
}	t_tkntype;

typedef struct s_token
{
	char		*str;
	t_tkntype	type;
}	t_token;

typedef struct s_cmd
{
	t_token	*tkn;
	t_list	*args;
	t_list	*rdrs_in;
	t_list	*rdrs_out;
}	t_cmd;

typedef struct s_shell
{
	char		*input;
	char		**env;
	t_trmcfg	trmcfg;
	t_trmcfg	trmcfgbackup;
	t_list		*tknlst;
	t_list		*ppln;
}	t_shell;

t_shell	*get_shell(void);
t_shell	*new_shell(char **sys_env);
void	set_prompt(void);
bool	is_builtin(char *cmd_name);
void	new_env(t_shell *sh, char **sys_env);
char	*get_evar(char *var_name);
void	set_evar(char *var_name, char *value);
void	unset_evar(char *var_name);
void	tokenizer(char *input);
void	token_expansion(t_token *tkn);
void	input_expansion(char **input);
void	dequote_token(t_token *tkn);
void	build_commands(t_list *tknlst, t_list **ppln);
void	exec_pipeline(t_list *ppln);
void	invoke_heredoc(char *dlmt, int to_proc_fd);
void	try_process(t_cmd *cmd);
int		__echo(t_list *args);
int		__cd(t_list *args);
int		__pwd(t_list *args);
int		__export(t_list *args);
int		__unset(t_list *args);
int		__env(t_list *args);
int		__exit(t_list *args);
int		__history(t_list *args);
int		sh_syntax_validation(t_list *tknlst);
int		sh_cmd_validation(t_cmd *cmd);
void	*sh_calloc(size_t num, size_t size);
void	*sh_ralloc(void *old, size_t new_sizeof);
void	sh_free(void *content);
void	sh_free_exit(int exit_code);
void	sh_free_reset(void);
void	sh_lfreeppln(t_list *ppln);
void	sh_lfreetkns(t_list *tknlst);
void	*sh_guard(void *alloc, void *nullable_old);
void	sh_perror(char *error_msg, bool exit);
bool	sh_finpath(char *filename);
bool	sh_fexists(char *filename);
bool	sh_fisexec(char *filename);
void	sh_fprelay(char *filename, int pipe_wr);
void	sh_pprelay(int pipe_rd, int pipe_wr);
void	sh_ctrld_handler(void);
void	sh_init_handlers(void);

#endif