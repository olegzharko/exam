#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	my_putchar(char c);
int		my_strlen(char *str);

char	*my_alloc(int len)
{
	char *res;
	int i;

	res = 0;
	res = (char *)malloc(sizeof(char) * len);
	i = 0;
	while (i < len)
		res[i++] = '\0';
	return (res);
}

void	make_num(char *str, int len)
{
	int i;

	i = 0;
	while (i < len)
		str[i++] -= '0';
}

void	make_str(char *str, int len)
{
	int i;
	int zero;

	zero = 0;
	i = 0;
	while (i < len)
	{
		if (zero || str[i] != 0 || i + 1 == len)
		{
			my_putchar(str[i] + '0');
			zero = 1;
		}
		i++;
	}
	free(str);
}

void	my_putchar(char c)
{
	write(1, &c, 1);
}

int		my_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	infin_sub(char *str1, char *str2)
{
	int len1;
	int len2;
	int pos;
	char *res;

	len1 = my_strlen(str1);
	len2 = my_strlen(str2);
	res = my_alloc(len1);
	make_num(str1, len1);
	make_num(str2, len2);
	pos = len1 - 1;
	len2--;
	while (pos >= 0)
	{
		res[pos] += (len2 < 0 ? 0 : str2[len2]);
		if (str1[pos] < res[pos])
		{
			str1[pos] += 10;
			res[pos - 1] = 1;
		}
		res[pos] = str1[pos] - res[pos];
		len2--;
		pos--;
	}
	make_str(res, len1);
}

void	infin_add(char *str1, char *str2)
{
	int len1;
	int len2;
	int str_len;
	int pos;
	char *res;

	len1 = my_strlen(str1);
	len2 = my_strlen(str2);
	res = my_alloc(len1 + 1);
	make_num(str1, len1);
	make_num(str2, len2);
	str_len = len1;
	pos = len1;
	len1--;
	len2--;
	while (pos > 0)
	{
		res[pos] += str1[len1] + (len2 < 0 ? 0 : str2[len2]);
		res[pos - 1] = res[pos] / 10;
		res[pos] = res[pos] % 10;
		pos--;
		len1--;
		len2--;
	}
	make_str(res, str_len + 1);
}

int		my_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	if (my_strlen(s1) < my_strlen(s2))
		return (-1);
	if (my_strlen(s1) > my_strlen(s2))
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int		manage_sign(char **s1, char **s2)
{
	int neg1;
	int neg2;
	int res;
	char *tmp;

	neg1 = **s1 == '-' ? 1 : 0;
	neg2 = **s2 == '-' ? 1 : 0;
	*s1 = &((*s1)[neg1]);
	*s2 = &((*s2)[neg2]);
	if ((res = my_strcmp(*s1, *s2)) == 0)
		return (neg1 == neg2);
	if (res < 0)
	{
		tmp = *s1;
		*s1 = *s2;
		*s2 = tmp;
		if (neg2)
			my_putchar('-');
	}
	else if (neg1)
		my_putchar('-');
	return (neg1 == neg2);
}

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		if (manage_sign(&argv[1], &argv[2]))
			infin_add(argv[1], argv[2]);
		else
			infin_sub(argv[1], argv[2]);
	}
	write(1, "\n", 1);
	return (0);
}