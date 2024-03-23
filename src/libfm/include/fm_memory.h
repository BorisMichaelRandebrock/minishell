/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_memory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:43:14 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/23 12:58:05 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FM_MEMORY_H
# define FM_MEMORY_H
# include <stddef.h>

typedef void	(*t_excpt)(void *);

void	*fm_malloc_(size_t size, t_excpt nble_ex, void *nble_arg);
void	*fm_calloc_(size_t size, t_excpt nble_ex, void *nble_arg);
void	*fm_realloc_(void *alloc, size_t size, t_excpt nble_ex, void *nble_arg);
#endif
