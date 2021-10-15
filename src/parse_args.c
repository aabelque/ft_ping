/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizou </var/mail/zizou>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:30:55 by zizou             #+#    #+#             */
/*   Updated: 2021/10/12 20:52:59 by zizou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern t_env g;

void		ft_parse_args(char **av) {
	char *s;

	while (av && *av) {
		s = *av;
		if (*s == '-') {
			while (*s != '\0') {
				switch (*s) {
					case 'h':
						g.opt.h = true;
						break;
					case 'v':
						g.opt.v = true;
						break;
				}
				s++;
			}
		}
		else
			g.arg = *av;
		av++;
	}
}
