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

// integration test
void	test_args()
{
	t_args	args;
	pthread_mutex_t	*cs;

	typedef struct s_test_case
	{
		int	ac;
		char *av[6];
	}	t_test_case;

	static t_test_case tests[] =
	{
		{5, {"philo", "4", "800", "200", "200"}},
		{6, {"philo", "4", "800", "200", "200", "3"}},
	};
	int	num_test = sizeof(tests) / sizeof(tests[0]);
	int	i = 0;
	while (i < num_test)
	{
		printf("Running test case %d:\n", i + 1);
		if (parse_init_args(tests[i].ac, tests[i].av, &args) != 0)
		{
			print_usage();
			printf("parse_init_args failed\n");
			return ;
		}
		if (validate_args(&args) != 0)
		{
			print_usage();
			printf("validate_args failed\n");
			return ;
		}
		if (init_chopsticks(&cs, args.philos) != 0)
		{
			printf("init_chopsticks failed\n");
			return ;
		}
		printf("number of philos: %d\n", args.philos);
		printf("time_til_death in ms: %zu\n", args.time_til_death);
		printf("eat_time in ms: %zu\n", args.eat_time);
		printf("sleep_time in ms: %zu\n", args.sleep_time);
		if (tests[i].ac == 6)
			printf("meal_goal: %d\n", args.meal_goal);
		i++;
	}
}

int	main(void)
{
//	test_atosize();
//	test_safe_atoi();
	test_args();
	return(0);
}
