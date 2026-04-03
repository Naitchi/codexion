/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:53:06 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/03 12:00:46 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handling.h"

int	error(int error_code, char *str)
{
	int	i;

	i = 0;
	if (!str)
		str = "Error\n";
	while (str[i])
		i++;
	write(2, str, i);
	return (error_code);
}
