/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:34:08 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/05 18:34:08 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATION_H
# define ALLOCATION_H

# include "codexion.h"
int	init_coders(t_data *data, int nbr_of_coders);
int	init_dongles(t_data *data, int nbr_of_coders);
int init_threads(t_data *data, pthread_t **threads);
int init_threads_data(t_data *data, pthread_t **threads
                        ,t_thread_data **threads_data);

#endif
