/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizou </var/mail/zizou>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:11:55 by zizou             #+#    #+#             */
/*   Updated: 2021/10/14 21:25:05 by zizou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_env g;

void	recv_icmp_echo(void) {
	int		err;
	struct	msghdr msg;
	struct	iovec iov;
	char	buff[100];

	ft_memset(&msg, 0, sizeof(msg));
	ft_memset(&iov, 0, sizeof(iov));
	iov.iov_base = buff;
	iov.iov_len = sizeof(buff);
	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = NULL;
	msg.msg_controllen = 1;
	msg.msg_flags = 0;
	err = recvmsg(g.socket, &msg, 0);
	printf("%s\n", strerror(errno));
	if (err == -1)
		exit_errors("Recvmsg() failed\n");
}

void	send_icmp_echo(void) {
	int seq = 0;
	ssize_t err;
	struct icmphdr hdr;

	ft_memset(&hdr, 0, sizeof(hdr));
	hdr.type = ICMP_ECHO;
	hdr.checksum = 0;
	hdr.checksum = icmp_checksum((uint16_t *)&hdr, sizeof(hdr));
	hdr.un.echo.id = htons(getpid());
	hdr.un.echo.sequence = htons(seq++);
	err = sendto(g.socket, &hdr, sizeof(hdr), 0, (struct sockaddr *)g.dst, sizeof(*g.dst));
	if (err == -1)
		exit_errors("Sendto() failed\n");
}

void	ft_ping() {
	init_socket();
	resolve_hostname();
	send_icmp_echo();
	recv_icmp_echo();
	close(g.socket);
}

int		main(int ac, char **av) {

	ft_setenv();
	ft_parse_args(av + 1);
	handle_errors(ac);
	ft_ping();
	return (0);
}
