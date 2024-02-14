/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:12:26 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/14 18:16:35 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MEM_ERROR -10

# define SUCCESS 0
# define FAILURE 1

# define NUL_CH '\0'
# define SPC_CH ' '
# define TAB_CH '\t'
# define SQU_CH '\''
# define DQU_CH '"'

# include <stdio.h> //TODO para pruebas retirar
# include <sys/types.h>
# include <signal.h>
# include <stdbool.h>

typedef struct s_env		t_env;
typedef struct s_shell		t_shell;
typedef struct s_prompt		t_prompt;
typedef struct s_parser		t_parser;
typedef struct s_token		t_token;
typedef struct s_command	t_command;
typedef struct s_arg		t_arg;
typedef struct s_process	t_process;
typedef struct s_str		t_str;

typedef struct s_str
{
	char	*str;
	t_str	*next;
}	t_str;

typedef struct s_prompt
{
	char	*_input;
	t_shell	*_shell;
	t_str	*_str_list;
	void	(*destroy)(t_prompt *prompt);
	void	(*invoke)(t_prompt *prompt);
}	t_prompt;

typedef enum e_tokentype
{
	TEXT,
	CMD,
	ARG,
	RD_IN,
	RD_IN_S,
	RD_OUT,
	RD_OUT_APP,
	VAR,
	PIPE
}	t_tokentype;

typedef struct s_token
{
	char		*_text;
	t_tokentype	_type;
	t_token		*_prev;
	t_token		*_next;
	void		(*destroy)(t_token *token);
	t_tokentype	(*get_type)(char *);
}	t_token;

typedef struct s_parser
{
	char	**_split;
	t_shell	*_shell;
	t_token	*_tokens;
	void	(*destroy)(t_parser *parser);
	void	(*parse)(t_prompt *prompt);
}	t_parser;

typedef struct s_arg
{
	char		*text;
	t_arg		*next;
}	t_arg;

typedef struct s_command
{
	char	*_name;
	t_arg	*_arg_lst;
	void	(*destroy)(t_command *command);
	void	(*consume_arg)(t_command *command);
	t_shell	*_shell;
}	t_command;

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
	char	*last_process_name;
	char	*last_exit_code;
	char	*path;
	char	*pwd;
	char	*old_pwd;
	char	*tmp_dir;
	void	(*destroy)(t_env *env);
}	t_env;

typedef struct s_shell
{
	bool				_is_running;

	struct sigaction	sig_action;	//TODO hacer un re-typedef?
	t_env				*_enviorment;
	t_prompt			*_prompt;
	t_parser			*_parser;
	t_command			_command;
	t_process			_process;
	void				(*destroy)(t_shell	*shell);
	char				*(*proc_exec)(t_process *process);
	void				(*builtin_exec)(t_command *command);
}	t_shell;

t_shell		*new_shell(char **env);
t_env		*new_enviorment(t_shell *shell, char **env);
t_prompt	*new_prompt(t_shell *shell);
t_token		*new_token(t_shell *shell);
t_parser	*new_parser(t_shell *shell);
t_arg		new_arg(void);
t_command	new_command(void);
t_process	new_process(void);
void		cleanexit(t_shell *shell, int error_code);

#endif
