/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizou </var/mail/zizou>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:30:55 by zizou             #+#    #+#             */
/*   Updated: 2021/10/19 01:54:18 by zizou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern struct s_env global_env;

void		ft_parse_args(char **av)
{
		char *s;

		while (av && *av) {
				s = *av;
				if (*s == '-') {
						while (*s != '\0') {
								switch (*s) {
								case 'h':
										global_env.opt.h = true;
										break;
								case 'v':
										global_env.opt.v = true;
										break;
								}
						s++;
						}
				} else {
						global_env.arg = (char *)malloc(ft_strlen(*av) + 1); 
				if (!global_env.arg)
						exit_errors("Malloc() failed\n");
				ft_memcpy(global_env.arg, *av, ft_strlen(*av));
				}
		av++;
	}
}
