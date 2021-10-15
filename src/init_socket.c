/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_socket.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizou </var/mail/zizou>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 23:08:44 by zizou             #+#    #+#             */
/*   Updated: 2021/10/14 21:36:49 by zizou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern t_env g;

int		init_socket(void) {
	int err;
	int opt_value = 42;

	g.socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (g.socket == -1)
		exit_errors("Socket() failed\n");
	err = setsockopt(g.socket, IPPROTO_ICMP, SO_REUSEADDR, &opt_value, sizeof(opt_value));
	if (err == -1)
		exit_errors("Setsockopt() failed\n");
	err = setsockopt(g.socket, SOL_IP, IP_TTL, &g.ttl, sizeof(g.ttl));
	if (err == -1) {
		printf("%s\n", strerror(errno));
		exit_errors("Setsockopt() failed\n");
	}
	return (0);
}

void	resolve_hostname(void) {
	int err;
	struct addrinfo hints;
	struct addrinfo *result;
	struct sockaddr_in *addr4;
	int buf = 42;

	ft_memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = 0;
	hints.ai_family = AF_INET;
	hints.ai_socktype = 0;
	hints.ai_protocol = IPPROTO_ICMP;
	hints.ai_addrlen = 0;
	hints.ai_addr = NULL;
	hints.ai_canonname = NULL;
	hints.ai_next = NULL;

	err = getaddrinfo(g.arg, NULL, &hints, &result);
	if (err) {
		exit_errors("Getaddrinfo() failed\n");
	}
	addr4 = (struct sockaddr_in *)result->ai_addr;
	g.dst = addr4;
	inet_ntop(AF_INET, &addr4->sin_addr, g.host, INET_ADDRSTRLEN);
}
