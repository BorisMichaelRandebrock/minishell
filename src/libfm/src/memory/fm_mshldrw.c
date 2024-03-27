/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_mshldrw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:09:54 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/26 13:20:33 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libfm.h"

//Shield allocation and free old, exception handler [1/5]
void	*fm_mshldrw_(void *new, void* old, t_fmexcpt ex)
{
	if (!new)
	{
		if (!ex)
			return (NULL);
		(ex)(NULL);
	}
	if (old)
		free(old);
	return (new);
}

//Shield allocation and free old, exception handler and exception arg [2/5]
void	*fm_mshldrw2_(void *new, void* old, t_fmexcpt ex, void *ex_arg)
{
	if (!new)
	{
		if (!ex)
			return (NULL);
		(ex)(ex_arg);
	}
	if (old)
		free(old);
	return (new);
}

//Shield allocation and free old, exception handler, fmlst append [3/5]
void	*fm_mshldrw3_(void *new, void* old, t_fmexcpt ex, t_fmlst **applst)
{
	if (!new)
	{
		if (!ex)
			return (NULL);
		(ex)(NULL);
	}
	if (old)
		free(old);
	fm_lstapp(applst, new, ex);
	return (new);
}

//Shield allocation and free old, exception handler, fmlst prepend [4/5]
void	*fm_mshldrw4_(void *new, void* old, t_fmexcpt ex, t_fmlst **preplst)
{
	if (!new)
	{
		if (!ex)
			return (NULL);
		(ex)(NULL);
	}
	if (old)
		free(old);
	fm_lstprep(preplst, new, ex);
	return (new);
}
//Shield allocation and free old, exception handler, fmlst prepend [5/5]
void	*fm_mshldrw5_(void *new, void* old, t_fmexcpt ex, t_fmlst **nestlst)
{
	if (!new)
	{
		if (!ex)
			return (NULL);
		(ex)(NULL);
	}
	if (old)
		free(old);
	fm_lstnest(nestlst, new, ex);
	return (new);
}
