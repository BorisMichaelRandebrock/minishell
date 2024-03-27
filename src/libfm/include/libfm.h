/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:15:59 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/26 14:12:59 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFM_H
# define LIBFM_H

# include <stddef.h>
# include <stdbool.h>

typedef struct s_fmlst	t_fmlst;
typedef void			(*t_fmiter)(t_fmlst *node, void *fn_arg);
typedef void			(*t_fmexcpt)(void *ex_arg);

typedef struct s_fmlst
{
	void		*item;
	bool		has_nest;
	t_fmlst		*prev;
	t_fmlst		*next;
}	t_fmlst;

void	fm_lstiter(t_fmlst **fmlst, t_fmiter fn);
void	fm_lstiter2(t_fmlst **fmlst, t_fmiter fn, void *fn_arg);
void	fm_lstriter(t_fmlst **fmlst, t_fmiter fn);
void	fm_lstriter2(t_fmlst **fmlst, t_fmiter fn, void *fn_arg);
t_fmlst	*fm_lstfind(t_fmlst *fmlst, void *item);
t_fmlst	*fm_lstfind2(t_fmlst *fmlst, void *item);
t_fmlst	*fm_lsttail(t_fmlst *fmlst);
t_fmlst	*fm_lsthead(t_fmlst *fmlst);
t_fmlst	*fm_lstapp(t_fmlst **fmlst, void *item, t_fmexcpt ex);
t_fmlst	*fm_lstapp2(t_fmlst **fmlst, void *item, t_fmexcpt ex, void *ex_arg);
t_fmlst	*fm_lstprep(t_fmlst **fmlst, void *item, t_fmexcpt ex);
t_fmlst	*fm_lstprep2(t_fmlst **fmlst, void *item, t_fmexcpt ex, void *ex_arg);
t_fmlst	*fm_lstnest(t_fmlst **fmlst, void *item, t_fmexcpt ex);
t_fmlst	*fm_lstnest2(t_fmlst **fmlst, void *item, t_fmexcpt ex, void *ex_arg);
t_fmlst	*fm_lstxtrc(t_fmlst **node);
t_fmlst	*fm_lstxtrc2(t_fmlst **node, t_fmlst *parent);
void	fm_lstdelnd(t_fmlst **node);
void	fm_lstdelnd2(t_fmlst **fmlst, void *item);
void	fm_lstfree(t_fmlst *fmlst);
void	fm_lstwipe(t_fmlst *fmlst);
void	*fm_malloc_(size_t size, t_fmexcpt ex);
void	*fm_malloc2_(size_t size, t_fmexcpt ex, void *ex_arg);
void	*fm_malloc3_(size_t size, t_fmexcpt ex, t_fmlst **applst);
void	*fm_malloc4_(size_t size, t_fmexcpt ex, t_fmlst **preplst);
void	*fm_malloc5_(size_t size, t_fmexcpt ex, t_fmlst **nestlst);
void	*fm_calloc_(size_t size, t_fmexcpt ex);
void	*fm_calloc2_(size_t size, t_fmexcpt ex, void *ex_arg);
void	*fm_calloc3_(size_t size, t_fmexcpt ex, t_fmlst **applst);
void	*fm_calloc4_(size_t size, t_fmexcpt ex, t_fmlst **preplst);
void	*fm_calloc5_(size_t size, t_fmexcpt ex, t_fmlst **nestlst);
void	*fm_realloc_(size_t size, void *alloc, t_fmexcpt ex);
void	*fm_realloc2_(size_t size, void *alloc, t_fmexcpt ex, void *ex_arg);
void	*fm_realloc3_(size_t size, void *alloc, t_fmexcpt ex, t_fmlst **fmlst);
void	*fm_mshld_(void *alloc, t_fmexcpt ex);
void	*fm_mshld2_(void *alloc, t_fmexcpt ex, void *ex_arg);
void	*fm_mshld3_(void *alloc, t_fmexcpt ex, t_fmlst **applst);
void	*fm_mshld4_(void *alloc, t_fmexcpt ex, t_fmlst **preplst);
void	*fm_mshld5_(void *alloc, t_fmexcpt ex, t_fmlst **nestlst);
void	*fm_mshldrw_(void *new, void* old, t_fmexcpt ex);
void	*fm_mshldrw2_(void *new, void* old, t_fmexcpt ex, void *ex_arg);
void	*fm_mshldrw3_(void *new, void* old, t_fmexcpt ex, t_fmlst **applst);
void	*fm_mshldrw4_(void *new, void* old, t_fmexcpt ex, t_fmlst **preplst);
void	*fm_mshldrw5_(void *new, void* old, t_fmexcpt ex, t_fmlst **nestlst);

#endif
