/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:40:22 by linhnguy          #+#    #+#             */
/*   Updated: 2024/03/12 22:50:38 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	put_image(t_data *g_data, int check)
{
	int	i;
	int	j;

	i = 0;
	if (mlx_image_to_window(g_data->mlx, g_data->grass, 0, 0) == -1)
		return (false);
	while (g_data->map[i])
	{
		j = 0;
		while (g_data->map[i][j])
		{
			if (!choose_image(g_data, g_data->map[i][j], j, i))
				return (false);
			else if (g_data->map[i][j] == 'E' && g_data->potion_count != 0)
				g_data->map[i][j] = '0';
			j++;
		}
		i++;
	}
	if (check == 1)
	{
		ft_printf("Number of movements is: %i\n", g_data->movements);
		g_data->movements++;
	}
	return (true);
}

bool	resize(t_data *g_data)
{
	if (!mlx_resize_image(g_data->end, g_data->map_width, g_data->map_height))
		return (false);
	if (!mlx_resize_image(g_data->grass,
			g_data->map_width, g_data->map_height))
		return (false);
	if (!mlx_resize_image(g_data->slime, INDEX_WIDTH, INDEX_HEIGHT))
		return (false);
	if (!mlx_resize_image(g_data->potion, INDEX_WIDTH, INDEX_HEIGHT))
		return (false);
	if (!mlx_resize_image(g_data->tree, INDEX_WIDTH, INDEX_HEIGHT))
		return (false);
	if (!mlx_resize_image(g_data->exit, INDEX_WIDTH, INDEX_HEIGHT))
		return (false);
	return (true);
}

static bool	load_png(t_data *g_data)
{
	g_data->end1 = mlx_load_png("./assets/end.png");
	g_data->grass1 = mlx_load_png("./assets/grass.png");
	g_data->slime1 = mlx_load_png("./assets/slime.png");
	g_data->potion1 = mlx_load_png("./assets/red_potion.png");
	g_data->tree1 = mlx_load_png("./assets/Tree2.png");
	g_data->exit1 = mlx_load_png("./assets/exit.png");
	if (!g_data->end1 || !g_data->grass1 || !g_data->slime1
		|| !g_data->potion1 || !g_data->tree1)
	{
		ft_printf("ERROR\n mlx load png failed");
		return (false);
	}
	return (true);
}

static bool	create_image(t_data *g_data)
{
	g_data->end = mlx_texture_to_image(g_data->mlx, g_data->end1);
	g_data->grass = mlx_texture_to_image(g_data->mlx, g_data->grass1);
	g_data->slime = mlx_texture_to_image(g_data->mlx, g_data->slime1);
	g_data->potion = mlx_texture_to_image(g_data->mlx, g_data->potion1);
	g_data->exit = mlx_texture_to_image(g_data->mlx, g_data->exit1);
	g_data->tree = mlx_texture_to_image(g_data->mlx, g_data->tree1);
	if (!g_data->end || !g_data->grass || !g_data->slime
		|| !g_data->potion || !g_data->tree)
	{
		ft_printf("ERROR\n mlx textture to image failed");
		return (false);
	}
	return (true);
}

bool	make_images(t_data *g_data)
{
	if ((!load_png(g_data)) || (!create_image(g_data)))
	{
		free_images(g_data);
		return (false);
	}
	if (!resize(g_data))
	{
		free_images(g_data);
		ft_printf("ERROR\n mlx resize failed");
		return (false);
	}
	if (!put_image(g_data, 0))
	{
		free_images(g_data);
		return (false);
	}
	return (true);
}
