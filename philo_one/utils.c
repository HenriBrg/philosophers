/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:23:05 by henri             #+#    #+#             */
/*   Updated: 2020/03/27 17:34:03 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		putuint64_t(int fd, uint64_t timer)
{
	int		i;
	char	tmp[15];

	if (timer == 0)
		tmp[0] = '0';
	i = 0;
	while (timer != 0)
	{
		tmp[i++] = '0' + (timer % 10);
		timer /= 10;
	}
	i = (i > 0) ? i - 1 : i;
	while (i >= 0)
		write(fd, &tmp[i--], 1);
}

/*
**	man gettimeofday
**	tv_sec = seconds since Jan. 1, 1970
**	tv_usec = microseconds left (need to / 1000 for miliseconds)
*/

uint64_t	chrono(void)
{
	uint64_t		time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec) * (uint64_t)1000 + (tv.tv_usec / 1000);
	return (time);
}

void	putstrfd(char *str, int fd)
{
	while (str)
	{
		write(fd, str, 1);
		str++;
	}
}

int		ft_atoi(char *str)
{
	int		i;
	int		sign;
	int		result;

	i = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
