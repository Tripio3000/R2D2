#include "../includes/ft_printf.h"

void	flags(char *format, t_struct *st, va_list ap)
{
	while (format[st->i] >= 32 && format[st->i] <= 48)
	{
		printf("st->i = %d\n", st->i);
		if (format[st->i] == '+')
			st->f_plus = 1;
		else if (format[st->i] == '-')
			st->f_minus = 1;
		else if (format[st->i] == ' ')
			st->f_space = width(format, st);
		else if (format[st->i] == '#')
			st->f_resh = 1;
		else if (format[st->i] == '0')
			st->f_nul = width(format, st);
		st->i++;
	}
	length(format, st, ap);
}

void	ft_print(char *format, t_struct *st)
{
	st->i = st->i - 2;
	if (st->f_resh == 1)
	{
		if (format[st->i] == 'x')
			st->schet = st->schet + ft_putstr("0x");
		else if (format[st->i] == 'X')
			st->schet = st->schet + ft_putstr("0X");
		else
			st->schet = st->schet + ft_putstr("0");
	}
	if (st->f_nul > 0 && st->f_minus != 1)
		null_print(st);
	if (st->f_space == 1)
		space_print(st);
	st->schet = st->schet + ft_putstr(st->tmp);
	ft_free(st);
	st->i = st->i + 1;
}

void space_print(t_struct *st)
{
	int d;

	int a = ft_strlen(st->tmp);
	d = st->wdht - ft_strlen(st->tmp);
	while (d-- > 0)
		st->schet = st->schet + ft_putchar(' ');
}

int		width(char *format, t_struct *st)
{
	int		i;
	int		j;
	char	*wdht;

	i = st->i;
	j = 0;
	wdht = ft_memalloc(20);
	while (format[i] != '\0' && format[i] != '%')
	{
		if (format[i] >= 48 && format[i] <= 57)
		{
			wdht[j] = format[i];
			j++;
		}
		i++;
		if (format[i] == '.' || (format[i] > 96 && format[i] < 123)
		|| format[i] == 'X')
			break ;
	}
	st->i = st->i + j - 1;
	st->wdht = ft_atoi(wdht);
	return (1);
}

void	null_print(t_struct *st)
{
	int d;

	d = st->wdht - ft_strlen(st->tmp);
	while (d-- > 0)
		st->schet = st->schet + ft_putchar('0');
}

void	ft_free(t_struct *st)
{
	// free(st->tmp);
	st->f_plus = 0; // триггер
	st->f_minus = 0;
	st->f_space = 0;
	st->f_resh = 0;
	st->f_nul = 0;
	st->wdht = 0;
}