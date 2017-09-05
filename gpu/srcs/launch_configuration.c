/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_configuration.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/09/05 16:51:34 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <cluster.h>
#include <parse.h>

void			local_config(t_world *world, char *argv)
{
	//parse_rtv1(world, argv);
	//load_data(world);
	interface_launch(world, argv);
}

void			master_config(t_world *world, char *argv)
{
	parse_rtv1(world, argv);
	load_data(world);
	ft_putstr("Waiting for connection...\n");
	master_cluster(world);
	ft_putstr("End of connexion, get started again\n");
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
	if (flags == 0 && argv[1])
		local_config(world, argv[1]);
	else if (flags == 1 && argv[1])
		master_config(world, argv[1]);
	else if (flags == 2)
		client_config(world, argv[2]);
}
