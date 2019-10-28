/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_weapon_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:15:48 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/28 17:34:43 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		output_text_ripper(t_doom *doom)
{
	int		i;

	i = -1;
	ft_putstr_fd("3\t\t2\t\t1 6\n", doom->file->fd);
	while (++i < COUNT_RIPPER)
		out_img_weapon(doom->txt->ripper[i], doom->file);
	ft_putstr_fd("#\n\n", doom->file->fd);
}

void		output_text_shotgun(t_doom *doom)
{
	int		i;

	i = -1;
	ft_putstr_fd("2\t\t2\t\t1 7\n", doom->file->fd);
	while (++i < COUNT_SHOTG)
		out_img_weapon(doom->txt->shotgun[i], doom->file);
	ft_putstr_fd(".\n", doom->file->fd);
}

void		output_text_pistol(t_doom *doom)
{
	int		i;

	i = -1;
	ft_putstr_fd("1\t\t3\t\t1 2 9\n", doom->file->fd);
	while (++i < COUNT_PIST)
		out_img_weapon(doom->txt->pistol[i], doom->file);
	ft_putstr_fd(".\n", doom->file->fd);
}

void		output_text_foot(t_doom *doom)
{
	int		i;

	i = -1;
	ft_putstr_fd("0\t\t2\t\t1 3\n", doom->file->fd);
	ft_putstr_fd("3 3 0 0 0 0 0 0 0 0 0\n", doom->file->fd);
	while (++i < COUNT_FOOT)
		out_img_weapon(doom->txt->foot[i], doom->file);
	ft_putstr_fd(".\n", doom->file->fd);
}

void		export_weapon_data(t_doom *doom)
{
	ft_putstr_fd("weapon_data\n4\n", doom->file->fd);
	output_text_foot(doom);
	output_text_pistol(doom);
	output_text_shotgun(doom);
	output_text_ripper(doom);
}
