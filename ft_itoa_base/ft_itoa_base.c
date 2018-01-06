/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozharko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 07:45:57 by ozharko           #+#    #+#             */
/*   Updated: 2017/11/30 09:21:54 by ozharko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
	как переводить минусовые числа при других системах счисления -1000 16 = 3E8 или NULL 
*/


#include <stdio.h>
#include <stdlib.h>

int			ft_length(int value, int base)
{
	int 	i;
	
	i = 0;
	if (value < 0 && base == 10)
		i++;
	while (value)
	{
		value = value / base;
		i++;
	}
	return (i);
}

char		*ft_itoa_base(int value, int base)
{
	int		i;
	int		check;
	char	*num;
	char	*str;
	int		length;

	num = "0123456789ABCDEF";
	length = ft_length(value, base);
	if (value < 0 && base == 10)
		value = value * (-1);
	str = (char *)malloc(sizeof(char) * (length + 1));
	str[length] = '\0';
	i = 0;
	while (value)
	{
		length--;
		str[length] = num[value % base];
		value = value / base;
		i++;
	}
	if (length != 0)
		str[--length] = '-';
	return (str);
}

int			main(int argc, char **argv)
{
	if (argc == 3)
	{
		printf("value = %d, base = %d\n", atoi(argv[1]), atoi(argv[2]));
		printf("result = %s\n", ft_itoa_base(atoi(argv[1]), atoi(argv[2])));
	}
	return (0);
}
