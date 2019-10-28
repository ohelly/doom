/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_text_stobj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 19:42:58 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/28 20:11:34 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		out_text(int st, int end, t_txt *txt, t_file *file)
{
	while (st <= end)
	{
		out_img_weapon(txt->stobj[st], file);
		st++;
	}
}

void		output_text_stobj_p2(int ind, t_doom *doom)
{
	if (ind == 9)
		out_text(11, 11, doom->txt, doom->file);
	else if (ind == 10)
		out_text(8, 8, doom->txt, doom->file);
	else if (ind == 11)
		out_text(10, 10, doom->txt, doom->file);
	else if (ind == 12)
		out_text(9, 9, doom->txt, doom->file);
	else if (ind == 13)
		out_text(2, 4, doom->txt, doom->file);
	else if (ind == 14)
		out_text(5, 6, doom->txt, doom->file);
	else if (ind == 15)
		out_text(18, 31, doom->txt, doom->file);
}

void		output_text_stobj(int ind, t_doom *doom)
{
	if (ind == 0)
		out_text(0, 0, doom->txt, doom->file);
	else if (ind == 1)
		out_text(1, 1, doom->txt, doom->file);
	else if (ind == 2)
		out_text(12, 12, doom->txt, doom->file);
	else if (ind == 3)
		out_text(13, 13, doom->txt, doom->file);
	else if (ind == 4)
		out_text(14, 14, doom->txt, doom->file);
	else if (ind == 5)
		out_text(15, 15, doom->txt, doom->file);
	else if (ind == 6)
		out_text(16, 16, doom->txt, doom->file);
	else if (ind == 7)
		out_text(7, 7, doom->txt, doom->file);
	else if (ind == 8)
		out_text(17, 17, doom->txt, doom->file);
	else
		output_text_stobj_p2(ind, doom);
}
