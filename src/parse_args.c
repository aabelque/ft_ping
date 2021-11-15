/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizou </var/mail/zizou>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:30:55 by zizou             #+#    #+#             */
/*   Updated: 2021/11/15 00:09:06 by zizou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern struct s_env global_env;

static void set_ttl(int ac, char **av)
{
		if (ac == 3) {
				global_env.ttl = ft_atoi(*av++);
		} else {
				av++;
				global_env.ttl = ft_atoi(*av);
		}
		if (!global_env.ttl)
				exit_errors("ping: can't set unicast time-to-live: Invalid argument\n");
}

void		ft_parse_args(int ac, char **av)
{
		char *s = NULL;

		while (av && *av) {
				s = *av;
				if (*s == '-') {
						global_env.dash++;
						if (*(s + 1) == '\0') {
								fprintf(stderr, "ft_ping: You have to set an option after '-'\n");
								fprintf(stderr, "%s\n%49s\n", USAGE, USAGE_OPT);
								exit_errors("");
						}
						while (*(++s) != '\0') {
								switch (*s) {
								case 'h':
										global_env.opt.h = true;
										break;
								case 'v':
										global_env.opt.v = true;
										break;
								case 'q':
										global_env.opt.q = true;
										break;
								case 't':
										set_ttl(ac, av);
										if (ac > 3) {
												s++;
												av++;
										}
										s++;
										break;
								default:
										fprintf(stderr, "ft_ping: invalid option -- '%c'\n", *s);
										fprintf(stderr, "%s\n%49s\n", USAGE, USAGE_OPT);
										exit_errors("");
								}
						}
				} else {
						if (!global_env.arg) {
								global_env.arg = malloc(ft_strlen(*av) + 1); 
								ft_memset(global_env.arg, 0, ft_strlen(*av) + 1);
								if (!global_env.arg)
										exit_errors("Malloc() failed\n");
								ft_memcpy(global_env.arg, *av, ft_strlen(*av));
						}
				}
		av++;
	}
}
