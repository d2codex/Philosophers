#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

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
		// expected input format
		// ./philo int t_size t_size t_size [int]
	
		// valid input: all fields correctly formatted
		{5, {"./philo", "4", "800", "200", "200", NULL}, 0},
		// valid signed ints for philos and meal_goal, valid positive size_ts
		{6, {"./philo", "-4", "800", "200", "200", "-3"}, 0},
		// too few arguments, should fail
		{4, {"./philo", "4", "800", "200", NULL}, 1},
		// invalid int for philosophers (non-numeric string)
		{5, {"./philo", "abc", "800", "200", "200", NULL}, 1},
		// invalid t_size for time_til_death (non-numeric string)
		{5, {"./philo", "33", "abc", "200", "200", NULL}, 1},
		// invalid t_size for eat_time (negative value not allowed)
		{5, {"./philo", "4", "800", "-123", "200", NULL}, 1},
		// invalid t_size for sleep_time (non-digit characters)
		{5, {"./philo", "4", "800", "200", "#$za", NULL}, 1},
		// valid meal_goal int, signed -1 accepted here as valid parse
		{6, {"./philo", "4", "800", "200", "200", "-1"}, 0},
		// all invalid inputs in one test case to check multiple errors reported
		{6, {"./philo", "abc", "-100", "abc", "zde", "abc", NULL}, 1},
		// all args empty or whitespace-only strings, expect parse failure
		{6, {"./philo", "", "   ", " ", "\t", "\n", NULL}, 1},
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
void	test_integration()
{
	t_args	args;

	typedef struct s_test_case
	{
		int	ac;
		char	*av[7];
	}	t_test_case;

	static t_test_case tests[] =
	{	
		// expected input format
		// ./philo int t_size t_size t_size [int]
		// INT_MAX
		{5, {"./philo", "15", "800", "200", "200", NULL}},
		// INT_MIN
		{5, {"./philo", "10", "800", "200", "200", NULL}},
		// Edge cases for size_t (time values)
		// max size_t
		{5, {"./philo", "4", "700", "200", "200", NULL}},
		// all invalid
		{6, {"./philo", "0", "0", "0", "0", "-2", NULL}},

	};
	int	num_test = sizeof(tests) / sizeof(tests[0]);
	int	i = 0;
	while (i < num_test)
	{
		printf("Test case %d:\n", i + 1);
		int j = 0;
		while (j < tests[i].ac)
		{
			printf("%s ", tests[i].av[j]);
			j++;
		}
		printf("\n");
		if (parse_init_args(tests[i].ac, tests[i].av, &args) != 0)
		{
			print_usage();
			printf("parse_init_args failed\n");
			i++;
			continue ;
		}
		validate_args(tests[i].ac, &args);		
		printf("\n");
		pthread_mutex_t *forks = NULL;
		t_philo *philos = NULL;
		if (init_forks(&forks, args.philos) != 0)
		{
			printf("init_forks failed\n");
			i++;
			continue;
		}
		// test init_philos
		if (init_philos(&philos, &args, forks) != 0)
		{
			printf("init_philo failed\n");
			free(forks);
			i++;
			continue;
		}
		// philo info after init
		for (int p = 0; p < args.philos; p++)
		{
			printf("Philo %d: id=%d, meals_eaten=%d, state=%d, last_meal_time=%ld\n",
				p, philos[p].id, philos[p].meals_eaten, philos[p].state,
				philos[p].t_last_meal_start);
			// Check fork pointers validity
			if (philos[p].left_fork == NULL || philos[p].right_fork == NULL)
				printf("Error: philosopher %d fork pointers NULL\n", p);
		}
		free(philos);
		free(forks);
		printf("\n");
		i++;
	}
}
#include <stdbool.h>

// test print_display_msg(t_philo *philo, t_state action)
// test single thread only
void	test_print_display_msg()
{
	t_args	args;
	t_philo philo;

	pthread_mutex_init(&args.print_lock, NULL);

	philo.id = 1;
	philo.args = &args;
	philo.t_start = get_time_ms();

	//args.simulation_stopped = false;
	args.simulation_stopped = true;

	print_display_msg(&philo, THINKING);
	print_display_msg(&philo, GOT_L_FORK);
	print_display_msg(&philo, EATING);
	print_display_msg(&philo, DIED);
	print_display_msg(&philo, SLEEPING);
	//print_display_msg(&philo, DIED);

	pthread_mutex_unlock(&args.print_lock);
}

int	main(void)
{
//	test_atosize();
//	test_safe_atoi();
//	test_parse_init_args();
//	test_integration();
	test_print_display_msg();
	return(0);
}
