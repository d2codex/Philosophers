

int	main(void)
{
	long	start;
	long	end;
	long	elapsed;

	start = get_time_ms();
	printf("Start time: %ld ms\n", start);

	//usleep(500 * 1000); // sleep 500ms
	
	smart_sleep(500);

	end = get_time_ms();
	elapsed = end - start;
	printf("Elapsed after 500ms sleep: %ld ms\n", elapsed);

	//usleep(700 * 1000); // sleep additional 700ms
	
	smart_sleep(700);

	end = get_time_ms();
	elapsed = end - start;
	printf("Elapsed after total 1200ms sleep: %ld ms\n", elapsed);

	return 0;
}
