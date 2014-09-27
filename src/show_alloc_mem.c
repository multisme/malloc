/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/24 12:23:38 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/27 13:25:53 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/malloc.h"

extern t_block	*g_tiny_malloc;
extern t_block	*g_small_malloc;
extern t_block	*g_large_malloc;
extern int		g_size;

static void			ft_putnbr_base(long int n, int div, char *s)
{
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n < div)
		write(1, &s[n], 1);
	else
	{
		ft_putnbr_base(n / div, div, s);
		ft_putnbr_base(n % div, div, s);
	}
}
#include <stdio.h>

static void			ft_print_memory(void *addr)
{
	long int		p;

	p = (long int)addr;
	p %= 268435456;
	ft_putstr("0x");
	ft_putnbr_base(p, 16, "0123456789ABCDEF");
}

static void			ft_putaddr(char *s, t_block *p)
{
	int				sum;

	sum = 0;
	ft_putstr(s);
	ft_print_memory(p);
	write(1, "\n", 1);
	while (p)
	{
		if ( p->freed != 1)
		{
			ft_print_memory(p + g_size / 16);
			write(1, " - ", 3);
			ft_print_memory(p->next);
			write(1, " : ", 3);
			ft_putnbr_base(p->size, 10, "0123456789");
			ft_putstr(" octects\n");
			sum += p->size;
		}
		p = p->next;
	}
	ft_putstr("Total : ");
	ft_putnbr_base(sum, 10, "0123456789");
	ft_putstr(" octects\n");
}
void				show_alloc_mem()
{
	if	(g_tiny_malloc)
		ft_putaddr("TINY : ", g_tiny_malloc);
	if	(g_small_malloc)
		ft_putaddr("SMALL : ", g_small_malloc);
	if	(g_large_malloc)
		ft_putaddr("LARGE : ", g_large_malloc);
}
