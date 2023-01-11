/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/04 15:05:22 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/01/11 15:35:44 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    *philo(void *philosopher)
{
    t_philo *philo;
    t_data *data;

    philo = (t_philo *)philosopher;
    data = philo->data;
    if (philo->id % 2 == 0)
    {
        p_sleep(philo, 100, 0);
    }
    while (philo->done == 0)
    {
        if (eating(philo))
            break ;
        p_sleep(philo, data->time_to_sleep, SLEEPING);
        thinking(philo);
    }
}

int philo_threads(t_data *data)
{
    int i;

    i = 0;
    data->start_time = get_current_time();
    while (i < data->num_philos)
    {
        data->philo[i].time_last_eat = data->start_time;
        if (pthread_create(data->philo_t, NULL, &philo, &data->philo[i]))
            return (EXIT_FAILURE);
        i++;
    }
}