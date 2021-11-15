/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizou </var/mail/zizou>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:06:56 by zizou             #+#    #+#             */
/*   Updated: 2021/11/14 23:41:59 by zizou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern struct s_env global_env;

void ft_setenv(void)
{
		global_env.opt = (struct s_opt) { .h = false, .v = false, .q = false };
		global_env.rdns = true;
		global_env.dash = 0;
		global_env.arg = NULL;
		global_env.res = NULL;
		global_env.packets_out = 0;
		global_env.packets_in = 0;
		global_env.errors = 0;
		global_env.rtt_max = 0;
		global_env.rtt_min = 0;
		global_env.rtt_avg = 0;
		global_env.rtt_total = 0;
		global_env.mdev = 0;
		global_env.pid = getpid();
		global_env.socket = 0;
		global_env.ttl = 0;
		global_env.seq = 1;
		global_env.ipv4 = NULL;
		ft_memset(global_env.host, 0, sizeof(global_env.host));
		ft_memset(global_env.dns, 0, sizeof(global_env.dns));
}

void ft_unsetenv(void)
{
		global_env.opt = (struct s_opt) { .h = false, .v = false, .q = false };
		global_env.dash = 0;
		global_env.packets_out = 0;
		global_env.packets_in = 0;
		global_env.errors = 0;
		global_env.rtt_max = 0;
		global_env.rtt_min = 0;
		global_env.rtt_avg = 0;
		global_env.rtt_total = 0;
		global_env.mdev = 0;
		global_env.pid = 0;
		global_env.socket = 0;
		global_env.ttl = 0;
		global_env.seq = 0;
		global_env.ipv4 = NULL;
		free(global_env.arg);
		freeaddrinfo(global_env.res);
		global_env.arg = NULL;
		global_env.res = NULL;
}

int init_socket(void)
{
		int err = 0;
		struct timeval timeout = {1, 0};

		global_env.socket = socket(global_env.res->ai_family,
				global_env.res->ai_socktype, global_env.res->ai_protocol);
		if (global_env.socket == -1)
				exit_errors("Socket() failed\n");
		err = setsockopt(global_env.socket, IPPROTO_IP, IP_TTL,
				&global_env.ttl, sizeof(global_env.ttl));
		if (err == -1)
				exit_errors("Setsockopt() failed\n");
		err = setsockopt(global_env.socket, SOL_SOCKET, SO_RCVTIMEO,
				(const void *)&timeout, sizeof(timeout));
		if (err == -1)
				exit_errors("Setsockopt() failed\n");
		return (0);
}

inline void sig_quit(__attribute__((unused))int sig)
{
	print_ewma_stats();
}

inline void	sig_interrupt(__attribute__((unused))int sig)
{
		print_stats();
}

inline void	sig_alarm(__attribute__((unused))int sig)
{
		send_ping();
}
