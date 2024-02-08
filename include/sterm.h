/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sterm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/08 17:39:57 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STERM_H
# define STERM_H

# define TERMTYPES 9

//TODO quotes
typedef enum e_stermtype
{
	TEXT,
	CMD,
	ARG,
	RD_IN,
	RD_IN_S, //TODO repasar el uso
	RD_OUT,
	RD_OUT_APP,
	VAR,
	PIPE
}	t_stermtype;

typedef struct s_sterm	t_sterm;

typedef struct s_sterm
{
	char		*text;
	t_stermtype	type;
	t_sterm		*prev;
	t_sterm		*next;
	void		(*destroy)(t_sterm * context);
	t_stermtype	(*get_type)(char *);
}	t_sterm;

t_sterm	*new_sterm(void);

#endif
