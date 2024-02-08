/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sterm_.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/08 13:19:58 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef sterm_H
# define sterm_H

//TODO quotes
typedef enum e_stermtype
{
	TEXT,
	RD_IN,
	RD_IN_S, //TODO repasar el uso
	RD_OUT,
	RD_OUT_APP,
	VAR,
	PIPE
}	t_stermtype;

typedef struct s_sterm t_sterm;

typedef struct s_sterm
{
	char	*text;
	t_stermtype	type;
	t_sterm		*next;
	t_sterm		*prev;
	t_stermtype	(*get_type)(char *);
}	t_sterm;

t_sterm	new_sterm(void);

#endif
