/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:29:40 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/07 16:42:44 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int	__pwd(t_list *args, int fd)
{
	char	*pwd;

	(void)args;
	pwd = get_evar("PWD");
	write(fd, pwd, ft_strlen(pwd));
	write(fd, "\n", 1);
	return(SUCCESS);
}
