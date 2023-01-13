/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 12:17:32 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/01/13 15:16:10 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int print_log(t_philo *philo, int state)
{
	uint64_t time;
	
	pthread_mutex_lock(philo->data->write_mutex);
	time = (get_current_time() - philo->data->start_time);
	if (state == DIED)
	{
		printf("%llu Philosopher %d died...\n", time, philo->id);
		pthread_mutex_unlock(philo->data->write_mutex);
		return (1);
	}
	else if (state == EATING)
	{
		philo->must_eat--;
		printf("%llu Philosopher %d is eating\n", time, philo->id);
	}
	else if (state == FORK)
		printf("%llu Philosopher %d picked up a fork\n", time, philo->id);
	else if (state == SLEEPING)
		printf("%llu Philosopher %d is sleeping\n", time, philo->id);
	else if (state == THINKING)
		printf("%llu Philosopher %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(philo->data->write_mutex);
	return (0);
}

int only_num(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-')
		return (EXIT_FAILURE);
	while(str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}