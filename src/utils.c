/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizou </var/mail/zizou>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:21:32 by zizou             #+#    #+#             */
/*   Updated: 2021/10/25 13:05:02 by zizou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern struct s_env global_env;

void print_stats(void)
{
		unsigned int packets_loss;
	
		packets_loss = ((global_env.packets_out - global_env.packets_in) * 100)
			/ global_env.packets_out;
		if (global_env.packets_in) {
				global_env.rtt_avg /= global_env.packets_in;
				global_env.mdev /= global_env.packets_in; 
				global_env.mdev = ft_sqrt(global_env.mdev - global_env.rtt_avg * global_env.rtt_avg);
		}

		gettimeofday(&global_env.tv_end, NULL);
		printf("\n--- %s ping statistics ---\n", global_env.arg);
		if (global_env.errors) {
				printf("%d packets transmitted, %d received, +%d errors, %d%% packet loss, time %.0f ms\n",
						global_env.packets_out, global_env.packets_in, global_env.errors, packets_loss,
						gettimeval(global_env.tv_start, global_env.tv_end));
				ft_unsetenv();
				close(global_env.socket);
				exit(EXIT_SUCCESS);
		}
		printf("%d packets transmitted, %d received, %d%% packet loss, time %.0f ms\n",
				global_env.packets_out, global_env.packets_in, packets_loss,
				gettimeval(global_env.tv_start, global_env.tv_end));
		printf("rtt min/avg/max/mdev = %.2f/%.2f/%.2f/%.2f ms\n", global_env.rtt_min,
				global_env.rtt_avg, global_env.rtt_max, global_env.mdev);
		ft_unsetenv();
		close(global_env.socket);
		exit(EXIT_SUCCESS);
}

void exit_errors(char *s)
{
		fprintf(stderr, "%s", s);
		ft_unsetenv();
		close(global_env.socket);
		exit(EXIT_FAILURE);
}

void handle_errors(int ac)
{
		if ((ac < 2 || ac > 3) || global_env.opt.h || (global_env.opt.v && ac != 3)
				|| (!global_env.opt.v && ac > 2) || global_env.arg == NULL)
				exit_errors("Usage: ft_ping [-hv] [-h help] \
						[-v verbose] destination\n");
		if (getuid() != 0)
				exit_errors("Operation not permitted. See man sudo\n");
}

unsigned short checksum(void *addr, int len)
{
		unsigned long checksum = 0;
		unsigned short *buf = addr;
	
		while (len > 1) {
				checksum += (unsigned short)*buf++;
				len -= sizeof(unsigned short);
		}
		if (len)
			checksum += *(unsigned char*)buf;
		checksum = (checksum >> 16) + (checksum & 0xffff);
		checksum = checksum + (checksum >> 16);
		return ((unsigned short)(~checksum));
}

inline int	is_little_endian(void)
{
		int x = 1;
		return (*(char *)&x);
}

inline double gettimeval(struct timeval before, struct timeval after)
{
		return (((after.tv_sec - before.tv_sec) * 1000.0)
				+ (after.tv_usec - before.tv_usec) / 1000.0);
}
