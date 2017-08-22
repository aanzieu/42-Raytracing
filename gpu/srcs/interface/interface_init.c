/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:48:38 by PZC               #+#    #+#             */
/*   Updated: 2017/08/22 16:57:58 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

static void init_topbar_bg(t_world *world)
{
	SDL_Rect	pos;

	world->interface.topbar = SDL_CreateRGBSurface(0, WIN_WIDTH, 36, 32, 0, 0, 0, 0);
	SDL_FillRect(world->interface.topbar, NULL, SDL_MapRGB(world->window.screen->format, 50, 50, 50));
	SDL_BlitSurface(world->interface.topbar, NULL, world->window.screen, NULL);
	SDL_FreeSurface(world->interface.topbar);
	world->interface.topbar = SDL_CreateRGBSurface(0, WIN_WIDTH, 1, 32, 0, 0, 0, 0);
	SDL_FillRect(world->interface.topbar, NULL, SDL_MapRGB(world->window.screen->format, 70, 70, 70));
	pos = interface_set_position(0, 36);
	SDL_BlitSurface(world->interface.topbar, NULL, world->window.screen, &pos);
	SDL_FreeSurface(world->interface.topbar);
}

void create_button(t_world *world, SDL_Rect *p, int x, int y)
{
	SDL_Surface *button;

	button = SDL_CreateRGBSurface(0, x, y, 32, 0, 0, 0, 0);
	SDL_FillRect(button, NULL, SDL_MapRGB(world->window.screen->format, 70, 70, 70));
	SDL_BlitSurface(button, NULL, world->window.screen, p);
	SDL_FreeSurface(button);
}

static void init_topbar_content(t_world *world)
{
	// SDL_Surface *button;
	SDL_Surface *texte;
	TTF_Font *police;
	SDL_Color white = {255, 255, 255, 255};
	SDL_Color yellow = {255, 255, 0, 255};
	SDL_Rect 	pos;

	pos = interface_set_position(0, 0);
	create_button(world, &pos, 100, 35);
	pos = interface_set_position(102, 0);
	create_button(world, &pos, 100, 35);

	pos = interface_set_position(10, 10);
	police = TTF_OpenFont("fonts/roboto.ttf", 14);
	if (world->keys.p == 1)
		texte = TTF_RenderText_Blended(police, "Snapshot(P)", yellow);
	else
		texte = TTF_RenderText_Blended(police, "Snapshot(P)", white);
	SDL_BlitSurface(texte, NULL, world->window.screen, &pos);

	pos = interface_set_position(111, 10);
	// police = TTF_OpenFont("fonts/roboto.ttf", 16);
	// TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
	texte = TTF_RenderText_Blended(police, "Open folder", white);
	SDL_BlitSurface(texte, NULL, world->window.screen, &pos);

	TTF_CloseFont(police);
    SDL_FreeSurface(texte);
}

static void init_sidebar_bg(t_world *world)
{
	SDL_Surface *rect;
	SDL_Rect	pos;

	pos.x = WIN_WIDTH - 240;
	pos.y = 0;
	rect = SDL_CreateRGBSurface(0, 240, WIN_HEIGHT, 32, 0, 0, 0, 0);
	SDL_FillRect(rect, NULL, SDL_MapRGB(world->window.screen->format, 50, 50, 50));
	SDL_BlitSurface(rect, NULL, world->window.screen, &pos);
	SDL_FreeSurface(rect);
	rect = SDL_CreateRGBSurface(0, 1, WIN_HEIGHT, 32, 0, 0, 0, 0);
	SDL_FillRect(rect, NULL, SDL_MapRGB(world->window.screen->format, 70, 70, 70));
	pos.x = WIN_WIDTH - 240;
	pos.y = 0;
	SDL_BlitSurface(rect, NULL, world->window.screen, &pos);
	SDL_FreeSurface(rect);
}

void create_loader(t_world *world)
{
	SDL_Surface *rect;
	SDL_Surface *texte;
	TTF_Font *police;
	SDL_Color white = {255, 255, 255, 255};
	SDL_Rect	pos;
	static int i = 10;
	
	pos = interface_set_position(30, WIN_HEIGHT - 30);
	rect = SDL_CreateRGBSurface(0, i, 5, 32, 0, 0, 0, 0);
	SDL_FillRect(rect, NULL, SDL_MapRGB(world->window.screen->format, 255, 255, 255));
	SDL_BlitSurface(rect, NULL, world->window.screen, &pos);
	SDL_FreeSurface(rect);
	pos = interface_set_position(30, WIN_HEIGHT - 50);
	police = TTF_OpenFont("fonts/roboto.ttf", 12);
	texte = TTF_RenderText_Blended(police, "Loading...", white);
	SDL_BlitSurface(texte, NULL, world->window.screen, &pos);
	TTF_CloseFont(police);
    SDL_FreeSurface(texte);
	// i += 10;
	// if (i > 50)
	// 	i = 10;
}

void	init_interface(t_world *world)
{
	// SDL_Surface *loader;
	// SDL_Rect 	pos;

	// int initted=IMG_Init(IMG_INIT_PNG);
	// if(!initted) {
	//     printf("IMG_Init: Failed to init required jpg and png support!\n");
	//     printf("IMG_Init: %s\n", IMG_GetError());
	//     // handle error
	// }

	init_sidebar_bg(world);
	init_topbar_bg(world);
	init_topbar_content(world);
	// loader = IMG_Load("img/loading.png");
	// pos = interface_set_position(200, 200);
	// SDL_BlitSurface(loader, NULL, world->window.screen, &pos);
	// SDL_FreeSurface(loader);

	// IMG_Quit();
}
