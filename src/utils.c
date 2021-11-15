/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizou </var/mail/zizou>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:21:32 by zizou             #+#    #+#             */
/*   Updated: 2021/11/14 23:41:59 by zizou            ###   ########.fr       */
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
		tv_sub(&global_env.tv_end, &global_env.tv_start);
		printf("\n--- %s ping statistics ---\n", global_env.arg);
		printf("%ld packets transmitted, ", global_env.packets_out);
		printf("%ld received, ", global_env.packets_in);
		if (global_env.errors)
				printf("+%ld errors, ", global_env.errors);
		if (global_env.packets_out) {
				printf("%d%% packet loss, ", packets_loss);
				printf("time %ld ms\n", 1000 * global_env.tv_end.tv_sec + global_env.tv_end.tv_usec/1000);
		}
		printf("rtt min/avg/max/mdev = %ld.%03ld/%lu.%03ld/%ld.%03ld/%ld.%03ld ms\n",
				global_env.rtt_min / 1000, global_env.rtt_min % 1000,
				(unsigned long)(global_env.rtt_avg / 1000), global_env.rtt_avg % 1000,
				global_env.rtt_max / 1000, global_env.rtt_max % 1000,
				global_env.mdev / 1000, global_env.mdev % 1000);
		ft_unsetenv();
		close(global_env.socket);
		exit(EXIT_SUCCESS);
}

void print_ewma_stats(void)
{
		unsigned int loss = 0;
		long avg = 0;
	
		loss = ((global_env.packets_out - global_env.packets_in) * 100)
			/ global_env.packets_out;
		avg = global_env.rtt_avg / global_env.packets_in;
		fprintf(stderr, "\r%ld/%ld packets, %d%% loss, ",
				global_env.packets_out, global_env.packets_in, loss);
		fprintf(stderr, "min/avg/ewma/max = %ld.%03ld/%lu.%03ld/%d.%03d/%ld.%03ld ms\n",
				global_env.rtt_min / 1000, global_env.rtt_min % 1000,
				avg / 1000, avg % 1000,
				(int)global_env.rtt / 8000, (int)(global_env.rtt/8)%1000,
				global_env.rtt_max / 1000, global_env.rtt_max % 1000);
}

void exit_errors(char *s)
{
		if (!s) {
				ft_unsetenv();
				close(global_env.socket);
				exit(EXIT_FAILURE);
		}
		fprintf(stderr, "%s", s);
		ft_unsetenv();
		close(global_env.socket);
		freeaddrinfo(global_env.res);
		exit(EXIT_FAILURE);
}

void handle_errors(int ac)
{
		if (global_env.dash > 1) {
				if (global_env.opt.h || global_env.arg == NULL) {
						fprintf(stderr, "%s\n%49s\n", USAGE, USAGE_OPT);
						exit_errors("");
				}
		} else {
				if (((ac < 2 || ac > 3) && !global_env.ttl)|| global_env.opt.h || (global_env.opt.v && ac != 3)
							|| global_env.arg == NULL || (!global_env.dash && ac != 2)) {
						fprintf(stderr, "%s\n%49s\n", USAGE, USAGE_OPT);
						exit_errors("");
				}
		}
		if (getuid() != 0)
				exit_errors("Operation not permitted. See man sudo\n");
		if (!global_env.ttl)
				global_env.ttl = IPDEFTTL;
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

inline long gettimeval(struct timeval before, struct timeval after)
{
		return (((after.tv_sec - before.tv_sec) * 1000.0)
				+ (after.tv_usec - before.tv_usec) / 1000.0);
}

inline void tv_sub(struct timeval *out, struct timeval *in)
{
		if ((out->tv_usec -= in->tv_usec) < 0) {
				--out->tv_sec;
				out->tv_usec += 1000000;
		}
		out->tv_sec -= in->tv_sec;
}
