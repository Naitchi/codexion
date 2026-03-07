/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 00:19:01 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/06 18:34:18 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sleep.h"

// TODO fuze with time at the end of the project
void	ft_sleep(long delay)
{
	long	end;

	end = get_ms() + delay;
	while (get_ms() < end)
		usleep(200);
}
