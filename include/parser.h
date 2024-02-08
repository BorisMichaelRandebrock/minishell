/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/08 13:09:31 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "prompt.h"





typedef struct s_parser t_parser;

typedef struct s_parser
{
	char	**_split;
	void	(*destroy)(t_parser *context);
	void	(*parse)(t_parser *context, t_prompt *prompt);
} t_parser;

t_parser	new_parser(void);

#endif
