/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:18:22 by omougel           #+#    #+#             */
/*   Updated: 2024/06/13 07:58:24 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static inline bool	is_space(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static long	ft_atol(const char *str)
{
	int		i;
	long	number;

	i = 0;
	number = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		error_exit(RED"Enter only positive values !"RST);
	if (!is_digit(str[i]))
		error_exit(RED"The input is not a correct digit"RST);
	while (is_digit(str[i]))
	{
		if (number > INT_MAX)
			break ;
		number = number * 10 + (str[i++] - 48);
	}
	if (number > INT_MAX)
		error_exit(RED"The value is too big, INT_MAX is the limit"RST);
	return (number);
}

void	parse_input(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error_exit(RED"Use timestamps major than 60ms"RST);
	if (argv[5])
		table->nbr_limits_meals = ft_atol(argv[5]);
	else
		table->nbr_limits_meals = -1;
}
