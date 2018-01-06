#include <unistd.h>

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        ft_putchar(str[i]);
        i++;
    }
}

int     brackets(char *s1)
{
    int n;
    int i;
    int k;
    int flag;
    char *tmp;
    char str[128];
    
    n = 0;
    i = 0;
    k = 0;
    tmp = 0;
    flag = 0;

    while (s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    str[i] = '\0';

    i = 0;
    while (str[n])
    {
      n++;
        while (str[i])
        {
            if (str[i] == '(' || str[i] == '{' || str[i] == '[')
            {
                if (str[i] == '(')
                    tmp = &str[i];
                if (str[i] == '{')
                    tmp = &str[i];
                if (str[i] == '[')
                    tmp = &str[i];
                k = i;
                if (flag == 0)
                    flag = 1;
            }
            i++;
        }

        while (str[k])
        {
            if (str[k] == ')' || str[k] == '}' || str[k] == ']')
            {
                if (flag == 1)
                    flag = 2;
                else 
                    flag = 1;
                if (tmp != 0)
                    if (*tmp + str[k] == 81 || *tmp + str[k] == 184 || *tmp + str[k] == 248)
                        break ; 
                if (str[k] == 41 || str[k] == 93 || str[k] == 125)
                    return (0);
            }
            k++;
        }
        if (flag == 2)
        {
          str[k] = ' ';
          if (tmp != 0)
             *tmp = ' ';
          n = 0;
          i = 0;
          k = 0;
          tmp = 0;
          flag = 0;
        }
        else if (flag == 1)
            return (0);
    }
    return (1);
}

int     main(int argc, char **argv)
{
    int i;

    i = 1;
    if (argc > 1)
    {
        while (i < argc)
        {
            if (brackets(argv[i]))
                ft_putstr("OK\n");     
            else
               ft_putstr("Error\n");
            i++;
        }
    }
    return (0);
}



