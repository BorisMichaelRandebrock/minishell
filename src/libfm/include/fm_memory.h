/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_memory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:43:14 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/23 22:55:10 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FM_MEMORY_H
# define FM_MEMORY_H
# include <stddef.h>

typedef void	(*t_excpt)(void *);

void	*fm_malloc_(size_t size, t_excpt ex);
void	*fm_malloc2_(size_t size, t_excpt ex, void *ex_arg);
void	*fm_malloc3_(size_t size, t_excpt ex, t_fmlst *applst);
void	*fm_malloc4_(size_t size, t_excpt ex, t_fmlst *preplst);
void	*fm_malloc5_(size_t size, t_excpt ex, t_fmlst *nestlst);
void	*fm_calloc_(size_t size, t_excpt ex);
void	*fm_calloc2_(size_t size, t_excpt ex, void *ex_arg);
void	*fm_calloc3_(size_t size, t_excpt ex, t_fmlst *applst);
void	*fm_calloc4_(size_t size, t_excpt ex, t_fmlst *preplst);
void	*fm_calloc5_(size_t size, t_excpt ex, t_fmlst *nestlst);
void	*fm_realloc_(void *alloc, size_t size, t_excpt nble_ex);
void	*fm_realloc2_(void *alloc, size_t size, t_excpt ex, void *ex_arg);
void	*fm_realloc3_(void *alloc, t_fmlst *fmlst, size_t size, t_excpt ex);
void	*fm_mshld(void *alloc, t_excpt ex);
void	*fm_mshld2(void *alloc, t_excpt ex, void *ex_arg);
void	*fm_mshld3(void *alloc, t_excpt ex, void *free_ptr);
void	*fm_mshld4(void *alloc, t_excpt ex, void *ex_arg, void *free_ptr);
#endif
