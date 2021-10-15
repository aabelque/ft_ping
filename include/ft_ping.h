/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:41:59 by aabelque          #+#    #+#             */
/*   Updated: 2021/10/14 21:00:14 by zizou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

#include <stdio.h>
#include <stdlib.h>
#include <netinet/ip_icmp.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <arpa/inet.h>

typedef struct	s_opt
{
	bool	h;
	bool	v;
}				t_opt;

typedef struct	s_env
{
	t_opt	opt;
	char	*arg;
	char	host[INET_ADDRSTRLEN];
	int		max_req;
	int		socket;
	int		ttl;
	pid_t	pid;
	uid_t	uid;
	struct sockaddr_in *dst;
	struct sockaddr_in res;
	struct icmphdr icmphdr;
}				t_env;

void			ft_ping(void);
int				init_socket(void);
void			resolve_hostname(void);
void			send_icmp_echo(void);
void			recv_icmp_echo(void);

/* Utils */
void			ft_setenv(void);
void			ft_unsetenv(void);
void			exit_errors(char *s);
void			ft_parse_args(char **av);
void			handle_errors(int c);
unsigned short				checksum(void *addr, int len);
uint16_t icmp_checksum(const uint16_t *const data, const size_t byte_sz);

/* Libc */
int				ft_strcmp(const char *s1, const char *s2);
int				ft_isspace(char c);
int				ft_atoi(const char *str);
/* int				ft_isdigit(int c); */
/* int				str_isdigit(char *s); */
void			*ft_memset(void *s, int c, size_t n);

#endif
