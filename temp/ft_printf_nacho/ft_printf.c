#include <unistd.h>
#include <stdarg.h>

void put_str(char *str, int *len)
{
	if (!str)
		str = "(null)";
	while (*str)
		*len += write(1, str++, 1);
}

void put_digit(long long int num, int base, int *len)
{
	char *hex = "0123456789abcdef";

	if (num < 0)
	{
		num *= -1;
		*len += write(1, "-", 1);
	}
	if (num >= base)
		put_digit((num / base), base, len);
	*len += write(1, &hex[num % base], 1);
}

int ft_printf(const char *format, ...)
{
	int len = 0;
	va_list ptr;

	va_start(ptr, format);

	while (*format)
	{
		if ((*format == '%') && (
					(*(format + 1) == 's') ||
					(*(format + 1) == 'd') ||
					(*(format + 1) == 'x')))
		{
			format++;
			if (*format == 's')
				put_str(va_arg(ptr, char *), &len);
			else if (*format == 'd')
				put_digit((long long int)va_arg(ptr, int), 10, &len);
			else if (*format == 'x')
				put_digit((long long int)va_arg(ptr, unsigned int), 16, &len);
		}
		else
			len += write(1, format, 1);
		format++;
	}
	return (va_end(ptr), len);
}

#include <stdio.h>

int main(void)
{
	ft_printf("%s\n", "toto");
	ft_printf("Magic %s is %d\n", "number", 42);
	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
	ft_printf("\n");
	printf("orig:\n%s\n", "toto");
	printf("orig:\nMagic %s is %d\n", "number", 42);
	printf("orig:  \nHexadecimal for %d is %x\n", 42, 42);
}
