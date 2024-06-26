/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_and_getters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:03:32 by omougel           #+#    #+#             */
/*   Updated: 2024/06/21 09:58:40 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	set_or_get_bool(t_flag flag, t_mtx *mutex, bool *val, bool new_val)
{
	bool	ret;

	safe_mutex_handler(mutex, LOCK);
	if (flag == SET)
		*val = new_val;
	ret = *val;
	safe_mutex_handler(mutex, UNLOCK);
	return (ret);
}

long	set_or_get_long(t_flag flag, t_mtx *mutex, long *val, long new_val)
{
	long	ret;

	safe_mutex_handler(mutex, LOCK);
	if (flag == SET)
		*val = new_val;
	ret = *val;
	safe_mutex_handler(mutex, UNLOCK);
	return (ret);
}

bool	simulation_finnished(t_table *table)
{
	return (set_or_get_bool(GET, &table->table_mutex, &table->end_simulation,
			-1));
}
