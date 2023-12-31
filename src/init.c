/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:35:04 by dbredykh          #+#    #+#             */
/*   Updated: 2023/08/20 19:53:12 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fract_data_init(t_fractal *f)
{
	f->palettes = ft_get_palettes();
	f->palette_index = 0;
	f->palette = &f->palettes[0];
	f->palette_len = ft_palletelen(f);
	f->smooth = false;
	f->limx = -2;
	f->limy = 2;
	f->max_iter = 35;
	f->k = -0.5;
	f->h = 0;
	f->zoom = 3.5;
	if (f->f_type == 2)
	{
		if (isnan(f->c_re) || !f->c_im)
		{
			f->c_re = -0.8;
			f->c_im = 0.156;
		}
		f->k = 0;
	}
	if (f->f_type == 3)
		f->h = -0.6;
}

void	ft_fract_typify(t_fractal *f)
{
	if (f->f_type == 1)
		ft_calc_mandelbrot(f);
	else if (f->f_type == 2)
		ft_calc_julia(f);
	else if (f->f_type == 3)
		ft_calc_ship(f);
}

void	ft_draw_fract(t_fractal *f)
{
	f->y = 0;
	while (f->y < SIZE)
	{
		f->x = 0;
		while (f->x < SIZE)
		{
			ft_fract_typify(f);
			f->x++;
		}
		f->y++;
	}
}

void	init(t_fractal *f)
{
	fract_data_init(f);
	f->mlx = mlx_init(1100, SIZE, ft_take_name(f->f_type), false);
	if (!f->mlx)
		ft_error(MLX_ERR, f);
	f->g_img = mlx_new_image(f->mlx, SIZE, SIZE);
	if (!f->g_img)
		ft_error(IMG_ERR, f);
	ft_draw_fract(f);
	mlx_image_to_window(f->mlx, f->g_img, 350, 0);
	ft_put_helper(f);
	mlx_loop_hook(f->mlx, &ft_loop_hook, f);
	mlx_loop(f->mlx);
	terminate(f);
}

int	main(int argv, char **argc)
{
	t_fractal	*f;

	f = malloc(sizeof(t_fractal));
	if (!f)
		exit (EXIT_FAILURE);
	ft_indata_checke(argv, argc, f);
	return (0);
}
