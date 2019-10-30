/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:15:21 by glormell          #+#    #+#             */
/*   Updated: 2019/10/30 14:16:26 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct		s_be
{
	int				x;
	int				begin;
	int				end;
}					t_be;

typedef struct		s_cf
{
	float			hei;
	int				x;
	int				y;
}					t_cf;

typedef struct		s_py_i
{
	int				y1;
	int				y2;
}					t_py_i;

typedef struct		s_xy
{
	float			x;
	float			y;
}					t_xy;

typedef	struct		s_xyz
{
	float			x;
	float			y;
	float			z;
}					t_xyz;

typedef	struct		s_ab_i
{
	int				a;
	int				b;
}					t_ab_i;

#endif
