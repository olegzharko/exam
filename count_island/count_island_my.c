#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void	count_island()

int	main(int argc, char **argv)
{
	if (argc == 2)
		count_island(argv[1]);
	write(1, "\n", 1);
	return (0);
}