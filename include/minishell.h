/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:29:12 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/21 14:28:38 by brandebr         ###   ########.fr       */
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

typedef struct termios	t_trmcfg;
typedef int(*t_bltin)(t_list *args);

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
	char		**sys_env;
	t_trmcfg	trmcfg;
	t_trmcfg	trmcfgbackup;
	t_list		*tknlst;
	t_list		*ppln;
}	t_shell;

t_shell	*get_shell(void);
t_shell	*new_shell(char **sys_env);
void	set_bltin_exit_code(int exit_code);
void	set_prompt(void);
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
t_bltin	is_builtin(t_cmd *cmd);
bool	try_builtin(t_cmd *cmd, int **pp, bool *status, int ppid);
void	try_process(t_cmd *cmd, int **pp, bool *status, int ppid);
int		__echo(t_list *args);
int		__cd(t_list *args);
int		__pwd(t_list *args);
int		__export(t_list *args);
int		__unset(t_list *args);
int		__env(t_list *args);
int		__exit(t_list *args);
int		__history(t_list *args);
int		sh_syntax_check(t_list *tknlst);
bool	sh_is_accesible(char *cmd_name);
bool	process_rd_in(t_list *rdrs_in, int pp_wr);
bool	process_rd_out(t_list *rdrs_out);
bool	process_rd_out_empty(t_list *rdrs_out);
bool	validate_rdrin(t_token	*_rdr);
bool	validate_cmd(t_cmd *cmd);
bool	validate_rdrout(t_token	*_rdr);
void	*sh_calloc(size_t num, size_t size);
void	*sh_ralloc(void *old, size_t new_sizeof);
void	sh_free(void *content);
void	sh_free_exit(int exit_code);
void	sh_free_reset(void);
void	sh_lfreeppln(t_list *ppln);
void	sh_lfreetkns(t_list *tknlst);
void	*sh_guard(void *alloc, void *nullable_old);
void	sh_perror(char *error_msg, bool exit);
char	*sh_get_dir_name(char *filename);
bool	sh_fexists(char *filename);
bool	sh_check_current_dir(char *cmd_name);
void	sh_fprelay(char *filename, int pipe_wr);
void	sh_pprelay(int pipe_rd, int pipe_wr);
void	sh_ppflush(int pipe_rd);
void	sh_ctrld_handler(void);
void	sh_init_handlers(void);
void	sh_store_stdio(void);
void	sh_restore_stdio(void);
void	sh_redirect_stdin(int fd);
void	sh_redirect_stdout(int fd);

#endif
