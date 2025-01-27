/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_logtime.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:35:46 by hanmpark          #+#    #+#             */
/*   Updated: 2023/03/14 01:25:18 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scholarship_logtime.h"
#include "calculate_time.h"
#include "find_time.h"
#include "print.h"

static int	set_days_off(void)
{
	int		days_off;

	printf("%s%sThe number of days you want to take off from now on:%s%s ", ITALIC, GRAY, DEF, GREEN);
	scanf("%d", &days_off);
	if (days_off < 0 || days_off >= days_left())
	{
		printf("%s%s\t\tIncompatible days off%s\n", ITALIC, RED, DEF);
		days_off = 0;
	}
	printf("%s%sDays off : %s%d%s\n", DEF, BOLD, GREEN, days_off, DEF);
	return (days_off);
}

static void	incomplete_logtime(int *ttlog)
{
	int	dleft;
	int	hours_left;
	int	minutes_left;
	int	seconds_left;

	ccl_timeleft(ttlog);
	dleft = days_left() - set_days_off();
	hours_left = ttlog[2] / dleft;
	minutes_left = ((ttlog[2] % dleft) * 60 + ttlog[1]) / dleft;
	seconds_left = ((((ttlog[2] % dleft) * 60 + ttlog[1]) % dleft) * 60 + ttlog[0]) / dleft;
	printf("%sTime left: %s%dh %dmin %ds%s\n", BOLD, GREEN,
		ttlog[2], ttlog[1], ttlog[0], DEF);
	printf("%sDays left: %s%d days%s\n", BOLD, GREEN, dleft, DEF);
	if (hours_left < 13)
	{
		printf("%sTo do log: %s%dh %dmin %ds / day%s\n", BOLD, GREEN,
			hours_left, minutes_left, seconds_left, DEF);
	}
	else if (hours_left < 24)
	{
		printf("%sTo do log: %s%dh %dmin %ds / day%s\n", BOLD, YELLOW,
			hours_left, minutes_left, seconds_left, DEF);
	}
	else
	{
		printf("%sTo do log: %s%dh %dmin %ds / day%s\n", BOLD, RED,
			hours_left, minutes_left, seconds_left, DEF);
		printf("%s%s\t   sorry it's impossible%s\n", ITALIC, RED, DEF);
	}
}

void	check_logtime(int month, int *stdlog, int *ttlog)
{
	printf("------------------------------------------------------\n");
	if (ttlog[2] < 140 && month == current_month())
		incomplete_logtime(ttlog);
	else if (stdlog[2] >= 140 && stdlog[2] < 210)
	{
		stdlog[2] -= 140;
		printf("%s%s\t\t     LOGTIME OK !%s\n\n", GREEN, ITALIC, DEF);
		printf("%sNext month bonus: %s%dh %dmin %ds%s\n", PURPLE, GREEN,
			stdlog[2], stdlog[1], stdlog[0], DEF);
	}
	else if (stdlog[2] >= 210)
	{
		stdlog[2] = 70;
		stdlog[1] = 0;
		stdlog[0] = 0;
		printf("%s%s\t\t     LOGTIME OK !%s\n\n", GREEN, ITALIC, DEF);
		printf("%sNext month bonus: %s%dh %dmin %ds%s\n", PURPLE, GREEN,
			stdlog[2], stdlog[1], stdlog[0], DEF);
	}
	else
		printf("%s\t\tNothing for next month%s\n", PURPLE, DEF);
	printf("------------------------------------------------------\n\n");
}
