/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hostname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizou </var/mail/zizou>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:05:16 by zizou             #+#    #+#             */
/*   Updated: 2021/10/19 01:41:32 by zizou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern struct s_env global_env;

void resolve_hostname(void)
{
		int err;
		struct addrinfo hints;
		struct addrinfo *result;
		struct sockaddr_in *addr4;

		ft_memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_flags = 0;
		hints.ai_family = AF_INET;
		hints.ai_socktype = 0;
		hints.ai_protocol = IPPROTO_ICMP;
		hints.ai_addrlen = 0;
		hints.ai_addr = NULL;
		hints.ai_canonname = NULL;
		hints.ai_next = NULL;

		err = getaddrinfo(global_env.arg, NULL, &hints, &result);
		if (err) {
				exit_errors("Getaddrinfo() failed\n");
		}
		addr4 = (struct sockaddr_in *)result->ai_addr;
		global_env.dst = addr4;
		inet_ntop(AF_INET, &addr4->sin_addr, global_env.host, INET_ADDRSTRLEN);
		freeaddrinfo(result);
}
