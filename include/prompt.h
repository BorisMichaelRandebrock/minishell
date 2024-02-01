/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/01 16:39:58 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
#define PROMPT_H

typedef struct s_prompt
{
	char *input;
	void (*destructor)();
	void (*prompt)();
} t_prompt;

t_prompt new_prompt(void);

#endif
