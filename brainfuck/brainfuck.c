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

#include <unistd.h>
#include <stdlib.h>

char	*brainfuck(char *str)
{
	int i;
	int loop;
	char *ptr;

	i = 0;
	loop = 0;
	ptr = (char *)malloc(sizeof(char ) * 2050);
	while (i < 2050)
		ptr[i++] = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
			ptr++;
		else if (str[i] == '<')
			ptr--;
		else if (str[i] == '+')
			(*ptr)++;
		else if (str[i] == '-')
			(*ptr)--;
		else if (str[i] == '.')
			write(1, ptr, 1);
		else if (str[i] == '[')
		{
			if (*ptr == 0)
			{
				loop = 0;
				while (str[i])
				{
					if (str[i] == '[')
						loop++;
					if (str[i] == ']')
						loop--;
					if (loop == 0)
						break ;
					i++;
				}
			}
		}
		else if (str[i] == ']')
		{
			if (*ptr != 0)
			{
				loop = 0;
				while (str[i])
				{
					if (str[i] == '[')
						loop++;
					if (str[i] == ']')
						loop--;
					if (loop == 0)
						break ;
					i--;
				}
			}
		}
		i++;
	}
	return (str);
} 

int main(int argc, char **argv)
{
	if (argc == 2)
		brainfuck(argv[1]);
	else
		write(1, "\n", 1);
	return (0);
}