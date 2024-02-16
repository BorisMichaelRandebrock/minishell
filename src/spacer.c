/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spacer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:42:29 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/16 18:50:17 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static bool	_is_operator(char c)
{
	char	*ops;
	int		i;

	i = 0;
	ops = "|<>";
	while (ops[i])
	{
		if (c == ops[i])
			return (true);
		i++;
	}
	return (false);
}

static int	_count_op(char *str)
{
	size_t	count;
	int		i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>')
		{
			count++;
			i++;
		}
		else if (str[i] == '<' && str[i + 1] == '<')
		{
			count++;
			i++;
		}
		else if (_is_operator(str[i]))
			count++;
		i++;
	}
	return (count);
}

static size_t	_insert_spc(char *ptr, t_op op)
{
	static char	*dict[] = {" < ", " > ", " | ", " >> ", " << "};
	size_t		offset;
	size_t		op_sz;

	offset = 3;
	op_sz = 1;
	if (op > 2)
	{
		offset = 4;
		op_sz = 2;
	}
	ft_memmove((ptr + offset), ptr, ft_strlen(ptr) + NUL_SZ);
	ft_memmove(ptr, dict[op], offset);
	ft_memmove(ptr + offset, ptr + offset + op_sz,
		ft_strlen(ptr + offset + op_sz) + NUL_SZ);
	return (offset);
}

static void	_replace_op(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>')
			i += _insert_spc(&str[i], RD_OUT_APP);
		else if (str[i] == '<' && str[i + 1] == '<')
			i += _insert_spc(&str[i], RD_IN_S);
		else if (str[i] == '|')
			i += _insert_spc(&str[i], PIPE);
		else if (str[i] == '>')
			i += _insert_spc(&str[i], RD_OUT);
		else if (str[i] == '<')
			i += _insert_spc(&str[i], RD_IN);
		i++;
	}
}

void	add_space(t_prompt *prompt)
{
	size_t	size;
	size_t	new_size;
	size_t	term_sz;
	char	*new_input;

	term_sz = 2;
	size = ft_strlen(prompt->_input);
	new_size = ((_count_op(prompt->_input) * 2) + size + term_sz + NUL_SZ);
	new_input = ft_realloc(prompt->_input, new_size * sizeof(char));
	_replace_op(new_input);
	new_size = ft_strlen(new_input);
	ft_memcpy(&new_input[new_size], " \0", term_sz);
	prompt->_input = new_input;
}
