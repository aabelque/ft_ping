/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:41:59 by aabelque          #+#    #+#             */
/*   Updated: 2021/11/18 16:26:02 by zizou            ###   ########.fr       */
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
#include <arpa/nameser.h>
#include <signal.h>

#define USAGE "Usage: ft_ping [-Dhqv] [-t ttl] destination"

#define NI_MAXHOST 1025
#define NI_MAXSERV 32

#define IPHDR_SIZE sizeof(struct ip)
#define ICMPHDR_SIZE sizeof(struct icmp)
#define DATA_SIZE 36
#define PING_SIZE (IPHDR_SIZE + ICMPHDR_SIZE + DATA_SIZE)

#define IPV4 4
#define IPV6 6

struct	s_opt
{
		bool	h;
		bool	v;
		bool	q;
		bool	ttl;
		bool	timestamp;
};

struct	s_env
{
		struct s_opt		opt;
		bool				rdns;
		char				*arg;
		char				dns[NI_MAXHOST];
		char				host[INET_ADDRSTRLEN];
		short				dash;
		int					socket;
		int					ttl;
		int					seq;
		int					ipv;
		pid_t				pid;
		long				packets_out;
		long				packets_in;
		long				errors;
		long				rtt_max;
		long				rtt_min;
		long				rtt_avg;
		long				rtt_total;
		long				rtt;
		long				mdev;
		struct timeval		tv_start;
		struct timeval		tv_tick;
		struct timeval		tv_end;
		struct sockaddr_in	*ipv4;
		struct addrinfo		*res;
};

void			ft_ping(void);
void			resolve_hostname(void);
void			update_statistics(long triptime);
void			update_stats(int nbytes, long triptime,
		struct icmp *icmp, struct ip *ip, int ttl);
void			get_reply(struct msghdr msg, int n);
int				init_socket(void);
int				send_ping(void);
int				recv_ping(void);
/* int				ip_version(char *s); */

/* Utils */
void			ft_setenv(void);
void			ft_unsetenv(void);
void			exit_errors(char *s);
void			ft_parse_args(int ac, char **av);
void			handle_errors(int c);
void			sig_interrupt(int sig);
void			sig_alarm(int sig);
void			sig_quit(int sig);
void			print_stats(void);
void			print_ewma_stats(void);
void			tv_sub(struct timeval *out, struct timeval *in);
unsigned short	checksum(void *addr, int len);
int				is_little_endian(void);
/* long			gettimeval(struct timeval before, struct timeval after); */

/* Libc */
void			*ft_memset(void *s, int c, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dest, const char *src);
int				ft_isspace(char c);
int				ft_atoi(const char *str);
size_t			ft_strlen(const char *s);
double			ft_sqrt(double x);
int				strisdigit(const char *s);
int				ft_isdigit(int c);

#endif
