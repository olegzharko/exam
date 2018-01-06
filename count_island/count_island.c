#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


void		set_num(char *point, int length)
{
	if (*(point + 1))
			*point = '1';
	if (*(point + length))
		*point = '1';
}

void replace_figure(char *box, char number, int length, int map_size, int i)
{
	if (box[i] == 'X')
		box[i] = number;
	if (i > 1 && box[i - 1] == 'X')
	{
		box[i - 1] = number;
		replace_figure(box, number, length, map_size, i-1);
	}
	if (i > length && box[i - length] == 'X')
	{
		box[i - length] = number;
		replace_figure(box, number, length, map_size, i - length);
	}
	if (i < map_size - 1 && box[i + 1] == 'X')
	{
		box[i + 1] = number;
		replace_figure(box, number, length, map_size, i+1);
	}
	if (i < map_size - length && box[i + length] == 'X')
	{
		box[i + length] = number;
		replace_figure(box, number, length, map_size, i + length);
	}
}



void	creat_map(int fd)
{
	int i;
	int size;
	char buf;
	char tmp[65000];
	char *box;
	char number;
		int length;

	number = '0';
	i = 0;
	size = 0;
	while (1)
	{
		if (read(fd, &buf, 1))
		{
			tmp[i] = buf;
			size++;
		}
		else
			break ;
		printf("%c", buf);
		i++;
	}
	tmp[i] = '\0';

	printf("!!!!!!!!!!\n");

	box = (char *)malloc(sizeof(char) * size + 1);
	i = 0;
	length = 1;
	while (tmp[i++] != '\n')
		length++;
	i = 0;
	while (tmp[i])
	{
		box[i] = tmp[i];
		printf("%c", box[i]);
		i++;
	}
	printf("!!!!!!!!!!\n");

	box[i] = '\0';
	int j = 0;
	while (j < size)
	{

		replace_figure(box++, number++, length, size, j);
		j++;
	}
}

int main(int argc, char **argv)
{
	int fd;

	fd = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		creat_map(fd);
	}
	write(1, "\n", 1);
	return (0);
}