/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 00:19:01 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/03 12:00:02 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sleep.h"

void	ft_sleep(long delay)
{
	long	end;

	end = get_ms() + delay;
	while (get_ms() < end)
		usleep(500);
}
