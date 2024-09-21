/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:51:24 by omougel           #+#    #+#             */
/*   Updated: 2024/09/21 15:35:00 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdbool.h>

void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		write_status(THINKING, philo, DEBUG_MODE);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = 2 * t_eat - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

static void	*one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_or_get_long(SET, &philo->philo_mutex, &philo->last_meal_time,
		gettime(MILLISECOND));
	increase_long(&philo->philo_mutex, &philo->table->thread_running_nbr);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_finnished(philo->table))
		usleep(200);
	return (NULL);
}
/*
static void	eat(t_philo	*philo)
{
	safe_mutex_handler(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handler(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_or_get_long(SET, &philo->philo_mutex, &philo->last_meal_time,
		gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limits_meals > 0
		&& philo->meals_counter == philo->table->nbr_limits_meals)
		set_or_get_bool(SET, &philo->philo_mutex, &philo->full, true);
	safe_mutex_handler(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handler(&philo->second_fork->fork, UNLOCK);
}*/

static void	eat(t_philo	*philo)
{
	while (set_or_get_bool(GET, &philo->first_fork->fork, &philo->first_fork->status, -1) == false)
		usleep(200);
	set_or_get_bool(SET, &philo->first_fork->fork, &philo->first_fork->status, false);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (set_or_get_bool(GET, &philo->second_fork->fork, &philo->second_fork->status, -1) == false)
		usleep(200);
	set_or_get_bool(SET, &philo->second_fork->fork, &philo->second_fork->status, false);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_or_get_long(SET, &philo->philo_mutex, &philo->last_meal_time,
				 gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limits_meals > 0 && philo->meals_counter == philo->table->nbr_limits_meals)
		set_or_get_bool(SET, &philo->philo_mutex, &philo->full, true);
	set_or_get_bool(SET, &philo->first_fork->fork, &philo->first_fork->status, true);
	set_or_get_bool(SET, &philo->second_fork->fork, &philo->second_fork->status, true);
}

void  *dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_or_get_long(SET, &philo->philo_mutex, &philo->last_meal_time,
		gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->thread_running_nbr);
	de_synchronize_philos(philo);
	while (!simulation_finnished(philo->table))
	{
		if (set_or_get_bool(GET, &philo->philo_mutex, &philo->full, -1))
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limits_meals == 0)
		return ;
	if (table->philo_nbr == 1)
		safe_thread_handler(&table->philos[0].thread_id, one_philo,
			&table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_nbr)
		{
			safe_thread_handler(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
		}
	}
	safe_thread_handler(&table->monitor, monitor_dinner, table, CREATE);
	table->start_simulation = gettime(MILLISECOND);
	set_or_get_bool(SET, &table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handler(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_or_get_bool(SET, &table->table_mutex, &table->end_simulation, true);
	safe_thread_handler(&table->monitor, NULL, NULL, JOIN);
}
