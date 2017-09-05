/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_keyboard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 11:07:12 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/14 17:12:21 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

static int		key_hook_release(t_keypress *keys)
{
	keys->right = 0;
	keys->left = 0;
	keys->up = 0;
	keys->down = 0;
	keys->p_up = 0;
	keys->p_down = 0;
	keys->plus = 0;
	keys->minus = 0;
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->del = 0;
	keys->ctrl = 0;
	keys->tab = 0;
	keys->alt = 0;
	keys->pad_1 = 0;
	keys->pad_2 = 0;
	keys->pad_3 = 0;
	keys->pad_0 = 0;
	keys->pad_4 = 0;
	keys->pad_5 = 0;
	keys->pad_7 = 0;
	keys->pad_8 = 0;
	return (0);
}

static int		key_hook_pressed(int keycode, t_keypress *keys)
{
	keycode == RIGHT ? keys->right = 1 : 0;
	keycode == LEFT ? keys->left = 1 : 0;
	keycode == UP ? keys->up = 1 : 0;
	keycode == DOWN ? keys->down = 1 : 0;
	keycode == P_UP ? keys->p_up = 1 : 0;
	keycode == P_DOWN ? keys->p_down = 1 : 0;
	keycode == PLUS ? keys->plus = 1 : 0;
	keycode == MINUS ? keys->minus = 1 : 0;
	keycode == W ? keys->w = 1 : 0;
	keycode == A ? keys->a = 1 : 0;
	keycode == S ? keys->s = 1 : 0;
	keycode == D ? keys->d = 1 : 0;
	keycode == DEL ? keys->del = 1 : 0;
	keycode == CTRL ? keys->ctrl = 1 : 0;
	keycode == TAB ? keys->tab = 1 : 0;
	keycode == ALT ? keys->alt = 1 : 0;
	keycode == PAD_1 ? keys->pad_1 = 1 : 0;
	keycode == PAD_2 ? keys->pad_2 = 1 : 0;
	keycode == PAD_0 ? keys->pad_0 = 1 : 0;
	keycode == PAD_3 ? keys->pad_3 = 1 : 0;
	keycode == PAD_7 ? keys->pad_7 = 1 : 0;
	keycode == PAD_8 ? keys->pad_8 = 1 : 0;
	keycode == PAD_4 ? keys->pad_4 = 1 : 0;
	keycode == PAD_5 ? keys->pad_5 = 1 : 0;
	return (0);
}

static void		check_pressed_keys_next(t_keypress *keys, t_env *e)
{
	if (keys->w)
		point_vector_scal(&e->scene->camera.pos, &e->scene->camera.axe_z, 1);
	if (keys->s)
		point_vector_scal(&e->scene->camera.pos, &e->scene->camera.axe_z, -1);
	if (keys->a)
		point_vector_scal(&e->scene->camera.pos, &e->scene->camera.axe_x, -1);
	if (keys->d)
		point_vector_scal(&e->scene->camera.pos, &e->scene->camera.axe_x, 1);
	if (keys->tab)
		cam_reset(&e->scene->camera);
	if (keys->tab)
		cam_reset(&e->scene->camera);
	keys->pad_1 ? e->image->endian = 1 : 0;
	keys->pad_2 ? e->image->endian = 0 : 1;
	keys->pad_7 ? e->scene->brillance = 1 : 0;
	keys->pad_8 ? e->scene->brillance = 0 : 1;
	keys->pad_3 ? e->scene->light = 1 : 0;
	keys->pad_0 ? e->scene->light = 0 : 1;
	keys->pad_4 ? e->scene->shadow = 1 : 0;
	keys->pad_5 ? e->scene->shadow = 0 : 1;
}

void			check_pressed_keys(t_keypress *keys, t_scene *e, t_env *env)
{
	if (keys->left)
		vector_rot_y(&e->camera.axe_z, &e->camera.axe_x, deg_to_radian(-10));
	if (keys->right)
		vector_rot_y(&e->camera.axe_z, &e->camera.axe_x, deg_to_radian(10));
	if (keys->up)
		vector_rot_x(&e->camera.axe_y, &e->camera.axe_z, deg_to_radian(10));
	if (keys->down)
		vector_rot_x(&e->camera.axe_y, &e->camera.axe_z, deg_to_radian(-10));
	if (keys->p_up)
		vector_rot_z(&e->camera.axe_x, &e->camera.axe_y, deg_to_radian(-10));
	if (keys->p_down)
		vector_rot_z(&e->camera.axe_x, &e->camera.axe_y, deg_to_radian(10));
	if (keys->plus)
		point_vector_scal(&e->camera.pos, &e->camera.axe_z, 1);
	if (keys->minus)
		point_vector_scal(&e->camera.pos, &e->camera.axe_z, -1);
	check_pressed_keys_next(keys, env);
	key_hook_release(&env->keys);
}

int				key_hook(int button, t_env *e)
{
	if (button == ECHAP)
		exit(0);
	button == 15 ? e->mouse_event = 1 : 0;
	button == 17 ? e->mouse_event = 0 : 1;
	key_hook_pressed(button, &e->keys);
	check_pressed_keys(&e->keys, e->scene, e);
	mlx_del(e);
	return (0);
}
