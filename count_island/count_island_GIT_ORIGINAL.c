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

int			get_size(char *s, int *fd, int *size)
{
	char	buf[1024];
	int		ln1;
	int 	ln2;
	int		ret;
	int		i;


	ln1 = 0;
	ln2 = 0;
	if (!s || (*fd = open(s, O_RDONLY)) < 0)
		return (0);
	if ((ret = read(*fd, buf, 1024)))
	{
		i = -1;
		while (++i < ret)
		{
			if (buf[i] == '\n')
			{
				if (i > 1024)
					return (0);
				if (ln1)
					ln1 = i / (ln2 + 1);
				else
					ln1 = i;
				ln2++;
			}
		}
		*size += ret;
	}
	close(*fd);
	return (ln1);
}

void		find_island(char *map, int index, int s_sl[2], char nbr)
{
	if (index > s_sl[0])
		return ;
	if (map[index] == 'X')
	{
		map[index] = nbr;
		find_island(map, index + 1, s_sl, nbr);
		find_island(map, index + s_sl[1] + 1, s_sl, nbr);
		find_island(map, index - 1, s_sl, nbr);
		find_island(map, index - s_sl[1] - 1, s_sl, nbr);
	}
}

void		print_island(char *map, int size_line, int size)
{
	int		s_sl[2];
	int		i;
	char	nbr;

	nbr = '0';
	i = -1;
	s_sl[0] = size;
	s_sl[1] = size_line;
	while (++i < size)
	{
		if (map[i] == 'X')
		{
			find_island(map, i, s_sl, nbr);
			nbr = nbr + 1;
		}
	}
	write(1, map, size);
	if (map)
		free(map);
}

int			count_island(char *s)
{
	char	*map;
	int		size;
	int		fd;
	int		size_line;

	size = 0;
	if ((size_line = get_size(s, &fd, &size)) == 0)
		return (0);
	if (!size)
		return (0);
	if ((fd = open(s, O_RDONLY)) < 0)
		return (0);
	if (!(map = (char *)malloc(sizeof(char) * (size + 1))))
		return (0);
	map[size] = '\0';
	if ((read(fd, map, size)) < 0)
		return (0);
	print_island(map, size_line, size);
	close(fd);
	return (1);
}

int			main(int argc, char ** argv)
{
	if (argc == 2)
	{
		if (count_island(argv[1]) == 0)
			write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
		return (0);
}