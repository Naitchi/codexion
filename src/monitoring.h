/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:48:41 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/13 11:12:04 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITORING_H
# define MONITORING_H

# include "codexion.h"
# include "utils/mutex.h"

void	*monitoring(void *arg);
int		cut_everything(pthread_t *threads, t_data *data,
			pthread_t *monitoring_thread, int code);

#endif
