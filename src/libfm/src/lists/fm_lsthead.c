/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_lsthead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:02:49 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/23 13:04:45 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fm_lists.h"

//Returns pointer to head node of a list given any node of it.
t_fmlst	*fm_lsthead(t_fmlst *node)
{
	t_fmlst	*head;

	head = node;
	while (head->prev)
		head = head->prev;
	return (head);
}
