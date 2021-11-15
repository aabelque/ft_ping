/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizou </var/mail/zizou>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:11:55 by zizou             #+#    #+#             */
/*   Updated: 2021/11/13 17:48:48 by zizou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

struct s_env global_env;

//TODO 
// ttl = 1 from 'routeur' (ip routeur)
void ft_ping(void)
{
		int		err = 0;

		resolve_hostname();
		init_socket();
		gettimeofday(&global_env.tv_start, NULL);
		printf("PING %s (%s) %ld(%ld) bytes of data.\n", global_env.arg,
				global_env.host, PING_SIZE - sizeof(struct icmp), PING_SIZE);
		signal(SIGALRM, sig_alarm);
		err = send_ping();
		if (err == -1)
				exit_errors("Sendto() failed\n");
		while (42) {
				err = recv_ping();
				if (err == -1)
						exit_errors("Recvmsg() failed\n");
				signal(SIGINT, sig_interrupt);
				signal(SIGQUIT, sig_quit);
				alarm(1);
		}
		free(global_env.arg);
		close(global_env.socket);
}

int main(int ac, char **av)
{
		ft_setenv();
		ft_parse_args(ac, av + 1);
		handle_errors(ac);
		ft_ping();
		return (0);
}
