/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_lsthead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:02:49 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/26 13:20:11 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfm.h"

//Returns head node of a fmlst given any node of it [1/1]
t_fmlst	*fm_lsthead(t_fmlst *fmlst)
{
	while (fmlst && fmlst->prev)
		fmlst = fmlst->prev;
	return (fmlst);
}
