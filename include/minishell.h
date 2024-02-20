/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:29:12 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/20 16:49:17 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define INIT -100
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

typedef struct s_env t_env;

typedef enum e_flst
{
	CNT,
	STRCT,
	NONE
}	t_flst;

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

typedef struct s_shell
{
	bool	is_running;
	char	*raw;
	t_env	*env;
	t_list	*free_lst;
	t_list	*free_cnt;
	t_list	*tkn_lst;
}	t_shell;

typedef struct s_env
{
	char	*last_proc;
	char	*last_exit;
	char	*path;
	char	*pwd;
	char	*old_pwd;
	char	*tmp_dir;
}	t_env;

t_shell		*new_shell(char **env);
t_env		*new_enviorment(char **env);
void		sh_exit(t_shell *shell, int error_code);
void		*sh_calloc(t_shell *shell, size_t size, t_flst freelst);
void		parse(t_shell *sh, char *raw);
#endif
