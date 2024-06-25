/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:27:52 by rparodi           #+#    #+#             */
/*   Updated: 2024/06/09 18:27:02 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static t_i32	ft_check_space(t_i32 c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static t_i32	ft_check_sign(const char *nptr, t_i32 *i)
{
	while (ft_check_space(nptr[*i]))
		(*i)++;
	if (nptr[*i] == '-')
	{
		(*i)++;
		return (-1);
	}
	else if (nptr[*i] == '+')
		(*i)++;
	return (1);
}

t_error	ft_atou(const char *nptr, t_usize *value)
{
	t_i32	i;
	t_i32	sign;

	i = 0;
	sign = ft_check_sign(nptr, &i);
	(*value) = 0;
	if (sign != 1)
		ft_exit("Negative number if find !\n", ERROR);
	while (nptr[i])
	{
		if (nptr[i] >= '0' && nptr[i] <= '9')
			(*value) = ((*value) * 10) + nptr[i] - '0';
		else
			break ;
		i++;
	}
	return (NO_ERROR);
}

t_usize	ft_atou_return(t_str str)
{
	t_usize	number;

	number = 0;
	ft_atou(str, &number);
	return (number);
}
