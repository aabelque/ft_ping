/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizou </var/mail/zizou>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 10:48:36 by zizou             #+#    #+#             */
/*   Updated: 2021/11/17 02:42:35 by zizou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

inline int strisdigit(const char *s)
{
		if (!s || !ft_strlen(s))
				return (0);
		while (*s != '\0')
				if (!ft_isdigit(*s++))
						return (0);
		return (1);
}

inline int ft_isdigit(int c)
{
		if (c >= '0' && c <= '9')
				return (1);
		return (0);
}

inline size_t ft_strlen(const char *s)
{
		const char *i = s;

		while (*s)
				s++;
		return (s - i);
}

inline void *ft_memcpy(void *dst, const void *src, size_t n)
{
		size_t	i = 0;

		while (i < n) {
				((char *)dst)[i] = ((char *)src)[i];
				i++;
		}
		return (dst);
}

inline int	ft_strcmp(const char *s1, const char *s2)
{
		while (*s1 == *s2) {
				if (*s1 == '\0')
						return (0);
				s1++;
				s2++;
		}
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

inline char	*ft_strcpy(char *dest, const char *src)
{
		char *tmp = dest;

		while ((*dest++ = *src++) != 0)
				;
		return tmp;
}

inline int	ft_isspace(char c)
{
		if (c == ' ' || c == '\t' || c == '\f' || c == '\r'
				|| c == '\n'|| c == '\v')
				return (1);
		return (0);
}

int	ft_atoi(const char *str)
{
		int	i, sign;
		long nbr;
		
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
		while (str[i] < '0' || str[i] > '9')
				i++;
		while (str[i] >= '0' && str[i] <= '9') {
				nbr = (nbr * 10) + (str[i++] - '0');
		}
		return (nbr * sign);
}

inline void *ft_memset(void *s, int c, size_t n)
{
		while (n) {
				*(char *)s = (unsigned char)c;
				s++;
				n--;
		}
		return (s);
}

double ft_sqrt(double x)
{
		double sqrt = 0, tmp = 0;

		sqrt = x / 2;

		while (sqrt != tmp) {
				tmp = sqrt;
				sqrt = (x / tmp + tmp) / 2;
		}
		return (sqrt);
}
