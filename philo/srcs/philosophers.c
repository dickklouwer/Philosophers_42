/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/04 15:05:22 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/01/19 13:49:34 by tklouwer      ########   odam.nl         */
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
        p_sleep(philo->data, 10);
    while (1)
    {
        eating(philo);
        philo_sleep(philo);
        thinking(philo);
        if (philo->done)
            break ;
    }
    return (EXIT_SUCCESS);
}

int philo_threads(t_data *data)
{
    long long int i;

    i = 0;
    data->finished = 0;
    data->start_time = get_current_time();
    while (i < data->num_philos)
    {
        data->philo[i].time_last_eat = data->start_time;
        if (pthread_create(data->philo[i].philo_t, NULL, &philo, &data->philo[i]))
        {
            data->finished = 1;
            return (EXIT_FAILURE);
        }
        i++;
    }
    died(data);
    return (EXIT_SUCCESS);
}