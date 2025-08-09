#include "philo.h"
#include <stdio.h>

void	test_atosize(void)
{
    const char *tests[] = {
        "42",
        "   123",
        "+456",
	"+ 457",
        "18446744073709551615", // max size_t on 64-bit
        "18446744073709551616", // overflow
        "12abc",
        "  789  ",
        "",
	"     ",
	"	123",
	"123	",
	"+",
        NULL
    };

    size_t value;
    int i = 0;

    while (tests[i])
    {
        int res = ft_atosize(tests[i], &value);
        if (res)
            printf("Input: '%s' -> Success: %zu\n", tests[i], value);
        else
            printf("Input: '%s' -> Failure: Invalid or out of range\n", tests[i]);
        i++;
    }
}

void	test_safe_atoi(void)
{
    const char *tests[] = {
        "42",
        "   123",
        "+456",
	"+ 457",
        "2147483647",
        "2147483648", // overflow
        "-2147483648",
        "-2147483649", // underflow
        "12abc",
        "  789  ",
        "",
	"     ",
	"	123",
	"123	",
	"+",
        NULL
    };

    int value;
    int i = 0;

    while (tests[i])
    {
        int res = ft_safe_atoi(tests[i], &value);
        if (res)
            printf("Input: '%s' -> Success: %d\n", tests[i], value);
        else
            printf("Input: '%s' -> Failure: Invalid or out of range\n", tests[i]);
        i++;
    }
}

int	main(void)
{
	test_atosize();
	test_safe_atoi();
	return(0);
}
