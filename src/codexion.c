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

void	print_struct(t_data data)
{
	int	i;

	i = 0;
	printf("nbr_of_coders: %d\n", data.nbr_of_coders);
	while (i < data.nbr_of_coders)
	{
		printf("coder n-%d:\n", i);
		printf("number_of_compiles_done: %d\n",
			data.coders[i].number_of_compiles_done);
		i++;
	}
	i = 0;
	while (i < data.nbr_of_coders)
	{
		printf("dongle n-%d: %d\n", i, data.dongle[i].available);
		i++;
	}
	printf("\nstarting_time: %ld\n", data.starting_time);
	printf("time_to_burnout: %d\n", data.timers.time_to_burnout);
	printf("time_to_compile: %d\n", data.timers.time_to_compile);
	printf("time_to_debug: %d\n", data.timers.time_to_debug);
	printf("time_to_refactor: %d\n", data.timers.time_to_refactor);
	printf("number_of_compiles_required: %d\n",
		data.number_of_compiles_required);
	printf("dongle_cooldown: %d\n", data.timers.dongle_cooldown);
	printf("scheduler_fifo: %d\n", data.scheduler_fifo);
}

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
	// print_struct(data);
	if (codexion(&data))
		return (1);
	return (0);
}
