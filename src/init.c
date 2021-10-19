/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizou </var/mail/zizou>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:06:56 by zizou             #+#    #+#             */
/*   Updated: 2021/10/19 02:14:07 by zizou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern struct s_env global_env;

void ft_setenv(void)
{
		global_env.opt = (struct s_opt) { .h = false, .v = false };
		global_env.arg = NULL;
		global_env.packets_out = 0;
		global_env.packets_in = 0;
		global_env.rtt_max = 0.0;
		global_env.rtt_min = 0.0;
		global_env.rtt_avg = 0.0;
		global_env.rtt_total = 0.0;
		global_env.mdev = 0.0;
		global_env.pid = getpid();
		global_env.socket = 0;
		global_env.ttl = IPDEFTTL;
		global_env.seq = 1;
		global_env.dst = NULL;
}

void ft_unsetenv(void)
{
		global_env.opt = (struct s_opt) { .h = false, .v = false };
		global_env.packets_out = 0;
		global_env.packets_in = 0;
		global_env.rtt_max = 0.0;
		global_env.rtt_min = 0.0;
		global_env.rtt_avg = 0.0;
		global_env.rtt_total = 0.0;
		global_env.mdev = 0.0;
		global_env.pid = 0;
		global_env.socket = 0;
		global_env.ttl = 0;
		global_env.seq = 0;
		global_env.dst = NULL;
		free(global_env.arg);
		global_env.arg = NULL;
}

int init_socket(void)
{
		int err;

		global_env.socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
		if (global_env.socket == -1)
				exit_errors("Socket() failed\n");
		err = setsockopt(global_env.socket, IPPROTO_IP, IP_TTL,
				&global_env.ttl, sizeof(global_env.ttl));
		if (err == -1)
				exit_errors("Setsockopt() failed\n");
		return (0);
}

inline void	sig_interrupt(__attribute__((unused))int sig)
{
		print_stats();
}

inline void	sig_alarm(__attribute__((unused))int sig)
{
		send_ping();
}
