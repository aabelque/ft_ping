/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizou </var/mail/zizou>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 10:48:36 by zizou             #+#    #+#             */
/*   Updated: 2021/10/12 20:48:36 by zizou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int		ft_strcmp(const char *s1, const char *s2) {
	while (*s1 == *s2) {
		if (*s1 == '\0')
			return (0);
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int				ft_isspace(char c) {
	if (c == ' ' || c == '\t' || c == '\f' || c == '\r' || c == '\n'
			|| c == '\v')
		return (1);
	return (0);
}

int				ft_atoi(const char *str) {
	int			i, sign;
	long		nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	if (!str[i])
		return (0);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+') {
		if (str[++i] == '-')
			sign = -1;
	}
	while (str[i] <= '0' || str[i] >= '9')
		i++;
	while (str[i] >= '0' && str[i] <= '9') {
		nbr = (nbr * 10) + (str[i++] - '0');
	}
	return (nbr * sign);
}

void			*ft_memset(void *s, int c, size_t n) {
	while(n) {
		*(char *)s = (unsigned char)c;
		s++;
		n--;
	}
	return (s);
}
/* int				ft_isdigit(int c) { */
/* 	if (c >= '0' || c <= '9') */
/* 		return (1); */
/* 	return (0); */
/* } */

/* int				str_isdigit(char *s) { */
/* 	while (*s) { */
/* 		if (ft_isdigit(*s)) */
/* 			s++; */
/* 		else */
/* 			return (0); */
/* 	} */
/* 	return (1); */
/* } */


