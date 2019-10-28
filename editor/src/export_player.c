/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 22:57:53 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/28 23:03:46 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		export_player(t_doom *doom)
{
	ft_putstr_fd("Player\t", doom->file->fd);
	ft_putnbr_fd(doom->player->pos.y, doom->file->fd);
	ft_putstr_fd(" ", doom->file->fd);
	ft_putnbr_fd(doom->player->pos.x, doom->file->fd);
	ft_putstr_fd("\t\t", doom->file->fd);
	ft_putnbr_fd(doom->player->angle, doom->file->fd);
	ft_putstr_fd("\t\t", doom->file->fd);
	ft_putnbr_fd(doom->player->sec, doom->file->fd);
	ft_putstr_fd("\t\t", doom->file->fd);
	ft_putnbr_fd(doom->player->hp, doom->file->fd);
	ft_putstr_fd("\t\t", doom->file->fd);
	ft_putnbr_fd(doom->player->weapon, doom->file->fd);
	ft_putstr_fd("\t\t", doom->file->fd);
	ft_putnbr_fd(doom->player->end, doom->file->fd);
	ft_putstr_fd("\n", doom->file->fd);
}
