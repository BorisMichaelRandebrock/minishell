/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:29:12 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/19 19:04:27 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MEM_ERROR -10
# define NULL_ERROR -11

# define START 0

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
# include <stdio.h> //TODO para pruebas retirar
# include <sys/types.h>
# include "libft.h"

typedef struct s_env		t_env;
typedef struct s_shell		t_shell;
typedef struct s_prompt		t_prompt;
typedef struct s_parser		t_parser;
typedef struct s_token		t_token;
typedef struct s_command	t_command;
typedef struct s_arg		t_arg;
typedef struct s_process	t_process;
typedef struct s_str		t_str;

typedef	enum e_op
{
	RD_IN,
	RD_OUT,
	PIPE,
	RD_OUT_APP,
	RD_IN_S,
	NONE
}	t_op;

typedef struct s_prompt
{
	char	*_input;
	t_shell	*_shell;
	t_list	*_raw_list;
	void	(*destroy)(t_prompt *prompt);
	void	(*invoke)(t_prompt *prompt);
}	t_prompt;

typedef enum e_tokentype
{
	TEXT,
	CMD,
	ARG,
	VAR,
	OP
}	t_tokentype;

typedef struct s_token
{
	char					*_text;
	t_tokentype				*_type;
	t_op					*_op;
	void					(*destroy)(t_token *token);
	t_op					(*get_op_type)(char *text);
}							t_token;

typedef struct s_parser
{
	t_shell					*_shell;
	t_list					*_tokens;
	void					(*destroy)(t_parser *parser);
	void					(*parse)(t_shell *shell);
}							t_parser;

typedef struct s_arg
{
	char					*text;
	t_arg					*next;
}							t_arg;

typedef struct s_command
{
	char					*_name;
	t_arg					*_arg_lst;
	void					(*destroy)(t_command *command);
	void					(*consume_arg)(t_command *command);
	t_shell					*_shell;
}							t_command;

typedef struct s_process
{
	pid_t	_pid;
	int		*_status;
	char	*_ppath;
	char	**_pargs;
	char	**_penvs;
	char	*_output;
	t_shell	*_shell;
	//Free process object resources
	void	(*destroy)(t_process *context);
	//Set absolute path to binary
	void	(*set_path)(t_process *context, char *path);
	//Set process args ended with NULL arg.
	void	(*set_args)(t_process *context, char *args[]);
	//Set process enviorment variables ended with NULL arg. Format "ENV=value".
	void	(*set_env)(t_process *context, char *envs[]);
}	t_process;


typedef struct s_env
{
	char					*last_process_name;
	char					*last_exit_code;
	char					*path;
	char					*pwd;
	char					*old_pwd;
	char					*tmp_dir;
	void					(*destroy)(t_env *env);
}							t_env;

typedef struct s_shell
{
	bool					_is_running;

	struct sigaction sig_action; // TODO hacer un re-typedef?
	t_env					*_enviorment;
	t_prompt				*_prompt;
	t_parser				*_parser;
	t_command				_command;
	t_process				_process;
	void					(*destroy)(t_shell *shell);
	char					*(*proc_exec)(t_process *process);
	void					(*builtin_exec)(t_command *command);
}							t_shell;

t_shell						*new_shell(char **env);
t_env						*new_enviorment(t_shell *shell, char **env);
t_prompt					*new_prompt(t_shell *shell);
t_token						*new_token();
t_parser					*new_parser(t_shell *shell);
t_arg						new_arg(void);
t_command					new_command(void);
t_process					new_process(void);
void						sh_exit(t_shell *shell, int error_code);
void						*sh_calloc(t_shell *shell, size_t size);

#endif
