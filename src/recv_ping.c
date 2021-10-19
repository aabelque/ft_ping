/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_ping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizou </var/mail/zizou>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:57:08 by zizou             #+#    #+#             */
/*   Updated: 2021/10/19 02:16:47 by zizou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern struct s_env global_env;

void get_reply(struct msghdr msg, int n)
{
		float rtt = 0.0;
		char *buff;
		struct ip *ip;
		struct icmp	*icmp;

		buff = msg.msg_iov->iov_base;
		ip = (struct ip *)buff;
		icmp = (struct icmp *)(buff + (ip->ip_hl * 4));

		rtt = gettimeval(global_env.tv_tick, global_env.tv_end);
		if (icmp->icmp_type != 8) {
				printf("%d bytes from %s (%s): icmp_seq=%d ttl=%d time=%.2f ms\n",
						n, global_env.arg, global_env.host,
						icmp->icmp_seq, global_env.ttl, rtt);
				if (icmp->icmp_type == 0) {
						global_env.packets_in++;
						global_env.rtt_avg += rtt;
						if (rtt > global_env.rtt_max)
								global_env.rtt_max = rtt;
						if (rtt < global_env.rtt_min)
								global_env.rtt_min = rtt;
						else if (global_env.rtt_min == 0)
								global_env.rtt_min = rtt;
						global_env.mdev += rtt * rtt;
				}
		}
}

struct msghdr fill_msghdr(struct iovec *iov)
{
		struct msghdr hdr;

		hdr.msg_name = NULL;
		hdr.msg_namelen = 0;
		hdr.msg_iov = iov;
		hdr.msg_iovlen = 1;
		hdr.msg_control = NULL;
		hdr.msg_controllen = 0;
		hdr.msg_flags = 0;
		return (hdr);
}

int	recv_ping(void)
{
		int	n = 0;
		char iov_base[PING_SIZE];
		struct iovec iov;
		struct msghdr msg;

		ft_memset(&msg, 0, sizeof(msg));
		ft_memset(&iov, 0, sizeof(iov));
		ft_memset(iov_base, 0, sizeof(iov_base));

		iov.iov_base = iov_base;
		iov.iov_len = sizeof(iov_base);
	
		msg = fill_msghdr(&iov);

		if ((n = recvmsg(global_env.socket, &msg, 0)) < 0)
				return (n);
		gettimeofday(&global_env.tv_end, NULL);
		get_reply(msg, n);
		return (0);
}
