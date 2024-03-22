/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:27:22 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/22 22:25:41 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FM_LIST_H
# define FM_LIST_H

#include <stdbool.h>

typedef struct s_fmlst	t_fmlst;

typedef enum e_fmlopt
{
	O_CREATE,
	O_NEST,
	O_APPEND,
	O_PREPEND
}	t_fmlopt;

typedef struct s_fmlst
{
	void		*item;
	bool		nested;
	t_fmlst		*prev;
	t_fmlst		*next;
}	t_fmlst;

t_fmlst	*fm_lstlast(t_fmlst *parent);
t_fmlst	*fm_lsthead(t_fmlst *parent);
t_fmlst	*fm_lstnew_(void *item, t_fmlst *nble_fmlst, t_fmlopt opt);
void	fm_lstfree(t_fmlst *parent);
void	fm_lstwipe(t_fmlst *parent);
#endif

//TODO list ring
//TODO list insert
//TODO list extract
//TODO list clone
//TODO list filter

