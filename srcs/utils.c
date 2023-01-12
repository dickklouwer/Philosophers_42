/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 12:17:32 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/01/12 13:55:01 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void print_log(t_philo *philo, int state)
{
	uint64_t time;
	
	time = (get_current_time() - philo->data->start_time);
	if (state == EATING)
	{
		philo->must_eat--;
		philo->time_last_eat = get_current_time();
		printf("%llu Philosopher %d is eating\n", time, philo->id);
	}
	if (state == FORK)
		printf("%llu Philosopher %d picked up a fork\n", time, philo->id);
	if (state == SLEEPING)
		printf("%llu Philosopher %d is sleeping\n", time, philo->id);
	if (state == THINKING)
		printf("%llu Philosopher %d is thinking\n", time, philo->id);
	if (state == DIED)
		printf("%llu Philosopher %d died\n");
	pthread_mutex_unlock(philo->data->write_mutex);
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