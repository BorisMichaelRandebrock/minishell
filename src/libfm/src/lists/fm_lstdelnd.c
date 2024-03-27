/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_lstdelnd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:15:13 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/26 14:19:53 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfm.h"

//Extract and delete a node and its item [1/2]
void	fm_lstdelnd(t_fmlst **node)
{
	fm_lstwipe(fm_lstxtrc(node));
}

//Extract and delete a node and its item, given an item and its list [2/2]
void	fm_lstdelnd2(t_fmlst **fmlst, void *item)
{
	t_fmlst	*node;

	node = fm_lstfind2(*fmlst, item);
	fm_lstwipe(fm_lstxtrc(&node));
}
