/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 10:04:38 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/04 14:15:28 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	free_all(t_data data, pthread_t* threads)
{
	free(threads);
	free(data.coders);
	free(data.available_dongle);
	return ;
}
