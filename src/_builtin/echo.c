/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:34:05 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/13 18:27:46 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	quotes(char *str)
{
	int		i;
	int		j;
	char	*temp;
	bool	double_q;
	bool	single_q;

	i = -1;
	j = -1;
	double_q = 0;
	single_q = 0;
	temp = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!temp)
		exit(MEM_ERROR);
	while (str[++i])
	{
		if (str[i] == '\"' && !single_q)
			double_q = !double_q;
		if (str[i] == '\'' && !double_q)
			single_q = !single_q;
		if ((str[i] != '\'' && str[i] != '\"') && !(double_q || single_q))
			temp[++j] = str[i];
	}
	free(str);
	return (temp);
}

static int	is_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	echo(t_command *command)
{
	int	i;

	if (!command->_arg_lst->text)
	{
		printf("\n");
		return ;
	}
	i = 1;
	while (command->_arg_lst->text[i] == 'n')
	{
		printf("%s", command->_arg_lst->text);
		if (command->_arg_lst->next)
			printf(" ");
		i++;
	}
	printf("\n");
}
