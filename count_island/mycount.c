/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mycount.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozharko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 08:21:47 by ozharko           #+#    #+#             */
/*   Updated: 2017/12/07 08:21:50 by ozharko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int 	get_size(char *s, int *fd, int *size)
{
	int lenth;
	int line;
	int ret;
	int i;
	char buf[1024];

	lenth = 0;
	line = 0;
	ret = 0;
	i = 0;
	if (!(*fd = open(s, O_RDONLY)))
		return (0);
	if (!(ret = read(*fd, buf, 1024)))
		return (0);
	buf[ret] = '\0';
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			line++;
			lenth = i / line;
		}
		i++;
	}
	*size += ret;
	close(*fd);
	return (lenth);
}

void	put_num(char *map, int index, int size, int size_length, char num)
{
	if (index > size)
		return ;
	if (map[index] == 'X')
	{
		map[index] = num;
		put_num(map, index + 1, size, size_length, num);
		put_num(map, index + size_length + 1, size, size_length, num);
		put_num(map, index - 1, size, size_length, num);
		put_num(map, index - size_length - 1, size, size_length, num);
	}
}

void 	print_island(char *map, int size, int size_length)
{
	int i;
	char num;

	i = 0;
	num = '0';
	while(map[i])
	{
		if (map[i] == 'X')
		{
			put_num(map, i, size, size_length, num);
			num = num + 1;
		}
		i++;
	}
	write(1, map, size);
}

void	count_island(char *s)
{
	int fd;
	int size;
	int size_length;
	char *map;

	size = 0;
	if ((size_length = get_size(s, &fd, &size)) == 0)
		return ;
	printf("size = %d, size_length = %d, fd = %d\n", size, size_length, fd);
	if (!(map = (char *)malloc(sizeof(char ) * (size + 1))))
		return ;
	if (!(open(s, O_RDONLY)))
		return ;
	if (!(read(fd, map, size)))
		return ;
	print_island(map, size, size_length);
	if (map)
	{
		close(fd);
		free(map);
	}
}

int	main(int argc, char **argv)
{
	if (argc == 2)
		count_island(argv[1]);
	write(1, "\n", 1);
	return (0);
}







