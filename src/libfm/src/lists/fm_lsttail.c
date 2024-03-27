/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_lsttail.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:03:18 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/26 13:20:11 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfm.h"

//Returns tail node of a fmlst given any node of it [1/1]
t_fmlst	*fm_lsttail(t_fmlst *fmlst)
{
	while (fmlst && fmlst->next)
		fmlst = fmlst->next;
	return (fmlst);
}
