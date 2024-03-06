/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:20:05 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/06 22:56:29 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

//TODO return errors?
int	__export(t_list *args, int fd)
{
	(void)args;
	(void)fd;
	/*
		NOTA: no implementar opciones.

		1. Sin argumentos
			- export sin argumentos muestra una lista de todas las variables de shell que han sido exportadas como variables de entorno.
			- env muestra todas las variables de entorno disponibles en el entorno actual del shell, incluyendo aquellas que han sido exportadas y aquellas que no.
		2. Con argumentos
			- crea una nuevas varaibles de entorno si no existen, de lo contrario las sobreescribe. args:  VAR1=asdasd VAR2=lllll ...
	*/
	return (SUCCESS);
}
