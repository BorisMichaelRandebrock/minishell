/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:28:25 by fmontser          #+#    #+#             */
/*   Updated: 2023/07/18 11:10:40 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	**ft_free_get(void)
{
	static t_list	*free_list;

	return (&free_list);
}

t_list	**ft_free_add(void *content)
{
	t_list	**free_list;

	free_list = ft_free_get();
	ft_lstadd_back(free_list, ft_lstnew(content));
	return (free_list);
}

void	ft_free_clear(void)
{
	t_list	*free_list;
	t_list	*current_item;

	free_list = *(ft_free_get());
	current_item = free_list;
	while (current_item-> next)
	{
		free(current_item-> content);
		current_item = current_item-> next;
	}
}
