/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizou </var/mail/zizou>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:30:55 by zizou             #+#    #+#             */
/*   Updated: 2021/11/17 02:33:48 by zizou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern struct s_env global_env;

void ft_parse_args(int ac, char **av)
{
		int  i;
		char *s;

		if (ac < 2) {
				fprintf(stderr, "%s\n", USAGE);
				exit_errors("");
		}
		i = 1;
		while (i < ac) {
				s = av[i];
				if (!strcmp(s, "-t")) {
						if (strisdigit(av[i + 1]) > 0) {
								global_env.ttl = ft_atoi(av[i++ + 1]);
								if (!global_env.ttl)
										exit_errors("ping: can't set unicast time-to-live: Invalid argument\n");
						} else {
								fprintf(stderr, "%s\n", USAGE);
								exit_errors("");
						}
				} else if (*s == '-') {
						s++;
						if (*s == '\0') {
								fprintf(stderr, "ft_ping: You have to set an option after '-'\n");
								fprintf(stderr, "%s\n", USAGE);
								exit_errors("");
						} while (*s != '\0') {
								if (*s == 'h') {
										global_env.opt.h = true;
								} else if (*s == 'v') {
										global_env.opt.v = true;
								} else if (*s == 'q') {
										global_env.opt.q = true;
								} else if (*s == 'D') {
										global_env.opt.timestamp = true;
								} else if (*s == 't') {
										fprintf(stderr, "%s\n", USAGE);
										exit_errors("");
								} else {
										fprintf(stderr, "ft_ping: invalid option -- '%c'\n", *s);
										fprintf(stderr, "%s\n", USAGE);
										exit_errors("");
								}
								s++;
						}
				} else {
						if (strisdigit(av[i]))
								fprintf(stderr, "%s\n", USAGE);
						global_env.arg = av[i];
				}
				i++;
		}
}
