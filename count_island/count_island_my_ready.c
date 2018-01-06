/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/30 16:27:46 by exam              #+#    #+#             */
/*   Updated: 2014/01/30 17:51:50 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	get_size(char *s, int *fd, int *size)
{
	char buf[1024];
	int i;
	int length;
	int ret;


	length = 0;
	i = 0;
	*fd = open(s, O_RDONLY);
	ret = read(*fd, buf, 1024);
	*size += ret;
	while (buf[i++] != '\n')
		++length;
	length++;
	close(*fd);
	return (length);
}


void find_island(char *map, int i, char num, int length, int size)
{
	if (i > size)
		return ;
	if (map[i] == 'X')
	{
		map[i] = num;
		find_island(map, i + 1, num, length, size);
		find_island(map, i + length , num, length, size);
		find_island(map, i - 1, num, length, size);
		find_island(map, i - length, num, length, size);
	}
}

void print_map(char *map, int length, int size)
{
	int i;
	char num;

	printf("%d\n", size);
	i = -1;
	num = '0';
	while (++i < size)
	{
		if (map[i] == 'X')
		{
			find_island(map, i, num, length, size);
			num = num + 1;
		}
	}
	write(1, map, size);
	if (map)
		free(map);
}

int	count_island(char *s)
{
	char *map;
	int size;
	int fd;
	int length;

	size = 0;
	if ((length = get_size(s, &fd, &size)) == 0)
		return (0);
	fd = open(s, O_RDONLY);
	if (!(map = (char *)malloc(sizeof(char) * (size + 1))))
		return (0);
	map[size] = '\0';
	read(fd, map, size);
	print_map(map, length, size);
	close(fd);
	return (0);
}

int main(int argc, char **argv)
{
	if (argc == 2)
		count_island(argv[1]);
	write(1, "\n", 1);
	return (0);
}