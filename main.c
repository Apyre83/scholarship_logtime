/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 22:25:52 by hanmpark          #+#    #+#             */
/*   Updated: 2023/01/20 15:26:07 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/scholarship_logtime.h"

static void	print_result(int month, int lastmonth, char **date, char **bonus_date)
{
	int		i;

	i = 0;
	if (date)
	{
		printf("%s\nTHE CHOSEN MONTH'S LOGTIMES:%s\n", BLUE, DEF);
		while (date[i])
		{
			printf("  - %s", date[i]);
			i++;
		}
		printf("\n");
	}
	ccl_logtime(month, lastmonth, date, bonus_date);
}

static int	find_month(int argc, char *month)
{
	int	res;

	if (argc == 2 && (atoi(month) >= 1 && atoi(month) <= 12))
	{
		res = atoi(month);
		printf("%sChosen month is:%s %d\n", BOLD, DEF, res);
	}
	else if (argc == 2 && (atoi(month) < 1 || atoi(month) > 12))
		return (0);
	else
	{
		res = current_month();
		printf("%sCurrent month:%s %d\n", BOLD, DEF, res);
		if (current_day() >= 27 && current_day() <= 31)
			res++;
		if (res == 13)
			res = 1;
	}
	return (res);
}

static int	set_dates(int month, int lastmonth, char ***date, char ***bonus_date)
{
	int	fd;

	fd = open("dates.txt", O_RDONLY);
	*date = parse_month(month, lastmonth, fd);
	close(fd);
	if (!*date)
	{
		printf("%sCan't calculate for this month...%s\n\n", RED, DEF);
		return (0);
	}
	month = lastmonth;
	lastmonth = month - 1;
	if (month == 1)
		lastmonth = 12;
	fd = open("dates.txt", O_RDONLY);
	*bonus_date = parse_month(month, lastmonth, fd);
	close(fd);
	return (1);
}

int	main(int argc, char **argv)
{
	int		month;
	int		lastmonth;
	char	**date;
	char	**bonus_date;

	api_dates();
	api_public_holidays();
	month = find_month(argc, argv[1]);
	if (!month)
	{
		printf("%sMonth doesn't exist...%s\n\n", RED, DEF);
		return (-1);
	}
	lastmonth = month - 1;
	if (month == 1)
		lastmonth = 12;
	if (!(set_dates(month, lastmonth, &date, &bonus_date)))
		return (-1);
	print_result(month, lastmonth, date, bonus_date);
	if (bonus_date)
		free_month(bonus_date);
	free_month(date);
	return (0);
}
