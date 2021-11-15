/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizou </var/mail/zizou>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:56:09 by zizou             #+#    #+#             */
/*   Updated: 2021/11/12 13:39:42 by zizou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern struct s_env global_env;

static struct icmp	*fill_icmphdr(struct icmp *icmp)
{
		struct icmp *hdr = NULL;

		hdr = icmp;
		hdr->icmp_type = ICMP_ECHO;
		hdr->icmp_code = 0;
		hdr->icmp_cksum = 0;
		hdr->icmp_id = global_env.pid;
		hdr->icmp_seq = global_env.seq;
		hdr->icmp_cksum = checksum(hdr, PING_SIZE);
		return (hdr);
}

static struct ip *fill_iphdr(struct ip *ip)
{
		struct ip *hdr = NULL;
	
		hdr = ip;
		if (is_little_endian()) {
				hdr->ip_hl = 5;
				hdr->ip_v = IPVERSION;
		} else {
				hdr->ip_hl = IPVERSION;
				hdr->ip_v = 5;
		}
		hdr->ip_tos = IPTOS_ECN_NOT_ECT;
		hdr->ip_len = PING_SIZE;
		hdr->ip_ttl = global_env.ttl;
		return (hdr);
}

int	send_ping(void)
{
		int	err = 0;
		char ping[PING_SIZE];
		struct ip *ip = NULL;
		struct icmp	*icmp = NULL;

		ft_memset(ping, 0, sizeof(ping));
		ft_memset(&ip, 0, sizeof(ip));
		ft_memset(&icmp, 0, sizeof(icmp));

		ip = fill_iphdr((struct ip *)ping);
		icmp = fill_icmphdr((struct icmp *)ip);

		gettimeofday(&global_env.tv_tick, NULL);
		err = sendto(global_env.socket, ping, sizeof(ping), 0,
				(struct sockaddr *)global_env.ipv4, sizeof(*global_env.ipv4));
		if (err == -1)
				return(err);
		global_env.seq++;
		global_env.packets_out++;
		return (0);
}
