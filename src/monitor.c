/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:21:10 by omougel           #+#    #+#             */
/*   Updated: 2024/09/21 15:35:03 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (set_or_get_bool(GET, &philo->philo_mutex, &philo->full, -1))
		return (false);
	elapsed = gettime(MILLISECOND) - set_or_get_long(GET, &philo->philo_mutex,
			&philo->last_meal_time, -1);
	t_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex, &table->thread_running_nbr,
			table->philo_nbr))
		usleep(200);
	while (!simulation_finnished(table))
	{
		i = -1;
		while (++i < table->philo_nbr)
		{
			if (philo_died(table->philos + i) && !simulation_finnished(table))
			{
				set_or_get_bool(SET, &table->table_mutex,
					&table->end_simulation, true);
				write_status(DIED, table->philos + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}
