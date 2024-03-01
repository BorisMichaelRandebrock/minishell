/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:26:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/01 18:09:01 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

#define LAST_EXIT_EVAR "?"

void	_exec_builtin(t_bltin bltin, t_cmd *cmd, char *shell_buffer)
{
	pid_t	bltin_pid;
	int		exit_code;
	int		pipefd[2];
	int		fd;

	//TODO @@@@@@@ añadir shell_buffer a  args si existe contenido.
	pipe(pipefd); //TODO debe cerrarse si no hay uso??
	fd = STDOUT_FILENO;
	if (cmd->is_piped)
		fd = pipefd[WR];
	bltin_pid = fork();
	if (bltin_pid == 0)
	{
		(bltin)(cmd->args, fd);
	}
	else if (cmd->is_piped)
	{
		wait3(&exit_code, 0 ,NULL);
		read(pipefd[RD], shell_buffer, BUFSIZ);
		close(pipefd[RD]);
		set_evar(LAST_EXIT_EVAR, sh_addfree(ft_itoa(exit_code)));
	}

}

static char	_to_lower(unsigned int ignore, char c)
{
	(void)ignore;
	return (ft_tolower(c));
}

static void	_exec_pipeline(t_list	*ppln)
{
	static t_bltin	bltin_ptr[7] = {__echo, __cd, __pwd, __export, __unset, __env, __exit};
	static char		*bltin_id[7] = {"echo","cd","pwd","export","unset","env","exit"};
	char			shell_buffer[BUFSIZ];
	t_cmd			*_cmd;
	int				i;

	int j = 0;

	i = 0;
	while(ppln)
	{
		_cmd = ppln->content;
		_cmd->cmd->str = sh_addfree(ft_strmapi(_cmd->cmd->str, _to_lower));
		if (ppln->next)
			_cmd->is_piped = true;
		while (bltin_id[i])
		{
			if (!ft_strncmp(_cmd->cmd->str, bltin_id[i],ft_strlen(bltin_id[i])))
				_exec_builtin(bltin_ptr[i], _cmd, shell_buffer);
			i++;
		}
		i = 0;
		ppln = ppln->next;
		//TODO test borrar
		if (j++ == 0)
			printf("piped: %s", shell_buffer);
	}
}

static void	_skip_redirection(t_list *lst)
{
	t_token	*tkn;

	tkn = lst->content;
	while ((tkn->type != OP && tkn->optype != PIPE) || lst)
		lst = lst->next;
}

void	run_pipeline(t_list *lst)
{
	t_shell	*sh;
	t_token	*_tkn;
	t_cmd	*cmd;
	t_list	*_lst;

	_lst = lst;
	sh = get_shell();
	while(_lst)
	{
		_tkn = _lst->content;
		if (_tkn->type == CMD)
		{
			cmd = sh_calloc(1, sizeof(t_cmd));
			cmd->cmd = _tkn;
			cmd->is_piped = false;
			ft_lstadd_back(&sh->ppln, sh_addfree(ft_lstnew(cmd)));
		}
		else if (_tkn->type == ARG)
			ft_lstadd_back(&cmd->args, sh_addfree(ft_lstnew(_tkn)));
		else if (_tkn->type == OP && _tkn->optype != PIPE)
			_skip_redirection(_lst);
		if (_lst)
			_lst = _lst->next;
	}
	_exec_pipeline(sh->ppln);
}
