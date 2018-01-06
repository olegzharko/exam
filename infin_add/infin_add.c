#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


void  my_putchar(char c); 
int my_strlen(char *str);

char	*my_alloc(int len)
{
  char	*to_alloc;
  int	i;

  if ((to_alloc = (char *) malloc(len * sizeof(char))) == NULL)
    exit(write(1, "malloc failed\n", my_strlen("malloc failed\n")));
  i = 0;
  while (i < len)
    to_alloc[i++] = '\0';
  return (to_alloc);
}

void	string_to_val(char *str, int len)
{
  int	i;

  i = 0;
  while (i < len)
    str[i++] -= '0';
}

void show_result_to_char(char *str, int len)
{
  int	zero;
  int	i;

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

void infin_sub(char *s1, char *s2)
{
  char	*result;
  int	len1;
  int	len2;
  int	pos;

  len1 = my_strlen(s1);
  len2 = my_strlen(s2);
  result = my_alloc(len1);
  string_to_val(s1, len1);
  string_to_val(s2, len2);
  pos = len1 - 1;
  len2--;
  while (pos >= 0)
    {
      result[pos] += (len2 < 0 ? 0 : s2[len2]);
      if (s1[pos] < result[pos])
	{
	  s1[pos] += 10;
	  result[pos - 1] = 1;
	}
      result[pos] = s1[pos] - result[pos];
      pos--;
      len2--;
    }
  show_result_to_char(result, len1);
}

void infin_add(char *s1, char *s2)
{
	int	len1;
	int	len2;
	int	save_len;
	int	pos;
	char	*result;

	len1 = my_strlen(s1);
	len2 = my_strlen(s2);
	result = my_alloc(len1 + 1);
	string_to_val(s1, len1);
	string_to_val(s2, len2);
	save_len = len1;
	pos = len1;
	len1--;
	len2--;
	while (pos > 0)
    {
      result[pos] += s1[len1] + (len2 < 0 ? 0 : s2[len2]);
      result[pos - 1] = result[pos] / 10;
      result[pos] = result[pos] % 10;
      pos--;
      len1--;
      len2--;
    }
  show_result_to_char(result, save_len + 1);
}


void  my_putchar(char c)
{
  write(1, &c, 1);
}

int my_strlen(char *str)
{
  int i;

  i = 0;
  while (str[i])
    i++;
  return (i);
}

int my_strcmp(char *s1, char *s2)
{
  int i;

  if (my_strlen(s1) < my_strlen(s2))
    return (-1);
  if (my_strlen(s1) > my_strlen(s2))
    return (1);
  i = 0;
  while (s1[i] && s2[i] && s1[i] == s2[i])
    i++;
  return (s1[i] - s2[i]);
}

int manage_sign(char **s1, char **s2)
{
  int neg1;
  int neg2;
  int res;
  char  *tmp;

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

int main(int ac, char **av)
{
  if (ac == 3)
    {
      if (manage_sign(&av[1], &av[2]))
           infin_add(av[1], av[2]);
      else
         infin_sub(av[1], av[2]);
    }
  my_putchar('\n');
  return (0);
}
