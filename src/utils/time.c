/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 00:07:45 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/06 15:09:43 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"

long	get_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// TODO pas sur que ce soit bien ca a voir
long	get_passed_time(t_data *data)
{
	long	rn;

	rn = get_ms();
	return (rn - data->starting_time);
}
