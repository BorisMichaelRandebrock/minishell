/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:29:12 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/21 11:31:18 by fmontser         ###   ########.fr       */
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

typedef struct s_shell
{
	bool	is_running;
	char	*raw;
	t_env	*env;
	t_list	*free_lst;
	t_list	*tkn_lst;
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

#endif

/*
static t_token	*_extract_token(char *raw, int start, int end)
{
	t_token	*tkn;
	size_t	length;
	char	*substr;

	length = ++end - start;
	tkn = sh_calloc(NULL, sizeof(t_token), STRCT);
	substr = ft_substr(raw, start, length);
	tkn->string = ft_strtrim(substr, " ");
	free(substr);
	//TODO guardar el puntero en lista CNT
	return (tkn);
}

void	parse(t_shell *sh, char *raw)
{
	int		i;
	int		start;
	int		end;
	bool	flag;
	char	dlmt;

	char *debug = raw;

	flag = true;
	i = 0;
	start = 0;
	dlmt = SPC_CH;
	while (raw[i])
	{
		if (raw[i] == SPC_CH && !flag)
		{
			i++;
			debug++;
			continue ;
		}
		if (!flag)
		{
			if (raw[i] == SQU_CH || raw[i] == DQU_CH)
				dlmt = raw[i];
			else
				dlmt = SPC_CH;
			flag = true;
			start = i;
		}
		else if ((raw[i] == dlmt || raw[i + 1] == NUL_CH) && flag)
		{
			flag = false;
			end = i;
			if (!sh->tkn_lst)
				sh->tkn_lst = ft_lstnew(_extract_token(raw, start, end));
			else
				ft_lstadd_back(&sh->tkn_lst, ft_lstnew(_extract_token(raw, start, end)));
		}
		i++;
		debug++;
	}
}*/
