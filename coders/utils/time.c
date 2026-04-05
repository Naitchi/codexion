/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 00:07:45 by bclairot          #+#    #+#             */
/*   Updated: 2026/04/05 11:01:37 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

long	get_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	get_p_t(long starting_time)
{
	long	rn;

	rn = get_ms();
	return (rn - starting_time);
}

long	get_s_t(t_coder *coder)
{
	long	time;

	time = 0;
	pthread_mutex_lock(&coder->starting_time_mutex);
	time = coder->starting_time;
	pthread_mutex_unlock(&coder->starting_time_mutex);
	return (time);
}

void	set_starting_time(t_coder *coder)
{
	pthread_mutex_lock(&coder->starting_time_mutex);
	coder->starting_time = get_ms();
	pthread_mutex_unlock(&coder->starting_time_mutex);
}

void	ft_sleep(long delay)
{
	long	end;

	end = get_ms() + delay;
	while (get_ms() < end)
		usleep(100);
}
