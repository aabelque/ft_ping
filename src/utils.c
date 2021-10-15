/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zizou </var/mail/zizou>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:21:32 by zizou             #+#    #+#             */
/*   Updated: 2021/10/14 21:01:12 by zizou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern t_env g;

void			exit_errors(char *s) {
	fprintf(stderr, "%s", s);
	ft_unsetenv();
	close(g.socket);
	exit(EXIT_FAILURE);
}

void			ft_setenv(void) {
	g.opt = (t_opt) { .h = false, .v = false };
	g.arg = NULL;
	g.max_req = 0;
	g.pid = 0;
	g.uid = 0;
	g.socket = 0;
	g.ttl = 64;
	g.dst = NULL;
}

void			ft_unsetenv(void) {
	g.opt = (t_opt) { .h = false, .v = false };
	g.arg = NULL;
	g.max_req = 0;
	g.pid = 0;
	g.uid = 0;
	g.socket = 0;
	g.ttl = 0;
	g.dst = NULL;
}

void			handle_errors(int ac) {
	if ((ac < 2 || ac > 3) || g.opt.h || (g.opt.v && ac != 3) || (!g.opt.v && ac > 2) || g.arg == NULL)
		exit_errors("Usage: ft_ping [-hv] [-h help] [-v verbose] destination\n");
	if (getuid() != 0)
		exit_errors("Operation not permitted. See man sudo\n");
}

unsigned short		checksum(void *addr, int len) {
	unsigned long checksum = 0;
	unsigned short *buf = addr;
	
	while (len > 1) {
		checksum += (unsigned short)*buf++;
		len -= sizeof(unsigned short);
	}
	if (len)
		checksum += *(unsigned char*)buf;
	checksum = (checksum >> 16) + (checksum & 0xffff);
	checksum = checksum + (checksum >> 16);
	return ((unsigned short)(~checksum));
}

uint16_t icmp_checksum(const uint16_t *const data, const size_t byte_sz)
{
  if (0 != (byte_sz & 1)) {
    exit_errors("icmp_checksum() failed");
  }

  uint32_t accu = 0;
  for (size_t i=0; i < (byte_sz >> 1); ++i) {
    const uint32_t val32 = data[i];
    accu = accu + val32;
  }

  /* Fold 32-bit sum to 16 bits */
  while (accu >> 16) {
    accu = (accu & 0xffff) + (accu >> 16);
  }

  const uint16_t checksum = ~accu;
  return checksum;
}

