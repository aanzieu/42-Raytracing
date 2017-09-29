/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_configuration.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/09/29 17:19:38 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <cluster.h>
#include <parse.h>

void			local_config(t_world *world, char *argv)
{
	interface_launch(world, argv);
}

void			client_config(t_world *world, char *argv)
{
	if (argv == NULL)
		ft_putstr_fd("usage : ./bin/RT map.xml client 'MASTER IP'\n", 1);
	serveur_address_serveur(argv, world);
	ft_putstr("Thank you for your patience\n");
}

void			choose_main_launcher(char **argv, int flags)
{
	t_world		*world;

	if (!(world = (t_world*)ft_memalloc(sizeof(t_world))))
		memory_allocation_error();
	data_setup(world);
	get_viewplane(world);
	if (flags == 0)
		local_config(world, NULL);
	else if (flags == 2)
		client_config(world, argv[2]);
}
