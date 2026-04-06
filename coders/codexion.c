/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 13:13:36 by bclairot          #+#    #+#             */
/*   Updated: 2026/04/06 13:41:06 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	launch_coder_threads(pthread_t *threads,
		t_thread_data *threads_data, int nbr_of_coders)
{
	int	i;

	i = 0;
	while (i < nbr_of_coders)
	{
		if (pthread_create(&threads[i], NULL, routine, &threads_data[i]) != 0)
			return (1);
		i += 2;
	}
	i = 1;
	while (i < nbr_of_coders)
	{
		if (pthread_create(&threads[i], NULL, routine, &threads_data[i]) != 0)
			return (1);
		i += 2;
	}
	return (0);
}

static int	cleanup_and_fail(pthread_t *threads, t_data *data,
		t_thread_data *threads_data)
{
	cut_everything(threads, data, NULL, 1);
	free_all(threads, data, threads_data);
	return (1);
}

int	codexion(t_data *data)
{
	pthread_t		*threads;
	pthread_t		thread_monitoring;
	t_thread_data	*threads_data;

	if (init_threads(data, &threads))
		return (1);
	if (init_threads_data(data, &threads, &threads_data))
		return (1);
	data->starting_time = get_ms();
	if (launch_coder_threads(threads, threads_data, data->nbr_of_coders))
		return (cleanup_and_fail(threads, data, threads_data));
	if (pthread_create(&thread_monitoring, NULL, monitoring, data) != 0)
		return (cleanup_and_fail(threads, data, threads_data));
	cut_everything(threads, data, &thread_monitoring, 0);
	free_all(threads, data, threads_data);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (parsing(&data, argc, argv))
		return (1);
	if (codexion(&data))
		return (1);
	return (0);
}
