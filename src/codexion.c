/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 13:13:36 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/13 11:40:40 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	codexion(t_data *data)
{
	int				i;
	pthread_t		*threads;
	pthread_t		thread_monitoring;
	t_thread_data	*threads_data;
	int code;

	i = 0;
	code = 0;
	if (init_threads(data, &threads))
		return (1);
	if (init_threads_data(data, &threads, &threads_data))
		return (1);
	data->starting_time = get_ms();
	while (i < data->nbr_of_coders)	// TODO init pair par pair puis impair par impair pour opti
	{
		if (pthread_create(&threads[i], NULL, routine, &threads_data[i]) != 0)
			code = cut_everything(threads, data, NULL, 1);
		i++;
	}
	if (pthread_create(&thread_monitoring, NULL, monitoring, data) != 0)
		code = cut_everything(threads, data, NULL, 1);
	code = cut_everything(threads, data, &thread_monitoring, 0);
	free_all(threads, data, threads_data);
	return (code);
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
