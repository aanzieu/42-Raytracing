

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"
#include "header/nuklear.h"
#include "header/gui.h"

int	key_press(struct nk_context *ctx, t_world *world)
{
	if (ctx->input.keyboard.keys[NK_KEY_L].down)
		world->keys.light_none = 1;
	else if (ctx->input.keyboard.keys[NK_KEY_K].down)
		world->keys.light_none = 0;
	else
		return (0);
	return(1);
	// rt(world);
	
	
}