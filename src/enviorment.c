/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviorment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:54:42 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/10 19:08:44 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_env		*new_enviorment(t_shell *shell, char **env)
{
	t_env	*new;
	char	**_env;

	new = malloc(sizeof(t_env));
	if (!new)
		cleanexit(shell, MEM_ERROR);

	//TODO LUNES! @@@@@@@@@@ PARSE envs...encontrar la variable y copiarla (ft_dup?)
	(void)_env;
	(void)env;


	return (new);
}

/*

_=/usr/bin/make				ultimo proceso ejecutado (opcional)
?=0							ultimo codigo de salida recibido
PATH=/bin:/usr/local/bin	Rutas del PATH
PWD=/Users/~/minishell		Directorio actual (.)
OLDPWD=/Users/~				Directorio anterior (..)
TMPDIR=						Directorio temporal (opcional)

 */
