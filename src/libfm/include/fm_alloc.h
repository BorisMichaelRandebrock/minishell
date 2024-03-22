/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_alloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:43:14 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/22 22:21:54 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FM_ALLOC_H
# define FM_ALLOC_H
# include <stdlib.h>

# define NUL_SZ	1

typedef void	(*t_excpt)(void *);

void	*fm_alloc_(size_t size, t_excpt nble_ex, void *nble_arg);
void	*fm_calloc_(size_t size, t_excpt nble_ex, void *nble_arg);
void	*fm_realloc_(void *alloc, size_t size, t_excpt nble_ex, void *nble_arg);
#endif
