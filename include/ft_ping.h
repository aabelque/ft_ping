/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:41:59 by aabelque          #+#    #+#             */
/*   Updated: 2021/10/19 01:36:38 by zizou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

#include <stdio.h>
#include <stdlib.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <signal.h>
#include <arpa/inet.h>
#include <signal.h>

#define IPHDR_SIZE sizeof(struct ip)
#define ICMPHDR_SIZE sizeof(struct icmp)
#define DATA_SIZE 36
#define PING_SIZE (IPHDR_SIZE + ICMPHDR_SIZE + DATA_SIZE)

struct	s_opt
{
		bool	h;
		bool	v;
};

struct	s_env
{
		struct s_opt		opt;
		char				*arg;
		char				host[INET_ADDRSTRLEN];
		unsigned int		packets_out;
		unsigned int		packets_in;
		float				rtt_max;
		float				rtt_min;
		float				rtt_avg;
		float				rtt_total;
		float				mdev;
		int					socket;
		int					ttl;
		int					seq;
		pid_t				pid;
		struct timeval		tv_start;
		struct timeval		tv_tick;
		struct timeval		tv_end;
		struct sockaddr_in	*dst;
		struct sockaddr_in	res;
};

void			ft_ping(void);
int				init_socket(void);
struct ip		*fill_iphdr(struct ip *ip);
struct icmp		*fill_icmphdr(struct icmp *icmp);
struct msghdr	fill_msghdr(struct iovec *iov);
void			get_reply(struct msghdr msg, int n);
void			resolve_hostname(void);
int				send_ping(void);
int				recv_ping(void);

/* Utils */
void			ft_setenv(void);
void			ft_unsetenv(void);
void			exit_errors(char *s);
void			ft_parse_args(char **av);
void			handle_errors(int c);
unsigned short	checksum(void *addr, int len);
int				is_little_endian(void);
double			gettimeval(struct timeval before, struct timeval after);
void			sig_interrupt(int sig);
void			sig_alarm(int sig);
void			print_stats(void);

/* Libc */
int				ft_strcmp(const char *s1, const char *s2);
int				ft_isspace(char c);
int				ft_atoi(const char *str);
/* int				ft_isdigit(int c); */
/* int				str_isdigit(char *s); */
size_t			ft_strlen(char *s);
void			*ft_memset(void *s, int c, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
double			ft_sqrt(double x);
double		ft_pow(double x, int y);

#endif
