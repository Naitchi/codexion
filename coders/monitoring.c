/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:48:44 by bclairot          #+#    #+#             */
/*   Updated: 2026/04/05 11:10:12 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	check_coder(t_data *d, int i, int *coders_done)
{
	if (get_compi_nbr(&d->coders[i]) >= d->compiles_required)
	{
		(*coders_done)++;
		return ;
	}
	if (get_p_t(get_s_t(&d->coders[i])) >= d->timers.time_to_burnout)
	{
		pthread_mutex_lock(&d->print_mutex);
		printf("%ld %d burned out\n", get_p_t(d->starting_time), i + 1);
		pthread_mutex_unlock(&d->print_mutex);
		set_stop(d);
	}
}

void	*monitoring(void *arg)
{
	int		i;
	int		coders_done;
	t_data	*d;

	d = (t_data *)arg;
	coders_done = 0;
	while (!get_stop(d) && coders_done < d->nbr_of_coders)
	{
		coders_done = 0;
		i = 0;
		while (i < d->nbr_of_coders)
		{
			check_coder(d, i, &coders_done);
			i++;
		}
		usleep(200);
	}
	set_stop(d);
	return (NULL);
}

int	cut_everything(pthread_t *threads, pthread_t *monitoring_thread, int code)
{
	int	i;

	i = 0;
	while (threads[i])
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	if (monitoring_thread)
		pthread_join(*monitoring_thread, NULL);
	return (code);
}
