/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 13:13:36 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/04 14:05:00 by bclairot         ###   ########.fr       */
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

void	codexion(t_data data)
{
	pthread_t	thread_monitoring;
	pthread_t*	threads;
	int i;
	
	i = 0;
	threads = malloc(sizeof(pthread_create) * data.nbr_of_coders);
	while (i < data.nbr_of_coders)
	{
		pthread_create(&thread[i], NULL, routine(), data); // TODO ici pas bon je passe pas un arg necessaire	
		i++;
	}
	pthread_create(&thread_monitoring, NULL, monitoring(), data); // TODO ici pas bon je passe pas un arg necessaire
}

int	main(int argc, char *argv[])
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (parsing(&data, argc, argv))
		return (1);
	// print_struct(data);
	codexion(data);
	return (0);
}
