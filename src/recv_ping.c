/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_ping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizou </var/mail/zizou>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:57:08 by zizou             #+#    #+#             */
/*   Updated: 2021/11/15 01:37:27 by zizou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern struct s_env global_env;

static void print_from(int x, int nbytes, char *hname, char *host)
{
		if (x)
			printf("%ld bytes from %s (%s):", nbytes - sizeof(struct ip), hname, host);
		else
			printf("%d bytes from %s:", nbytes, hname);
}

static void print_output(int x, int seq, int nbytes, long triptime, int ttl)
{
		if (global_env.rdns)
				print_from(x, nbytes, global_env.dns, global_env.host);
		else
				print_from(x, nbytes, global_env.arg, global_env.host);
		printf(" icmp_seq=%d", seq);
		printf(" ttl=%d", ttl);
		if (triptime >= 100000)
			printf(" time=%ld ms\n", triptime / 1000);
		else if (triptime >= 10000)
			printf(" time=%ld.%01ld ms\n", triptime / 1000, (triptime % 1000) / 100);
		else if (triptime >= 1000)
			printf(" time=%ld.%02ld ms\n", triptime / 1000, (triptime % 1000) / 10);
		else
			printf(" time=%ld.%03ld ms\n", triptime / 1000, triptime % 1000);
}

void update_statistics(long triptime)
{
		global_env.packets_in++;
		global_env.rtt_avg += triptime;
		if (triptime > global_env.rtt_max)
				global_env.rtt_max = triptime;
		if (triptime < global_env.rtt_min)
				global_env.rtt_min = triptime;
		else if (global_env.rtt_min == 0)
				global_env.rtt_min = triptime;
		if (!global_env.rtt)
				global_env.rtt = triptime * 8;
		else
				global_env.rtt += triptime - global_env.rtt / 8;
		global_env.mdev += triptime * triptime;
}

void update_stats(int nbytes, long triptime, struct icmp *icmp, struct ip *ip, int ttl)
{
		struct hostent *ht = NULL;

		switch (icmp->icmp_type) {
		case 0:
				switch (global_env.opt.v) {
				case true:
						if (!global_env.opt.q) {
								printf("%d bytes from %s: type = %d, code = %d\n",
										nbytes, global_env.arg, icmp->icmp_type,
										icmp->icmp_code);
						}
						break;
				case false:
						if (!global_env.opt.q) {
								if (ft_strcmp(global_env.arg, global_env.host))
										print_output(1, icmp->icmp_seq, nbytes, triptime, ttl);
								else
										print_output(0, icmp->icmp_seq, nbytes, triptime, ttl);
						}
						break;
				}
				update_statistics(triptime);
				break;
		case 11:
				if (!global_env.opt.q) {
						if (global_env.ttl > 8) {
								printf("From %s (%s): icmp_seq=%d Time to live exceeded\n",
										global_env.arg, global_env.host, icmp->icmp_seq);
						} else {
								ht = gethostbyaddr(&ip->ip_src, 4, AF_INET);
								if (ht)
										printf("From %s (%s): icmp_seq=%d Time to live exceeded\n",
												ht->h_name, inet_ntoa(ip->ip_src), icmp->icmp_seq);
								else
										printf("From %s (%s): icmp_seq=%d Time to live exceeded\n",
												inet_ntoa(ip->ip_src), inet_ntoa(ip->ip_src), icmp->icmp_seq);
						}
				}
				global_env.errors++;
				break;
		}
}

void get_reply(struct msghdr msg, int nbytes)
{
		int ttl = 0;
		long triptime = 0;
		char *buff;
		struct ip *ip;
		struct icmp	*icmp;

		buff = msg.msg_iov->iov_base;
		ip = (struct ip *)buff;
		icmp = (struct icmp *)(buff + (ip->ip_hl * 4));

		ttl = ip->ip_ttl;
		tv_sub(&global_env.tv_end, &global_env.tv_tick);
		triptime = global_env.tv_end.tv_sec * 1000000 + global_env.tv_end.tv_usec;
		if (icmp->icmp_type != 8) {
				if (nbytes > 0)
						update_stats(nbytes, triptime, icmp, ip, ttl);
				else if (global_env.opt.v)
						if (errno != EWOULDBLOCK)
						printf("%ld bytes from %s: type = %d, code = %d\n", PING_SIZE, global_env.arg,
								icmp->icmp_type, icmp->icmp_code);
		}
}

static struct msghdr fill_msghdr(struct iovec *iov)
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
		int	nbytes = 0;
		char iov_base[PING_SIZE];
		struct iovec iov;
		struct msghdr msg;

		ft_memset(&msg, 0, sizeof(msg));
		ft_memset(&iov, 0, sizeof(iov));
		ft_memset(iov_base, 0, sizeof(iov_base));

		iov.iov_base = iov_base;
		iov.iov_len = sizeof(iov_base);
	
		msg = fill_msghdr(&iov);

		if ((nbytes = recvmsg(global_env.socket, &msg, 0)) < 0)
				if (errno != EAGAIN && errno != EINTR)
					return (nbytes);
		gettimeofday(&global_env.tv_end, NULL);
		get_reply(msg, nbytes);
		return (0);
}
