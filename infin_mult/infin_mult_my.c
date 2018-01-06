#include <stdlib.h>
#include <unistd.h>

#define END_OF_STRING -1;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_bzero(char *str, int size)
{
	int i;

	i = 0;
	while (i < size)
		str[i++] = 0;
}

void	print(char *res)
{
	while (*res == 0)
		res++;
	while (*res != END_OF_STRING)
	{
		ft_putchar(*res + '0');
		res++;
	}
}

void	add(char *res, int len1, int len2, char c1, char c2)
{
	int curr_i;
	int prev_i;

	curr_i = len1 + len2 + 1;
	prev_i = len1 + len2;
	res[curr_i] += (c1 - '0') * (c2 - '0');
	res[prev_i] += res[curr_i] / 10;
	res[curr_i] %= 10;
}

char	*mult(char *str1, char *str2)
{
	char *res;
	int res_size;
	int len2_save;
	int len1;
	int len2;

	res_size = ft_strlen(str1) + ft_strlen(str2);
	res = (char *)malloc(sizeof(char) * (res_size + 1));
	ft_bzero(res, res_size + 1);
	res[res_size] = END_OF_STRING;
	len1 = ft_strlen(str1) - 1;
	len2 = ft_strlen(str2) - 1;
	len2_save = len2;
	while (len1 >= 0)
	{
		len2 = len2_save;
		while (len2 >= 0)
		{
			add(res, len1, len2, str1[len1], str2[len2]);
			len2--;
		}
		len1--;
	}
	return (res);
}

void	mult_wrapper(char *str1, char *str2)
{
	int neg;

	if (str1[0] == 0 || str2[0] == 0 || str1[0] == '0' || str2[0] == '0')
	{
		write(1, "0", 1);
		return ;
	}
	neg = 0;
	if (str1[0] == '-')
	{
		neg = 1;
		str1++;
	}
	if (str2[0] == '-')
	{
		neg = 1;
		str2++;
	}
	if (neg)
		write(1, "-", 1);
	print(mult(str1, str2));
}

int		main(int argc, char **argv)
{
	if (argc == 3)
		mult_wrapper(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}