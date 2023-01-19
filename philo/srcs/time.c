/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/04 14:54:24 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/01/19 13:37:23 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static u_int64_t	sec_to_millisec(u_int64_t sec)
{
	u_int64_t	millisec;

	millisec = sec * 1000;
	return (millisec);
}

static u_int64_t	microsec_to_millisec(u_int64_t microsec)
{
	u_int64_t	millisec;

	millisec = microsec / 1000;
	return (millisec);
}

u_int64_t	get_current_time(void)
{
	struct timeval	tv;
	u_int64_t		cur_time_ms;

	gettimeofday(&tv, NULL);
	cur_time_ms = (u_int64_t)sec_to_millisec(tv.tv_sec) + \
	microsec_to_millisec(tv.tv_usec);
	return (cur_time_ms);
}

void p_sleep(t_data *data, long long ms)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    while(1)
    {
        gettimeofday(&end, NULL);
        if ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000 >= ms)
            return;
        if (data->num_philos < 100)
			usleep(100);
		else
			usleep(1000);
    }
}

// void	sleeper(t_env *env, u_int64_t ms)
// {
// 	u_int64_t	timestamp_tmp;
// 	u_int64_t	time_diff;

// 	timestamp_tmp = get_current_time();
// 	time_diff = 0;
// 	while (time_diff < ms)
// 	{
// 		time_diff = get_current_time() - timestamp_tmp;
// 		pthread_mutex_lock(&env->print_mutex);
// 		if (!env->continue_dinner)
// 		{
// 			pthread_mutex_unlock(&env->print_mutex);
// 			break ;
// 		}
// 		pthread_mutex_unlock(&env->print_mutex);
// 		if (env->n_philos < 100)
// 			usleep(100);
// 		else
// 			usleep(1000);
// 	}
// }
