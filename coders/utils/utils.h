/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:12:59 by bclairot          #+#    #+#             */
/*   Updated: 2026/04/03 18:12:59 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../codexion.h"
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

void	action(t_data *data, int index_coder, char *annonce, int time);
void	free_all(pthread_t *threads, t_data *data, t_thread_data *threads_data);
void	set_stop(t_data *data);
bool	get_stop(t_data *data);
void	inc_compilation_nbr(t_coder *coder);
int		get_compilation_nbr(t_coder *coder);
void	set_starting_time(t_coder *coder);
long	get_starting_time(t_coder *coder);
void	ft_sleep(long delay);
long	get_ms(void);
long	get_passed_time(long starting_time);

#endif
