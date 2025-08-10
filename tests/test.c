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

//test int     parse_init_args(int ac, char **av, t_args *args)
void	test_parse_init_args()
{
	t_args	args;
	int	ret;

	typedef struct s_test_case
	{
		int	ac;
		char	*av[7]; //max 6 args + NULL char
		int	expected_return;
	}	t_test_case;

	static t_test_case tests[] =
	{
		/*
		//tests test[1] int, t_size, t_size, t_size
		//or test[1] int, t_size, t_size, t_size, int
		//valid input, expect 0 (no error)
		{5, {"philo", "4", "800", "200", "200", NULL}, 0},
		// valid input negative int ok, expect 0
		{6, {"philo", "-4", "800", "200", "200", "-3"}, 0},
		// not enough args, expect 1 (error)
		{4, {"philo", "4", "800", "200", NULL}, 1},
		// Invalid philos (non-numeric), expect error
		{5, {"philo", "abc", "800", "200", "200", NULL}, 1},
		// Invalid time_to_death (non-numeric), expect error
		{5, {"philo", "33", "abc", "200", "200", NULL}, 1},
		// Invalid eat_time (non-numeric), expect error
		{5, {"philo", "abc", "800", "-123", "200", NULL}, 1},
		// Invalid sleep_time (non-numeric), expect error
		// also leading trailing spaces ok
		{5, {"philo", "  abc  ", " 800", "200 ", "#$za", NULL}, 1},
		// Negative meal goal, no error
		{6, {"philo", "4", "800", "200", "200", "-1"}, 0},
		*/
		{5, {"./philo", "4", "800", "200", "200", NULL}, 0},
		{6, {"./philo", "-4", "800", "200", "200", "-3"}, 0},
		{4, {"./philo", "4", "800", "200", NULL}, 1},
		{5, {"./philo", "abc", "800", "200", "200", NULL}, 1},
		{5, {"./philo", "33", "abc", "200", "200", NULL}, 1},
		{5, {"./philo", "abc", "800", "-123", "200", NULL}, 1},
		{5, {"./philo", "  abc  ", " 800", "200 ", "#$za", NULL}, 1},
		{6, {"./philo", "4", "800", "200", "200", "-1"}, 0},

		// Edge cases for int (philos)
		// INT_MAX
		{5, {"./philo", "2147483647", "800", "200", "200", NULL}, 0},
		// INT_MIN
		{5, {"./philo", "-2147483648", "800", "200", "200", NULL}, 0},
		// overflow
		{5, {"./philo", "2147483648", "800", "200", "200", NULL}, 1},
		// underflow
		{5, {"./philo", "-2147483649", "800", "200", "200", NULL}, 1},

		// Edge cases for size_t (time values)
		// max size_t
		{5, {"./philo", "4", "18446744073709551615", "200", "200", NULL}, 0},
		// size_t overflow
		{5, {"./philo", "4", "18446744073709551616", "200", "200", NULL}, 1},
		// negative size_t invalid
		{5, {"./philo", "4", "-1", "200", "200", NULL}, 1},
		// all invalid
		{6, {"./philo", "abc", "-100", "abc", "zde", "abc", NULL}, 1},

	};

	int	num_tests = sizeof(tests) / sizeof(tests[0]);
	int	i = 0;
	while (i < num_tests)
	{
		printf("parse_init_args test case %d:\n", i + 1);
		int j = 0;
		while (j < tests[i].ac)
		{
			printf("%s ", tests[i].av[j]);
			j++;
		}
		printf("\n");
		ret = parse_init_args(tests[i].ac, tests[i].av, &args);
		printf("Return value: %d\n\n", ret);
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
		printf("Test case %d:\n", i + 1);
		if (parse_init_args(tests[i].ac, tests[i].av, &args) != 0)
		{
			print_usage();
			printf("parse_init_args failed\n");
			return ;
		}
		if (validate_args(tests[i].ac, &args) != 0)
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
	test_parse_init_args();
//	test_args();
	return(0);
}
