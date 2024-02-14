/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:28:13 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/13 18:34:52 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ok(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (0);
	return (1);
}

int	token_count(char *str)
{
	int	count;
	int	i;
	int	qflag;

	count = 0;
	i = 0;
	qflag = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			qflag = !qflag;
		if (((i = 0 && ok(str[i])) && !qflag) || ((!ok(str[i]) && ok(str[i + 1])
					&& !qflag)))
			count++;
		i++;
	}
}
