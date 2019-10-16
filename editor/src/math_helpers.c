/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:44:28 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/15 13:44:29 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

double	ran(double l, double h)
{
	return (l + (h - l) * ((double)rand() / RAND_MAX * 2.0 - 1.0));
}

double	min(double a, double b)
{
	return (a > b ? b : a);
}

double	max(double a, double b)
{
	return (a > b ? a : b);
}

double	clamp(double a, double mi, double ma)
{
	return (min(max(a, mi), ma));
}

double	wrap(double a, double wr)
{
	if (a < 0)
		return (a + wr);
	if (a >= wr)
		return (a - wr);
	return (a);
}
