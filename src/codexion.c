/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 13:13:36 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/04 14:51:30 by bclairot         ###   ########.fr       */
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
		printf("number_of_compiles_done: %d\n", data.coders[i].number_of_compiles_done);
		printf("compile: %d\n", data.coders[i].compile);
		printf("debug: %d\n", data.coders[i].debug);
		printf("refactor: %d\n", data.coders[i].refactor);
		printf("burnout: %d\n\n", data.coders[i].burnout);
		i++;
	}
	i = 0;
	while (i < data.nbr_of_coders)
	{
		printf("dongle n-%d: %d\n", i, data.available_dongle[i]);
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
	t_thread_data 	*threads_data;

	i = 0;
	// TODO peut-etre fuse les deux sachant qu'elles sont dependante que dans le free, a voir
	if(init_threads(data, &threads))
		return (1);
	if(init_threads_data(data, &threads, &threads_data))
		return (1);
	data->starting_time = get_ms();
	while (i < data->nbr_of_coders)
	{
		pthread_create(&threads[i], NULL, routine, &threads_data[i]);
		i++;
	}
	monitoring(data);
	cut_everything(threads, data);
	return (0);
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
