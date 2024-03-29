/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 01:04:18 by akanbari          #+#    #+#             */
/*   Updated: 2023/09/30 07:47:44 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	invalid_base(char *base)
{
	int	i;
	int	result;

	result = 0;
	while (*base != '\0')
	{
		if (*base == '-' || *base == '+')
			return (0);
		if (*base == ' ' || (*base >= 9 && *base <= 13))
			return (0);
		i = result + 1;
		while (base[i] != '\0')
		{
			if (base[result] == base[i])
				return (0);
			i++;
		}
		result++;
	}
	if (result < 2)
		return (0);
	else
		return (result);
}

static int	get_value(char *base, char c)
{
	int	index;

	index = 0;
	while (base[index] != '\0')
	{
		if (base[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

static int	get_size(char *base)
{
	int	index;

	index = -1;
	while (base[++index] != '\0')
	{
		if (base[index] == '-' || base[index] == '+' || base[index] <= 32)
			return (0);
		if (base[index + 1] == base[index])
			return (0);
	}
	if (index < 2)
		return (0);
	return (index);
}

int	ft_atoi_base(char *str, char *base)
{
	int	result;
	int	helper;
	int	size;

	result = 0;
	helper = 1;
	size = get_size(base);
	if (invalid_base(base))
	{
		return (0);
	}
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			helper *= (-1);
		str++;
	}
	while (get_value(base, *str) != -1)
	{
		result = (result * size) + get_value(base, *str);
		str++;
	}
	return (result * helper);
}
