/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hostname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizou </var/mail/zizou>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:05:16 by zizou             #+#    #+#             */
/*   Updated: 2021/11/17 02:43:17 by zizou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern struct s_env global_env;

int ip_version(char *ip)
{
		char buf[16] = {0};

		if (inet_pton(AF_INET, ip, buf))
			return (4);
		else if (inet_pton(AF_INET6, ip, buf))
			return (6);
		return (-1);
}

void	resolve_dns(struct sockaddr *addr)
{
		socklen_t len;

		if (getnameinfo(addr, len, global_env.dns, sizeof(global_env.dns),
					NULL, 0, NI_NAMEREQD))
				global_env.rdns = false;
}

void resolve_hostname(void)
{
		int err;
		struct addrinfo hints;
		struct sockaddr_in *addr4;

		ft_memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_flags = 0;
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_RAW;
		hints.ai_protocol = IPPROTO_ICMP;
		hints.ai_addrlen = 0;
		hints.ai_addr = NULL;
		hints.ai_canonname = NULL;
		hints.ai_next = NULL;

		err = getaddrinfo(global_env.arg, NULL, &hints, &global_env.res);
		if (err) {
				switch (err) {
				case -3:
						fprintf(stderr, "ft_ping: %s: Temporary failure in name resolution\n", global_env.arg);
						break;
				case -2:
						fprintf(stderr, "ft_ping: %s: Name or service not known\n", global_env.arg);
						break;
				}
				exit_errors("");
		}
		addr4 = (struct sockaddr_in *)global_env.res->ai_addr;
		global_env.ipv4 = addr4;
		inet_ntop(AF_INET, &addr4->sin_addr, global_env.host, INET_ADDRSTRLEN);
		if (!ft_strcmp(global_env.host, "0.0.0.0"))
				ft_strcpy(global_env.host, "127.0.0.1");
		resolve_dns((struct sockaddr *)addr4);
}
