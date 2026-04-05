/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_types.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:20:00 by bclairot          #+#    #+#             */
/*   Updated: 2026/04/05 11:16:24 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_TYPES_H
# define CODEXION_TYPES_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_coder
{
	int				number_of_compiles_done;
	pthread_mutex_t	number_of_compiles_mutex;
	long			starting_time;
	pthread_mutex_t	starting_time_mutex;
}					t_coder;

typedef struct s_timer
{
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				dongle_cooldown;
}					t_timer;

typedef struct s_dongle
{
	bool			available;
	long			available_time;
	pthread_mutex_t	mutex_dongle;
}					t_dongle;

typedef struct s_data
{
	long			starting_time;
	t_timer			timers;
	t_coder			*coders;
	int				nbr_of_coders;
	t_dongle		*dongle;
	bool			scheduler_fifo;
	int				compiles_required;
	bool			stop;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
}					t_data;

typedef struct s_thread_data
{
	int				index_coder;
	t_data			*data;
}					t_thread_data;

#endif