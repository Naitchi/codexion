/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 00:07:45 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/03 14:53:08 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"

long	get_ms(void) // TODO pas oublier d'init starting_time dans la struct quand on lance.
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec / 1000 + tv.tv_usec * 1000);
}

// TODO pas sur que ce soit bien ca a voir
long	get_passed_time(t_data data)
{
	long	rn;

	rn = get_ms();
	return (rn - data.starting_time);
}
