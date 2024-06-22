/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:51:24 by omougel           #+#    #+#             */
/*   Updated: 2024/06/22 11:40:11 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	thinking(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}

static void	eat(t_philo	*philo)
{
	safe_mutex_handler(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handler(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_or_get_long(SET, &philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limits_meals > 0 && philo->meals_counter == philo->table->nbr_limits_meals)
		set_or_get_bool(SET, &philo->philo_mutex, &philo->full, true);
	safe_mutex_handler(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handler(&philo->second_fork->fork, UNLOCK);
}


void  *dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	while (!simulation_finnished(philo->table))
	{
		if (philo->full) // TODO thread safe
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo);
	}
	return (NULL);
}

void  dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limits_meals == 0)
		return ;
	if (table->philo_nbr == 1)
		;
	else
	{
		while (++i < table->philo_nbr)
		{
			safe_thread_handler(&table->philos[i].thread_id, dinner_simulation,
					   &table->philos[i], CREATE);
		}
	}
	table->start_simulation = gettime(MILLISECOND);
	set_or_get_bool(SET, &table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handler(&table->philos[i].thread_id, NULL, NULL, JOIN);

}
