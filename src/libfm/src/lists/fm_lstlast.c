/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:03:18 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/23 13:04:33 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fm_lists.h"

//Returns pointer to last node of a list given any node of it.
t_fmlst	*fm_lstlast(t_fmlst *node)
{
	t_fmlst	*last;

	last = node;
	while (last->next)
		last = last->next;
	return (last);
}
