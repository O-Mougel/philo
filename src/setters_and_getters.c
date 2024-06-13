/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_and_getters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:03:32 by omougel           #+#    #+#             */
/*   Updated: 2024/06/13 17:09:26 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	set_or_get_bool(t_flag flag, t_mtx *mutex, bool *val, bool new_val)
{
	bool	ret;

	pthread_mutex_lock(mutex);
	if (flag == SET)
		*val = new_val;
	ret = *val;
	pthread_mutex_unlock(mutex);
	return (ret);
}

long	set_or_get_long(t_flag flag, t_mtx *mutex, long *val, long new_val)
{
	long	ret;

	pthread_mutex_lock(mutex);
	if (flag == SET)
		*val = new_val;
	ret = *val;
	pthread_mutex_unlock(mutex);
	return (ret);
}
